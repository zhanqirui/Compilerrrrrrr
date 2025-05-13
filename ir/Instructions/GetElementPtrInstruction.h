#pragma once

#include <string>
#include <vector>
#include "Instruction.h"

class Function;

///
/// @brief GetElementPtr 指令
///
class GetElementPtrInstruction : public Instruction {

public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param base 基地址
    /// @param indices 偏移量索引
    ///
    int index;
    int dim;
    std::vector<int> indices;
    GetElementPtrInstruction(Function * _func, Value * basePtr, std::vector<int> indices);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};