#pragma once

#include <string>
#include "Instruction.h"

class Function;

///
/// @brief Memset 指令
///
class MemsetInstruction : public Instruction {

public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param dest 目标地址
    /// @param value 填充值
    /// @param size 填充大小
    /// @param align 对齐方式
    ///
    MemsetInstruction(Function * _func, Value * dest, int8_t value, int64_t size, int32_t align);

    /// @brief 转换成字符串
    void toString(std::string & str) override;

	int64_t getSize() const
	{
		return size;
	}

private:
    int8_t value;
    int64_t size;
    int32_t align;
};