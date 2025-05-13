#include "MemcpyInstruction.h"
#include "IntegerType.h"
#include "FloatType.h"
#include "PointerType.h"
#include "BitcastInstruction.h"
#include "VoidType.h"
#include "Function.h"
MemcpyInstruction::MemcpyInstruction(Function * _func, Value * dest, Value * src, int64_t _size, int32_t _align)
    : Instruction(_func, IRInstOperator::IRINST_OP_MEMCPY, VoidType::getType()), size(_size), align(_align)
{
    _func->is_use_memcpy = true;
    addOperand(dest);
    addOperand(src);
}

void MemcpyInstruction::toString(std::string & str)
{
    std::string arrayType = "";
    Value * dest = getOperand(0);
    Value * src = getOperand(1);
    const std::vector<int32_t> dims = src->arraydimensionVector;
    if (!dims.empty()) {
        for (auto it = dims.begin(); it != dims.end(); ++it) {
            arrayType += "[" + std::to_string(*it) + " x ";
        }
        Type * baseType = src->getType(); // 获取类型
        PointerType * pointerType = dynamic_cast<PointerType *>(baseType);
        arrayType += pointerType->getRootType()->toString();
        for (size_t i = 0; i < dims.size(); ++i) {
            arrayType += "]";
        }
    }
    str = "call void @llvm.memcpy.p0i8.p0i8.i64(i8* align " + std::to_string(align) + " " + dest->getIRName() +
          ", i8* align " + std::to_string(align) + " bitcast (" + arrayType + "* " + src->getIRName() +
          " to i8*), i64 " + std::to_string(size) + ", i1 false)";
}