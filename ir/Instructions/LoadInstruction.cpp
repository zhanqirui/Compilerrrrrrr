///
/// @file LoadInstruction.cpp
/// @brief Load 指令，也就是 DragonIR 中的从内存加载指令（类似 LLVM 的 load）
///
/// @author ...
/// @version 1.0
/// @date 2024-09-29
///
#include "Instruction.h"
#include "FloatType.h"

#include "LoadInstruction.h"

///
/// @brief 构造函数
/// @param _func 所属的函数
/// @param result 加载目标
/// @param srcPtr 内存地址源
///
LoadInstruction::LoadInstruction(Function * _func, Value * result, Value * srcPtr)
    : Instruction(_func,
                  IRInstOperator::IRINST_OP_LOAD,
                  result->getType() // 加载类型与目标相同
      )
{
    addOperand(result); // 第一个操作数是目的变量
    addOperand(srcPtr); // 第二个是地址源（指针）
}

///
/// @brief 转换成字符串
/// @param str 输出字符串
///
void LoadInstruction::toString(std::string & str)
{
    Value * result = getOperand(0);
    Value * srcPtr = getOperand(1);

    // 类似 LLVM IR: %result = load i32, i32* %srcPtr, align 4
    str = result->getIRName() + " = load " + result->getType()->toString() + ", " + result->getType()->toString() +
          "* " + srcPtr->getIRName() + ", align 4";
}
