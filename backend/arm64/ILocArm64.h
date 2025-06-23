///
/// @file ILocArm64.h
/// @brief ARM64汇编指令序列管理
/// @author zenglj
/// @version 1.0
/// @date 2024-11-21
///
#pragma once

#include <list>
#include <string>
#include "Instruction.h"
#include "Module.h"
#include "PlatformArm64.h"

#define Instanceof(res, type, var) auto res = dynamic_cast<type>(var)

struct ArmInst {
    std::string opcode, cond, result, arg1, arg2, addition;
    bool dead;
    ArmInst(std::string op, std::string rs = "", std::string s1 = "", std::string s2 = "", std::string cond = "", std::string extra = "");
    void replace(std::string op, std::string rs = "", std::string s1 = "", std::string s2 = "", std::string cond = "", std::string extra = "");
    void setDead();
    std::string outPut();
};

class ILocArm64 {
    std::list<ArmInst *> code;
    Module * module;
    void load_symbol(int rs_reg_no, std::string name);
    void leaStack(int rs_reg_no, int base_reg_no, int offset);

public:
    ILocArm64(Module * _module);
    ~ILocArm64();
    void comment(std::string str);
    std::string toStr(int64_t num, bool flag = true);
    std::list<ArmInst *> & getCode();
    void load_base_i(int rs_reg_no, int base_reg_no, int disp);
	void load_base_f(int rs_reg_no, int base_reg_no, int disp);
	void load_array_base(int rs_reg_no, int base_reg_no, int disp, bool is_param = false);
	void load_imm(int rs_reg_no, int64_t num);
    void load_imm_float(int rs_reg_no, float constant);
    void store_base_i(int src_reg_no, int base_reg_no, int disp, int tmp_reg_no);
	void store_base_f(int src_reg_no, int base_reg_no, int disp, int tmp_reg_no);
    void label(std::string name);
    void inst(std::string op, std::string rs=PlatformArm64::regName[ARM64_LR_REG_NO]);
    void inst(std::string op, std::string rs, std::string arg1);
    void inst(std::string op, std::string rs, std::string arg1, std::string arg2);
    void load_var(int rs_reg_no, Value * var, bool is_float_var=false, bool is_param = false);
    void lea_var(int rs_reg_no, Value * var);
    void store_var(int src_reg_no, Value * var, int addr_reg_no, bool is_float_var = false);
    void mov_reg(int rs_reg_no, int src_reg_no);
    void call_fun(std::string name);
    void allocStack(Function * func, int tmp_reg_No);
    void nop();
    void jump(std::string label);
    void outPut(FILE * file, bool outputEmpty = false);
    void deleteUsedLabel();

    // 新增：浮点数相关接口
    void load_var_float(int rs_reg_no, Value * var);
    void store_var_float(int src_reg_no, Value * var, int addr_reg_no);
    void mov_reg_float(int rs_reg_no, int src_reg_no);
};
