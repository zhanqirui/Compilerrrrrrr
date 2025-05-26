#pragma once

#include <string>
#include "Instruction.h"

class Function;

///
/// @brief 强制类型转换指令（如 int<->float）
///
class CastInstruction : public Instruction {
public:
    enum CastKind {
        SITOFP, // int -> float
        FPTOUI, // float -> unsigned int
        FPTOSI, // float -> int
        UITOFP  // unsigned int -> float
        // 可扩展
    };

    CastKind kind;

    CastInstruction(Function * _func, CastKind kind, Value * src, Type * dstType);

    void toString(std::string & str) override;
};