///
/// @file BranchInstruction.cpp
/// @brief 条件分支指令
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
#include "BranchInstruction.h"

///
/// @brief 条件分支指令的构造函数
/// @param _func 所属的函数
/// @param _condition 条件值
/// @param _trueTarget 条件为真时的跳转目标
/// @param _falseTarget 条件为假时的跳转目标
///
BranchInstruction::BranchInstruction(Function * _func, Value * _condition, Instruction * _trueTarget, Instruction * _falseTarget)
    : Instruction(_func, IRInstOperator::IRINST_OP_BRANCH_I, VoidType::getType())
{
    // 添加条件值作为操作数
    addOperand(_condition);
    
    // 保存真假跳转目标
    trueTarget = static_cast<LabelInstruction *>(_trueTarget);
    falseTarget = static_cast<LabelInstruction *>(_falseTarget);
}

/// @brief 转换成IR指令文本
void BranchInstruction::toString(std::string & str)
{
    Value * condition = getOperand(0);
    str = "br " + condition->getType()->toString() + " " + condition->getIRName() + ", ";
    str += "label " + trueTarget->getIRName() + ", ";
    str += "label " + falseTarget->getIRName();
}

///
/// @brief 获取条件为真时的目标Label指令
/// @return LabelInstruction* 真分支label指令
///
LabelInstruction * BranchInstruction::getTrueTarget() const
{
    return trueTarget;
}

///
/// @brief 获取条件为假时的目标Label指令
/// @return LabelInstruction* 假分支label指令
///
LabelInstruction * BranchInstruction::getFalseTarget() const
{
    return falseTarget;
}