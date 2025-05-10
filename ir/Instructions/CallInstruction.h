///
/// @file CallInstruction.h
/// @brief 函数调用指令（简化版FuncCallInstruction）
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

class Function;

///
/// @brief 函数调用指令（简化版）
///
class CallInstruction : public Instruction {

public:
    ///
    /// @brief 函数调用时的被调用函数
    ///
    Function * calledFunction = nullptr;

public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param calledFunc 被调用的函数
    /// @param result 保存返回值的Value
    ///
    CallInstruction(Function * _func, Function * calledFunc, Value * result = nullptr);

    ///
    /// @brief 转换成IR指令文本
    /// @param str IR指令
    ///
    void toString(std::string & str) override;

    ///
    /// @brief 获取被调用函数的名字
    /// @return std::string 被调用函数名字
    ///
    [[nodiscard]] std::string getCalledName() const;
};