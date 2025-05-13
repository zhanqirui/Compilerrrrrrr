#include "MemsetInstruction.h"
#include "IntegerType.h"
#include "FloatType.h"
#include "PointerType.h"
#include "VoidType.h"
#include "BitcastInstruction.h"
#include "Function.h"
MemsetInstruction::MemsetInstruction(Function * _func, Value * dest, int8_t _value, int64_t _size, int32_t _align)
    : Instruction(_func, IRInstOperator::IRINST_OP_MEMSET, VoidType::getType()), value(_value), size(_size),
      align(_align)
{
    _func->is_use_memset = true;
    addOperand(dest);
}

void MemsetInstruction::toString(std::string & str)
{
    Value * dest = getOperand(0);
    str = "call void @llvm.memset.p0i8.i64(i8* align " + std::to_string(align) + " " + dest->getIRName() + ", i8 " +
          std::to_string(value) + ", i64 " + std::to_string(size) + ", i1 false)";
}