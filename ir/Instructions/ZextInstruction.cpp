#include "ZextInstruction.h"

ZextInstruction::ZextInstruction(Function * _func, Value * srcVal1, Type * dstType)
    : Instruction(_func, IRInstOperator::IRINST_OP_ZEXT, dstType)
{
    addOperand(srcVal1);
}

void ZextInstruction::toString(std::string & str)
{
    Value * srcVal1 = getOperand(0);
    str += getIRName() +
           " = "
           "zext i1 " +
           srcVal1->getIRName() + " to i32";
}