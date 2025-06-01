#pragma once

#include <string>

#include "Value.h"
#include "Instruction.h"

class Function;

///
/// @brief 复制指令
///
class BitcastInstruction : public Instruction {

public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param result 结构操作数
    /// @param srcVal1 源操作数
    ///
    int bit;
    bool is_int = true;
    BitcastInstruction(Function * _func, Value * srcVal1, int bit);
    BitcastInstruction(Function * _func, Value * srcVal1, int bit, bool is_int);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};
