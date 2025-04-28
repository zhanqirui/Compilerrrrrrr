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
