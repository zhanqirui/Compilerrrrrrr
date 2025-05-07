#include <cstdio>
#include "Common.h"
#include "ILocArm64.h"
#include "InstSelectorArm64.h"
#include "PlatformArm64.h"
#include "PointerType.h"
#include "RegVariable.h"
#include "Function.h"
#include "LabelInstruction.h"
#include "GotoInstruction.h"
#include "FuncCallInstruction.h"
#include "MoveInstruction.h"

InstSelectorArm64::InstSelectorArm64(vector<Instruction *> & _irCode,
                                     ILocArm64 & _iloc,
                                     Function * _func,
                                     SimpleRegisterAllocator & allocator)
    : ir(_irCode), iloc(_iloc), func(_func), simpleRegisterAllocator(allocator)
{
    translator_handlers[IRInstOperator::IRINST_OP_ENTRY] = &InstSelectorArm64::translate_entry;
    translator_handlers[IRInstOperator::IRINST_OP_EXIT] = &InstSelectorArm64::translate_exit;
    translator_handlers[IRInstOperator::IRINST_OP_LABEL] = &InstSelectorArm64::translate_label;
    translator_handlers[IRInstOperator::IRINST_OP_GOTO] = &InstSelectorArm64::translate_goto;
    translator_handlers[IRInstOperator::IRINST_OP_ASSIGN] = &InstSelectorArm64::translate_assign;

    // 新增：注册算术/逻辑/分支/函数相关指令
    translator_handlers[IRInstOperator::IRINST_OP_ADD_I] = &InstSelectorArm64::translate_add;
    translator_handlers[IRInstOperator::IRINST_OP_SUB_I] = &InstSelectorArm64::translate_sub;
    translator_handlers[IRInstOperator::IRINST_OP_MUL_I] = &InstSelectorArm64::translate_mul;
    translator_handlers[IRInstOperator::IRINST_OP_DIV_I] = &InstSelectorArm64::translate_div;
    translator_handlers[IRInstOperator::IRINST_OP_GT_I]  = &InstSelectorArm64::translate_gt;
    translator_handlers[IRInstOperator::IRINST_OP_LT_I]  = &InstSelectorArm64::translate_lt;
    translator_handlers[IRInstOperator::IRINST_OP_LE_I]  = &InstSelectorArm64::translate_le;
    translator_handlers[IRInstOperator::IRINST_OP_GE_I]  = &InstSelectorArm64::translate_ge;
    translator_handlers[IRInstOperator::IRINST_OP_EQ_I]  = &InstSelectorArm64::translate_eq;
    translator_handlers[IRInstOperator::IRINST_OP_NE_I]  = &InstSelectorArm64::translate_ne;
    translator_handlers[IRInstOperator::IRINST_OP_AND_I] = &InstSelectorArm64::translate_and;
    translator_handlers[IRInstOperator::IRINST_OP_OR_I]  = &InstSelectorArm64::translate_or;
    translator_handlers[IRInstOperator::IRINST_OP_NOT_I] = &InstSelectorArm64::translate_not;
    translator_handlers[IRInstOperator::IRINST_OP_MOD_I] = &InstSelectorArm64::translate_mod;
    translator_handlers[IRInstOperator::IRINST_OP_BRANCH_I] = &InstSelectorArm64::translate_branch;
    translator_handlers[IRInstOperator::IRINST_OP_FUNC_CALL] = &InstSelectorArm64::translate_func_call;
    translator_handlers[IRInstOperator::IRINST_OP_ARG] = &InstSelectorArm64::translate_arg;
}

InstSelectorArm64::~InstSelectorArm64() {}

void InstSelectorArm64::run() {
    for (auto inst: ir) {
        if (!inst->isDead()) {
            translate(inst);
        }
    }
}

void InstSelectorArm64::translate(Instruction * inst) {
    IRInstOperator op = inst->getOp();
    auto pIter = translator_handlers.find(op);
    if (pIter == translator_handlers.end()) {
        printf("Translate: Operator(%d) not support", (int) op);
        return;
    }
    if (showLinearIR) {
        outputIRInstruction(inst);
    }
    (this->*(pIter->second))(inst);
}

void InstSelectorArm64::outputIRInstruction(Instruction * inst) {
    std::string irStr;
    inst->toString(irStr);
    if (!irStr.empty()) {
        iloc.comment(irStr);
    }
}

void InstSelectorArm64::translate_nop(Instruction * inst) {
    (void) inst;
    iloc.nop();
}

void InstSelectorArm64::translate_label(Instruction * inst) {
    Instanceof(labelInst, LabelInstruction *, inst);
    iloc.label(labelInst->getName());
}

void InstSelectorArm64::translate_goto(Instruction * inst) {
    Instanceof(gotoInst, GotoInstruction *, inst);
    iloc.jump(gotoInst->getTarget()->getName());
}

void InstSelectorArm64::translate_entry(Instruction * inst) {
    auto & protectedRegNo = func->getProtectedReg();
    auto & protectedRegStr = func->getProtectedRegStr();
    bool first = true;
    for (auto regno: protectedRegNo) {
        if (first) {
            protectedRegStr = PlatformArm64::regName[regno];
            first = false;
        } else if (!first) {
            protectedRegStr += "," + PlatformArm64::regName[regno];
        }
    }
    // 修改stp格式
    if (protectedRegNo.size() == 2) {
        iloc.inst("stp", PlatformArm64::regName[protectedRegNo[0]], PlatformArm64::regName[protectedRegNo[1]], "[sp, #-16]!");
    } else if (protectedRegNo.size() == 1) {
        iloc.inst("str", PlatformArm64::regName[protectedRegNo[0]], "[sp, #-8]!");
    }
    iloc.allocStack(func, ARM64_TMP_REG_NO);
}

void InstSelectorArm64::translate_exit(Instruction * inst) {
    if (inst->getOperandsNum()) {
        Value * retVal = inst->getOperand(0);
        iloc.load_var(0, retVal);
    }
    auto & protectedRegStr = func->getProtectedRegStr();
    iloc.inst("add", PlatformArm64::regName[ARM64_FP_REG_NO], PlatformArm64::regName[ARM64_FP_REG_NO], iloc.toStr(func->getMaxDep()));
    iloc.inst("mov", "sp", PlatformArm64::regName[ARM64_FP_REG_NO]);
    // 修改ldp格式
    auto & protectedRegNo = func->getProtectedReg();
    if (protectedRegNo.size() == 2) {
        iloc.inst("ldp", PlatformArm64::regName[protectedRegNo[0]], PlatformArm64::regName[protectedRegNo[1]], "[sp], #16");
    } else if (protectedRegNo.size() == 1) {
        iloc.inst("ldr", PlatformArm64::regName[protectedRegNo[0]], "[sp], #8");
    }
    iloc.inst("ret", "");
}

void InstSelectorArm64::translate_assign(Instruction * inst) {
    Value * result = inst->getOperand(0);
    Value * arg1 = inst->getOperand(1);
    int32_t arg1_regId = arg1->getRegId();
    int32_t result_regId = result->getRegId();
    if (arg1_regId != -1) {
        iloc.store_var(arg1_regId, result, ARM64_TMP_REG_NO);
    } else if (result_regId != -1) {
        iloc.load_var(result_regId, arg1);
    } else {
        int32_t temp_regno = simpleRegisterAllocator.Allocate();
        iloc.load_var(temp_regno, arg1);
        iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO);
        simpleRegisterAllocator.free(temp_regno);
    }
}

// 算术二元指令
void InstSelectorArm64::translate_add(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst->getOperand(2);
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("add", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_sub(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst->getOperand(2);
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("sub", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_mul(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst->getOperand(2);
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("mul", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_div(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst->getOperand(2);
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("sdiv", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_mod(Instruction * inst) {
    // a % b = a - (a / b) * b
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst->getOperand(2);
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    int32_t tmp_div = simpleRegisterAllocator.Allocate();
    int32_t tmp_mul = simpleRegisterAllocator.Allocate();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("sdiv", PlatformArm64::regName[tmp_div], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.inst("mul", PlatformArm64::regName[tmp_mul], PlatformArm64::regName[tmp_div], PlatformArm64::regName[rhs_reg]);
    iloc.inst("sub", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[tmp_mul]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    simpleRegisterAllocator.free(tmp_div);
    simpleRegisterAllocator.free(tmp_mul);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

// ARMv8-A A64条件码映射
static const char* getA64Cond(IRInstOperator op) {
    switch (op) {
        case IRInstOperator::IRINST_OP_GT_I: return "gt"; // signed greater than
        case IRInstOperator::IRINST_OP_LT_I: return "lt"; // signed less than
        case IRInstOperator::IRINST_OP_GE_I: return "ge"; // signed greater or equal
        case IRInstOperator::IRINST_OP_LE_I: return "le"; // signed less or equal
        case IRInstOperator::IRINST_OP_EQ_I: return "eq"; // equal
        case IRInstOperator::IRINST_OP_NE_I: return "ne"; // not equal
        default: return "al"; // always (should not happen)
    }
}

// 关系运算通用实现
void InstSelectorArm64::translate_cmp(Instruction * inst, IRInstOperator op) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst->getOperand(2);
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) { lhs_reg = simpleRegisterAllocator.Allocate(); iloc.load_var(lhs_reg, lhs); }
    if (rhs_reg == -1) { rhs_reg = simpleRegisterAllocator.Allocate(); iloc.load_var(rhs_reg, rhs); }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("cmp", PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.inst("cset", PlatformArm64::regName[dst_reg], getA64Cond(op));
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

// 替换原有宏和函数
void InstSelectorArm64::translate_gt(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_GT_I); }   // 大于
void InstSelectorArm64::translate_lt(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_LT_I); }   // 小于
void InstSelectorArm64::translate_le(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_LE_I); }   // 小于等于
void InstSelectorArm64::translate_ge(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_GE_I); }   // 大于等于
void InstSelectorArm64::translate_eq(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_EQ_I); }   // 等于
void InstSelectorArm64::translate_ne(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_NE_I); }   // 不等于

// 分支指令（b.cond格式）
void InstSelectorArm64::translate_branch(Instruction * inst) {
    // 假设操作数0为条件，1为true label，2为false label
    Value * cond = inst->getOperand(0);
    Value * trueLabel = inst->getOperand(1);
    Value * falseLabel = inst->getOperand(2);
    int32_t cond_reg = cond->getRegId();
    if (cond_reg == -1) {
        cond_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(cond_reg, cond);
    }
    // 先cmp #0
    iloc.inst("cmp", PlatformArm64::regName[cond_reg], "#0");
    // b.ne trueLabel
    iloc.inst("b.ne", trueLabel->getName());
    // b falseLabel
    iloc.inst("b", falseLabel->getName());
    if (cond->getRegId() == -1) simpleRegisterAllocator.free(cond_reg);
}

// 逻辑运算
void InstSelectorArm64::translate_and(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst->getOperand(2);
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("and", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_or(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst->getOperand(2);
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("orr", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_not(Instruction * inst) {
    Value * dst = inst->getOperand(0);
    Value * src = inst->getOperand(1);
    int32_t dst_reg = dst->getRegId();
    int32_t src_reg = src->getRegId();
    if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    if (src_reg == -1) {
        src_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(src_reg, src);
    }
    iloc.inst("mvn", PlatformArm64::regName[dst_reg], PlatformArm64::regName[src_reg], "");
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (src->getRegId() == -1) simpleRegisterAllocator.free(src_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

// 函数调用
void InstSelectorArm64::translate_func_call(Instruction * inst) {
    // 假设操作数0为函数名，1~n为参数
    Value * funcVal = inst->getOperand(0);
    int n = inst->getOperandsNum();
    for (int i = 1; i < n; ++i) {
        Value * arg = inst->getOperand(i);
        int32_t reg = arg->getRegId();
        if (reg == -1) {
            reg = simpleRegisterAllocator.Allocate();
            iloc.load_var(reg, arg);
        }
        // ARM64前8个参数寄存器x0-x7
        if (i - 1 < 8) {
            iloc.inst("mov", PlatformArm64::regName[i - 1], PlatformArm64::regName[reg], "");
        } else {
            // 超过8个参数，按ABI入栈
            // 这里只做注释，实际实现需完善
            iloc.comment("TODO: 参数" + std::to_string(i) + "入栈");
        }
        if (arg->getRegId() == -1) simpleRegisterAllocator.free(reg);
    }
    iloc.inst("bl", funcVal->getIRName());
    // 返回值默认在x0
    if (n > 0) {
        Value * ret = inst->getOperand(0);
        iloc.store_var(0, ret, ARM64_TMP_REG_NO);
    }
}

// 实参
void InstSelectorArm64::translate_arg(Instruction * inst) {
    // 通常参数传递已在translate_func_call处理
    outputIRInstruction(inst);
}
