///
/// @file ArgInstruction.cpp
/// @brief 函数调用前的实参指令
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
#include <string>
#include "AdjsutStack.h"
#include "Function.h"
#include "VoidType.h"

/// @brief 函数实参指令
/// @param target 跳转目标
AdjustStackInstruction::AdjustStackInstruction(int _size)
	: Instruction(nullptr, IRInstOperator::IRINST_OP_ADJUSTSTACK, VoidType::getType()), size(_size)
{
}

/// @brief 转换成字符串
void AdjustStackInstruction::toString(std::string & str)
{
    return;
}
