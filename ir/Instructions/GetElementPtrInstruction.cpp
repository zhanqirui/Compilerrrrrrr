#pragma once

#include <string>
#include <vector>
#include "Instruction.h"
#include "GetElementPtrInstruction.h"
#include "IntegerType.h"
#include "PointerType.h"
///
/// @brief GetElementPtr 指令
///
GetElementPtrInstruction::GetElementPtrInstruction(Function * _func, Value * basePtr, Value * offset)
    : Instruction(_func, IRInstOperator::IRINST_OP_GEP, basePtr->getType())
{
    addOperand(basePtr);
    addOperand(offset);
}
void GetElementPtrInstruction::toString(std::string & str)
{

    Value * srcVal1 = getOperand(0);
    Value * srcVal2 = getOperand(1);
    std::string arrayType = "";
    // 构造 bitcast 指令的字符串

    const std::vector<int32_t> dims = srcVal1->arraydimensionVector;
    if (!dims.empty()) {
        for (auto it = dims.begin(); it != dims.end(); ++it) {
            arrayType += "[" + std::to_string(*it) + " x ";
        }
        Type * baseType = srcVal1->getType(); // 获取类型
        PointerType * pointerType = dynamic_cast<PointerType *>(baseType);
        arrayType += pointerType->getRootType()->toString();
        for (auto it = dims.begin(); it != dims.end(); ++it) {
            arrayType += "]";
        }
    } else {
        arrayType = "i32";
    }
    str = getIRName() + " = getelementptr inbounds " + arrayType + ", " + arrayType + "* " + srcVal1->getIRName() +
          ", i32 " + srcVal2->getIRName();
    // if (indices.size() == 1) {
    //     str = getIRName() + " = getelementptr inbounds " + arrayType + ", " + arrayType + "* " + srcVal1->getIRName()
    //     +
    //           ", i64 " + std::to_string(indices[0]);
    // } else {
    //     str = getIRName() + " = getelementptr inbounds " + arrayType + ", " + arrayType + "* " + srcVal1->getIRName()
    //     +
    //           ", i64 0";
    //     for (size_t i = 0; i < indices.size(); ++i) {
    //         str += ", i64 " + std::to_string(indices[i]);
    //     }
    // }
}
