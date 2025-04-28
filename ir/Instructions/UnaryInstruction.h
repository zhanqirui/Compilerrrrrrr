///
/// @file MoveInstruction.h
/// @brief 为了处理这种情况专门设计的指令。%t31 = *%t30
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

#include <string>

#include "Value.h"
#include "Instruction.h"

class Function;

///
/// @brief 复制指令
///
class UnaryInstruction : public Instruction {

public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param result 结构操作数
    /// @param srcVal1 源操作数
    ///
    std::string st;
    UnaryInstruction(Function * _func, Value * srcVal1, bool is_int, std::string st);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};
