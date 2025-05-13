#include <cstdio>
#include <string>
#include "ILocArm64.h"
#include "Common.h"
#include "Function.h"
#include "PlatformArm64.h"
#include "Module.h"

ArmInst::ArmInst(std::string _opcode,
                 std::string _result,
                 std::string _arg1,
                 std::string _arg2,
                 std::string _cond,
                 std::string _addition)
    : opcode(_opcode), cond(_cond), result(_result), arg1(_arg1), arg2(_arg2), addition(_addition), dead(false)
{}

void ArmInst::replace(std::string _opcode,
                      std::string _result,
                      std::string _arg1,
                      std::string _arg2,
                      std::string _cond,
                      std::string _addition)
{
    opcode = _opcode;
    result = _result;
    arg1 = _arg1;
    arg2 = _arg2;
    cond = _cond;
    addition = _addition;
}

void ArmInst::setDead() { dead = true; }

std::string ArmInst::outPut()
{
    if (dead) return "";
    if (opcode.empty()) return "";
    std::string ret = opcode;
    if (!cond.empty()) ret += cond;
    if (!result.empty()) {
        if (result == ":") ret += result;
        else ret += " " + result;
    }
    if (!arg1.empty()) ret += "," + arg1;
    if (!arg2.empty()) ret += "," + arg2;
    if (!addition.empty()) ret += "," + addition;
    return ret;
}

#define emit(...) code.push_back(new ArmInst(__VA_ARGS__))

ILocArm64::ILocArm64(Module * _module) { this->module = _module; }

ILocArm64::~ILocArm64()
{
    for (auto pIter = code.begin(); pIter != code.end(); ++pIter) {
        delete (*pIter);
    }
}

void ILocArm64::deleteUsedLabel()
{
    std::list<ArmInst *> labelInsts;
    for (ArmInst * arm: code) {
        if ((!arm->dead) && (arm->opcode[0] == '.') && (arm->result == ":")) {
            labelInsts.push_back(arm);
        }
    }
    for (ArmInst * labelArm: labelInsts) {
        bool labelUsed = false;
        for (ArmInst * arm: code) {
            if ((!arm->dead) && (arm->opcode[0] == 'b') && (arm->result == labelArm->opcode)) {
                labelUsed = true;
                break;
            }
        }
        if (!labelUsed) labelArm->setDead();
    }
}

void ILocArm64::outPut(FILE * file, bool outputEmpty)
{
    for (auto arm: code) {
        std::string s = arm->outPut();
        if (arm->result == ":") {
            fprintf(file, "%s\n", s.c_str());
            continue;
        }
        if (!s.empty()) {
            fprintf(file, "\t%s\n", s.c_str());
        } else if ((outputEmpty)) {
            fprintf(file, "\n");
        }
    }
}

std::list<ArmInst *> & ILocArm64::getCode() { return code; }

std::string ILocArm64::toStr(int64_t num, bool flag)
{
    std::string ret;
    if (flag) ret = "#";
    ret += std::to_string(num);
    return ret;
}

void ILocArm64::label(std::string name) { emit(name, ":"); }
void ILocArm64::inst(std::string op, std::string rs) { emit(op, rs); }
void ILocArm64::inst(std::string op, std::string rs, std::string arg1) { emit(op, rs, arg1); }
void ILocArm64::inst(std::string op, std::string rs, std::string arg1, std::string arg2) { emit(op, rs, arg1, arg2); }

void ILocArm64::comment(std::string str) { emit("//", str); }

// !所有的load_xx都是把xx加载到制定寄存器
// !所有的store_xx都是把寄存器的值存储到xx处

// 将一个立即数（常量）加载到指定寄存器。
void ILocArm64::load_imm(int rs_reg_no, int64_t constant)
{
    // ARM64: movz/movk 组合加载64位立即数，简化为mov
    emit("mov", PlatformArm64::regName[rs_reg_no], toStr(constant));
}

// 将符号（如全局变量地址）加载到寄存器。
void ILocArm64::load_symbol(int rs_reg_no, std::string name)
{
    // ARM64: adrp/add 组合加载符号地址，简化为adrp
    emit("adrp", PlatformArm64::regName[rs_reg_no], name);
    emit("add", PlatformArm64::regName[rs_reg_no], PlatformArm64::regName[rs_reg_no], ":lo12:" + name);
}

//从基址寄存器加偏移（或加寄存器）地址处加载内存到寄存器。
void ILocArm64::load_base(int rs_reg_no, int base_reg_no, int disp)
{
    std::string rsReg = PlatformArm64::regName[rs_reg_no];
    std::string base = PlatformArm64::regName[base_reg_no];
    if (PlatformArm64::isDisp(disp)) {
        if (disp) base += "," + toStr(disp);
    } else {
        load_imm(rs_reg_no, disp);
        base += "," + rsReg;
    }
    base = "[" + base + "]";
    emit("ldr", rsReg, base);
}

// 将寄存器内容存储到基址寄存器加偏移（或加寄存器）地址处。
void ILocArm64::store_base(int src_reg_no, int base_reg_no, int disp, int tmp_reg_no)
{
    std::string base = PlatformArm64::regName[base_reg_no];
    if (PlatformArm64::isDisp(disp)) {
        if (disp) base += "," + toStr(disp);
    } else {
        load_imm(tmp_reg_no, disp);
        base += "," + PlatformArm64::regName[tmp_reg_no];
    }
    base = "[" + base + "]";
    emit("str", PlatformArm64::regName[src_reg_no], base);
}

//寄存器之间的数据传送。
void ILocArm64::mov_reg(int rs_reg_no, int src_reg_no)
{
    emit("mov", PlatformArm64::regName[rs_reg_no], PlatformArm64::regName[src_reg_no]);
}

// 将变量的值加载到寄存器
void ILocArm64::load_var(int rs_reg_no, Value * src_var)
{
    if (Instanceof(constVal, ConstInt *, src_var)) {
        load_imm(rs_reg_no, constVal->getVal());
    } else if (src_var->getRegId() != -1) {
        int32_t src_regId = src_var->getRegId();
        if (src_regId != rs_reg_no) {
            emit("mov", PlatformArm64::regName[rs_reg_no], PlatformArm64::regName[src_regId]);
        }
    } else if (Instanceof(globalVar, GlobalVariable *, src_var)) {
        load_symbol(rs_reg_no, globalVar->getName());
        emit("ldr", PlatformArm64::regName[rs_reg_no], "[" + PlatformArm64::regName[rs_reg_no] + "]");
    } else {
        int32_t var_baseRegId = -1;
        int64_t var_offset = -1;
        bool result = src_var->getMemoryAddr(&var_baseRegId, &var_offset);
        if (!result) {
            minic_log(LOG_ERROR, "BUG");
        }
        load_base(rs_reg_no, var_baseRegId, var_offset);
    }
}

// 将变量的地址加载到寄存器
void ILocArm64::lea_var(int rs_reg_no, Value * var)
{
    int32_t var_baseRegId = -1;
    int64_t var_offset = -1;
    bool result = var->getMemoryAddr(&var_baseRegId, &var_offset);
    if (!result) {
        minic_log(LOG_ERROR, "BUG");
    }
    leaStack(rs_reg_no, var_baseRegId, var_offset);
}

// 将寄存器的值存储到变量（内存/全局/局部/寄存器变量）。
void ILocArm64::store_var(int src_reg_no, Value * dest_var, int tmp_reg_no)
{
    if (dest_var->getRegId() != -1) {
        int dest_reg_id = dest_var->getRegId();
        if (src_reg_no != dest_reg_id) {
            emit("mov", PlatformArm64::regName[dest_reg_id], PlatformArm64::regName[src_reg_no]);
        }
    } else if (Instanceof(globalVar, GlobalVariable *, dest_var)) {
        load_symbol(tmp_reg_no, globalVar->getName());
        emit("str", PlatformArm64::regName[src_reg_no], "[" + PlatformArm64::regName[tmp_reg_no] + "]");
    } else {
        int32_t dest_baseRegId = -1;
        int64_t dest_offset = -1;
        bool result = dest_var->getMemoryAddr(&dest_baseRegId, &dest_offset);
        if (!result) {
            minic_log(LOG_ERROR, "BUG");
        }
        store_base(src_reg_no, dest_baseRegId, dest_offset, tmp_reg_no);
    }
}

void ILocArm64::leaStack(int rs_reg_no, int base_reg_no, int off)
{
    std::string rs_reg_name = PlatformArm64::regName[rs_reg_no];
    std::string base_reg_name = PlatformArm64::regName[base_reg_no];
    if (PlatformArm64::constExpr(off))
        emit("add", rs_reg_name, base_reg_name, toStr(off));
    else {
        load_imm(rs_reg_no, off);
        emit("add", rs_reg_name, base_reg_name, rs_reg_name);
    }
}

void ILocArm64::allocStack(Function * func, int tmp_reg_no)
{
    int funcCallArgCnt = func->getMaxFuncCallArgCnt() - 8;
    funcCallArgCnt = std::max(funcCallArgCnt, 0);
    int off = func->getMaxDep();
    off += funcCallArgCnt * 8;
    if (0 == off) return;
    if (PlatformArm64::constExpr(off)) {
        emit("sub", "sp", "sp", toStr(off));
    } else {
        load_imm(tmp_reg_no, off);
        emit("sub", "sp", "sp", PlatformArm64::regName[tmp_reg_no]);
    }
    inst("add", PlatformArm64::regName[ARM64_FP_REG_NO], "sp", toStr(funcCallArgCnt * 8));
}

void ILocArm64::call_fun(std::string name)
{
    emit("bl", name);
}

void ILocArm64::nop()
{
    emit("nop");
}

void ILocArm64::jump(std::string label)
{
    emit("b", label);
}
