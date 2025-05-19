#pragma once

#include <string>
#include "Instruction.h"

class Function;

///
/// @brief Memcpy 指令
///
class MemcpyInstruction : public Instruction {

public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param dest 目标地址
    /// @param src 源地址
    /// @param size 拷贝大小
    /// @param align 对齐方式
    ///
    MemcpyInstruction(Function * _func, Value * dest, Value * src, int64_t size, int32_t align);

    /// @brief 转换成字符串
    void toString(std::string & str) override;

private:
    int64_t size;
    int32_t align;
};