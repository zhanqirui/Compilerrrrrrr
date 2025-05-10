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

#include "BranchifCondition.h"

///

BranchifCondition::BranchifCondition(Function * _func, Value * cond, Value * label1, Value * label2)
    : Instruction(_func, IRInstOperator::IRINST_OP_BRANCH_I, VoidType::getType())
{
    addOperand(cond);
    addOperand(label1);
    addOperand(label2);
    // addOperand(_srcVal1);
}

/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void BranchifCondition::toString(std::string & str)
{

    Value *condition = getOperand(0), *l1 = getOperand(1), *l2 = getOperand(2);

    str = "bc " + condition->getIRName() + ",  " + " label " + l1->getIRName() + +"  label " + l2->getIRName();
}
