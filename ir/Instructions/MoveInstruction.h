///
/// @file MoveInstruction.h
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
#pragma once

#include <string>

#include "Value.h"
#include "Instruction.h"

class Function;

///
/// @brief 复制指令
///
class MoveInstruction : public Instruction {

public:
	bool is_paramReg; // 是否是参数传递的Move指令
    int offset;
    bool need_reg;
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param result 结构操作数
    /// @param srcVal1 源操作数
    ///
    MoveInstruction(Function * _func, Value * result, Value * srcVal1, bool _is_paramreg = false, int _offset = 0, bool _need_reg=false);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};
