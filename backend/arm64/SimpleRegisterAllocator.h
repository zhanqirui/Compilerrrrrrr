///
/// @file SimpleRegisterAllocator.h
/// @brief 简单或朴素的寄存器分配器（ARM64）
/// @author zenglj
/// @version 1.0
/// @date 2024-11-21
///
#pragma once

#include <vector>
#include "BitMap.h"
#include "Value.h"
#include "PlatformArm64.h"

class SimpleRegisterAllocator {

public:
    SimpleRegisterAllocator();

    int Allocate(Value * var = nullptr, int32_t no = -1);
    void Allocate(int32_t no);
    void free(Value * var);
    void free(int32_t);

protected:
    void bitmapSet(int32_t no);

protected:
    BitMap<PlatformArm64::maxUsableRegNum> regBitmap;
    std::vector<Value *> regValues;
    BitMap<PlatformArm64::maxUsableRegNum> usedBitmap;
};
