///
/// @file ArgInstruction.cpp
/// @brief 函数调用前的实参指令
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
#include <string>
#include "ArgInstruction.h"
#include "Function.h"
#include "VoidType.h"

/// @brief 函数实参指令构造函数
/// @param _func 所属函数
/// @param src 实参值
ArgInstruction::ArgInstruction(Function * _func, Value * src)
    : Instruction(_func, IRInstOperator::IRINST_OP_ARG, VoidType::getType())
{
    this->addOperand(src);
}

/// @brief 转换成字符串
/// @details 将ARG指令转换为字符串形式，如果参数有寄存器分配或内存地址，则添加为注释
void ArgInstruction::toString(std::string & str)
{
    int32_t regId;
    int64_t offset;
    Value * src = getOperand(0);

    str = "arg " + src->getIRName();

    if (src->getRegId() != -1) {
        str += " ; " + std::to_string(src->getRegId());
    } else if (src->getMemoryAddr(&regId, &offset)) {
        str += " ; " + std::to_string(regId) + "[" + std::to_string(offset) + "]";
    }

    // ARG指令个数增加1
    func->realArgCountInc();
}
