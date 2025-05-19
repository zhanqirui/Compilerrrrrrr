///
/// @file UnaryInstruction.cpp
/// @brief 单目操作符指令
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

#include "IntegerType.h"
#include "FloatType.h"

#include "UnaryInstruction.h"

///
/// @brief 构造函数
/// @param _func 所属的函数
/// @param result 结构操作数
/// @param srcVal1 源操作数
///
UnaryInstruction::UnaryInstruction(Function * _func, Value * srcVal1, bool is_int, std::string st)
    : Instruction(
          _func,
          IRInstOperator::IRINST_OP_ASSIGN,
          (is_int ? static_cast<Type *>(IntegerType::getTypeInt()) : static_cast<Type *>(FloatType::getTypeFloat())))
{
    this->st = st;
    addOperand(srcVal1);
}

/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void UnaryInstruction::toString(std::string & str)
{

    Value * srcVal1 = getOperand(0);
    str = getIRName() + " = " + this->st + " " + srcVal1->getIRName();
}
