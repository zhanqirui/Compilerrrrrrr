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
    void translate_label(Instruction * inst);
    void translate_goto(Instruction * inst);
    void outputIRInstruction(Instruction * inst);

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
