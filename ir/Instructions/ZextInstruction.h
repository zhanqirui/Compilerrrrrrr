#pragma once

#include <string>
#include "Value.h"
#include "Instruction.h"

class Function;

///
/// @brief 零扩展指令
///
class ZextInstruction : public Instruction {
public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param srcVal1 源操作数
    /// @param dstType 目标类型
    ///
    ZextInstruction(Function * _func, Value * srcVal1, Type * dstType);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};