///
/// @file MoveInstruction.cpp
/// @brief Move指令，也就是DragonIR的Asssign指令
///
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-09-29 <td>1.0     <td>zenglj  <td>新建
/// </table>
///

#include "VoidType.h"

#include "MoveInstruction.h"

/// MOVE指令需要按照LLVM的要求改写为Store指令，现在函数头都还未调整，只让打印出来的结果跟LLVM一致

///
/// @brief 构造函数
/// @param _func 所属的函数
/// @param result 结构操作数
/// @param srcVal1 源操作数
///
MoveInstruction::MoveInstruction(Function * _func, Value * _result, Value * _srcVal1)
    : Instruction(_func, IRInstOperator::IRINST_OP_ASSIGN, VoidType::getType())
{
    addOperand(_result);
    addOperand(_srcVal1);
}

/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void MoveInstruction::toString(std::string & str)
{

    Value *dstVal = getOperand(0), *srcVal = getOperand(1);
    if (dstVal->getType() && dstVal->getType()->isPointerType()) {
        // str = '*' + dstVal->getIRName() + " = " + srcVal->getIRName();
        str = "store " + srcVal->getType()->toString() + " " + srcVal->getIRName() + ", " +
              dstVal->getType()->toString() + '*' + " " + dstVal->getIRName() + ", align 4";
        return;
    }
    if (srcVal->getType() && srcVal->getType()->isPointerType()) {
        // str = dstVal->getIRName() + " = " + '*' + srcVal->getIRName();
        str = "store " + srcVal->getType()->toString() + '*' + " " + srcVal->getIRName() + ", " +
              dstVal->getType()->toString() + " " + dstVal->getIRName() + ", align 4";
        return;
    }
    // str = dstVal->getIRName() + " = " + srcVal->getIRName();
    str = "store " + srcVal->getType()->toString() + " " + srcVal->getIRName() + ", " + dstVal->getType()->toString() +
          "*" + " " + dstVal->getIRName() + ", align 4";
}
