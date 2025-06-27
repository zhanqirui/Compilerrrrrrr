///
/// @file AdjustStackInstruction.h
/// @brief 栈分配指令
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
#pragma once

#include "Instruction.h"

///
/// @brief 栈分配指令
///
class AdjustStackInstruction : public Instruction {

public:
    int size;
    /// @brief 函数实参指令
    /// @param src 实参结果变量
    AdjustStackInstruction(int _size);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};
