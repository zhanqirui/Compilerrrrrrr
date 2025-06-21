///
/// @file SimpleRegisterAllocator.h
/// @brief 简单或朴素的寄存器分配器（ARM64）
/// @author zenglj
/// @version 1.0
/// @date 2024-11-21
///
#pragma once

#include <vector>
#include <iostream>
#include "BitMap.h"
#include "Value.h"
#include "PlatformArm64.h"

class SimpleRegisterAllocator {

public:
    SimpleRegisterAllocator();

    int AllocateInt(Value * var = nullptr, int32_t no = -1);
    void AllocateInt(int32_t no);
    void freeInt(Value * var);
    void freeInt(int32_t);
    void bitmapSet(int32_t no);

    // 新增：浮点数寄存器分配与释放接口
    int AllocateFloat(Value * var = nullptr, int32_t no = -1);
    void AllocateFloat(int32_t no);
    void freeFloat(Value * var);
    void freeFloat(int32_t);
    void floatBitmapSet(int32_t no);

	void free(Value * var, bool is_float=false);
	void free(int32_t, bool is_float=false);

	int Allocate(bool is_float=false, Value * var = nullptr, int32_t no = -1);
    void AllocateReg(int32_t no, bool is_float=false);

protected:
    BitMap<PlatformArm64::maxUsableRegNum> regBitmap;
    std::vector<Value *> regValues;
    BitMap<PlatformArm64::maxUsableRegNum> usedBitmap;

    // 新增：浮点数寄存器分配状态
    BitMap<PlatformArm64::maxUsableRegNum> floatRegBitmap;
    std::vector<Value *> floatRegValues;
    BitMap<PlatformArm64::maxUsableRegNum> floatUsedBitmap;
};
