#pragma once

#include <string>

#include "Value.h"
#include "Instruction.h"

class Function;

///
/// @brief 加载指令（对应 LLVM 的 load）
/// 从指针地址中读取值
///
class LoadInstruction : public Instruction {

public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param result 加载目标（如 %a）
    /// @param srcPtr 加载源地址（如 *%b）
    ///
    LoadInstruction(Function * _func, Value * result, Value * srcPtr);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};
