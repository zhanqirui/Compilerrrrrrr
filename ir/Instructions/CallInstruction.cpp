///
/// @file CallInstruction.cpp
/// @brief 函数调用指令（简化版FuncCallInstruction）
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
#include "CallInstruction.h"
#include "Function.h"

///
/// @brief 构造函数
/// @param _func 所属的函数
/// @param calledFunc 被调用的函数
/// @param result 保存返回值的Value
///
CallInstruction::CallInstruction(Function * _func, Function * calledFunc, Value * result)
    : Instruction(_func, IRInstOperator::IRINST_OP_FUNC_CALL, result ? result->getType() : calledFunc->getReturnType()), calledFunction(calledFunc)
{
    // 保存函数名
    name = calledFunc->getName();

    // 如果有结果值，将其作为操作数添加
    if (result) {
        addOperand(result);
    }
}

///
/// @brief 转换成IR指令文本
/// @param str IR指令
///
void CallInstruction::toString(std::string & str)
{
    // 如果函数返回类型是void
    if (type->isVoidType()) {
        // 函数没有返回值设置
        str = "call void " + calledFunction->getIRName() + "()";
    } else {
        // 函数有返回值
        str = type->toString() + " " + getIRName() + " = call i32 " + calledFunction->getIRName() + "()";
    }
}

///
/// @brief 获取被调用函数的名字
/// @return std::string 被调用函数名字
///
std::string CallInstruction::getCalledName() const
{
    return calledFunction->getName();
}