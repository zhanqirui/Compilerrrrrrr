///
/// @file BranchInstruction.h
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
#pragma once

#include <string>

#include "Instruction.h"
#include "LabelInstruction.h"
#include "Function.h"

///
/// @brief 条件分支指令
///
class BranchInstruction final : public Instruction {

public:
    ///
    /// @brief 条件分支指令的构造函数
    /// @param _func 所属的函数
    /// @param _condition 条件值
    /// @param _trueTarget 条件为真时的跳转目标
    /// @param _falseTarget 条件为假时的跳转目标
    ///
    BranchInstruction(Function * _func, Value * _condition, Instruction * _trueTarget, Instruction * _falseTarget);

    /// @brief 转换成字符串
    void toString(std::string & str) override;

    ///
    /// @brief 获取条件为真时的目标Label指令
    /// @return LabelInstruction* 真分支label指令
    ///
    [[nodiscard]] LabelInstruction * getTrueTarget() const;

    ///
    /// @brief 获取条件为假时的目标Label指令
    /// @return LabelInstruction* 假分支label指令
    ///
    [[nodiscard]] LabelInstruction * getFalseTarget() const;

private:
    ///
    /// @brief 条件为真时跳转到的目标Label指令
    ///
    LabelInstruction * trueTarget;

    ///
    /// @brief 条件为假时跳转到的目标Label指令
    ///
    LabelInstruction * falseTarget;
};