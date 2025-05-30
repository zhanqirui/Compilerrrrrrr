///
/// @file InstSelectorArm64.h
/// @brief 指令选择器-ARM64
/// @author zenglj
/// @version 1.0
/// @date 2024-11-21
///
#pragma once

#include <map>
#include <vector>
#include "Function.h"
#include "ILocArm64.h"
#include "Instruction.h"
#include "PlatformArm64.h"
#include "SimpleRegisterAllocator.h"
#include "RegVariable.h"

using namespace std;

class InstSelectorArm64 {
    std::vector<Instruction *> & ir;
    ILocArm64 & iloc;
    Function * func;

protected:
    void translate(Instruction * inst);
    void translate_nop(Instruction * inst);
    void translate_entry(Instruction * inst);
    void translate_exit(Instruction * inst);
    void translate_assign(Instruction * inst);
	void translate_load(Instruction * inst);
	void translate_gep(Instruction * inst);
	void translate_cast(Instruction * inst);
	void translate_memset(Instruction * inst);
	void translate_store(Instruction * inst);
    void translate_label(Instruction * inst);
    void translate_goto(Instruction * inst);
    void outputIRInstruction(Instruction * inst);

    // 新增：声明各算术/逻辑指令的处理函数
    void translate_add(Instruction * inst);
    void translate_sub(Instruction * inst);
    void translate_mul(Instruction * inst);
    void translate_div(Instruction * inst);
    void translate_gt(Instruction * inst);
    void translate_lt(Instruction * inst);
    void translate_le(Instruction * inst);
    void translate_ge(Instruction * inst);
    void translate_eq(Instruction * inst);
    void translate_ne(Instruction * inst);
    void translate_and(Instruction * inst);
    void translate_or(Instruction * inst);
    void translate_not(Instruction * inst);
    void translate_mod(Instruction * inst);
    void translate_branch(Instruction * inst);
    void translate_cmp(Instruction * inst, IRInstOperator op);
    void translate_func_call(Instruction * inst);
    void translate_arg(Instruction * inst);

    typedef void (InstSelectorArm64::*translate_handler)(Instruction *);
    map<IRInstOperator, translate_handler> translator_handlers;
    SimpleRegisterAllocator & simpleRegisterAllocator;
    bool showLinearIR = false;

public:
    InstSelectorArm64(std::vector<Instruction *> & _irCode,
                      ILocArm64 & _iloc,
                      Function * _func,
                      SimpleRegisterAllocator & allocator);
    ~InstSelectorArm64();
    void setShowLinearIR(bool show) { showLinearIR = show; }
    void run();
};
