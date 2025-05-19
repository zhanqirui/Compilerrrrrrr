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

#include "LoadInstruction.h"

///
/// @brief 构造函数
/// @param _func 所属的函数
/// @param result 结构操作数
/// @param srcVal1 源操作数
///
LoadInstruction::LoadInstruction(Function * _func, Value * srcVal1, bool is_int)
    : Instruction(
          _func,
          IRInstOperator::IRINST_OP_LOAD,
          (is_int ? static_cast<Type *>(IntegerType::getTypeInt()) : static_cast<Type *>(FloatType::getTypeFloat())))
{
    addOperand(srcVal1);
}

/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void LoadInstruction::toString(std::string & str)
{

    Value * srcVal1 = getOperand(0);
    str = getIRName() + " = load " + getType()->toString() + ", " + getType()->toString() + "* " +
          srcVal1->getIRName() + ", align 4";
    //根据LLVM的要求，store指令的格式为
    // str = "store " + srcVal1->getType()->toString() + "* " + srcVal1->getIRName() + ", align 4";
}
