///
/// @file MoveInstruction.cpp
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

#include "IntegerType.h"
#include "FloatType.h"
#include "PointerType.h"
#include "BitcastInstruction.h"

///
/// @brief 构造函数
/// @param _func 所属的函数
/// @param result 结构操作数
/// @param srcVal1 源操作数
///
BitcastInstruction::BitcastInstruction(Function * _func, Value * srcVal1, int bit = 8)
    : Instruction(_func, IRInstOperator::IRINST_OP_ASSIGN, (static_cast<Type *>(IntegerType::getTypeInt())))
//   (is_int ? static_cast<Type *>(IntegerType::getTypeInt()) : static_cast<Type *>(FloatType::getTypeFloat())))
{
    addOperand(srcVal1);
    this->bit = bit;
}

/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void BitcastInstruction::toString(std::string & str)
{
    // 获取操作数
    Value * srcVal1 = getOperand(0);
    std::string arrayType = "";
    // 构造 bitcast 指令的字符串

    const std::vector<int32_t> dims = srcVal1->arraydimensionVector;
    if (!dims.empty()) {
        for (auto it = dims.begin(); it != dims.end(); ++it) {
            arrayType += "[" + std::to_string(*it) + " x ";
        }
        Type * baseType = srcVal1->getType(); // 获取类型
        PointerType * pointerType = dynamic_cast<PointerType *>(baseType);
        arrayType += pointerType->getRootType()->toString();
        for (size_t i = 0; i < dims.size(); ++i) {
            arrayType += "]";
        }
    }
    str = getIRName() + " = bitcast " + arrayType + "* " + srcVal1->getIRName() + " to i" + std::to_string(bit) + "*";
}