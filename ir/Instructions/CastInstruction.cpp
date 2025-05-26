#include "CastInstruction.h"

CastInstruction::CastInstruction(Function * _func, CastKind kind, Value * src, Type * dstType)
    : Instruction(_func, IRInstOperator::IRINST_OP_CAST, dstType), kind(kind)
{
    addOperand(src);
}

void CastInstruction::toString(std::string & str)
{
    Value * src = getOperand(0);
    std::string op;
    switch (kind) {
        case SITOFP:
            op = "sitofp";
            break;
        case FPTOUI:
            op = "fptoui";
            break;
        case FPTOSI:
            op = "fptosi";
            break;
        case UITOFP:
            op = "uitofp";
            break;
        default:
            op = "cast";
            break;
    }
    str = getIRName() + " = " + op + " " + src->getType()->toString() + " " + src->getIRName() + " to " +
          type->toString();
}