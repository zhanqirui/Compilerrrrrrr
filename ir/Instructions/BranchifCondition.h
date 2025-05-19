///
/// @file BranchifCondition.h
/// @brief 条件跳转指令，
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
class BranchifCondition : public Instruction {

public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param cond 跳转条件
    /// @param label1
    /// @param label2
    ///
    BranchifCondition(Function * _func, Value * cond, Value * label1, Value * label2);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};
