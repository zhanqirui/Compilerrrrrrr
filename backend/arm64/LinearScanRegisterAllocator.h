///
/// @file LinearScanRegisterAllocator.h
/// @brief 简单或朴素的寄存器分配器
/// @author jimmy-lpl
/// @version 1.0
/// @date 2025-05-05
///
/// @copyright Copyright (c) 2024

#pragma once

#include <bitset>
#include <vector>
#include <cstdint>
#include "BitMap.h"
#include "Value.h"

#include "PlatformArm64.h"   // 提供 maxUsableRegNum

class LinearScanRegisterAllocator {
public:
    LinearScanRegisterAllocator();

    /**
     * @brief 为变量分配寄存器
     * @param var  需要装载到寄存器的变量；nullptr 表示仅按寄存器号分配
     * @param no   希望使用的寄存器号，-1 表示不指定
     * @return     成功返回寄存器号，失败返回 -1
     */
    int Allocate(Value *var = nullptr, int32_t no = -1);

    /**
     * @brief 直接标记指定寄存器为已占用（不与变量绑定）
     * @param no  寄存器号
     */
    void Allocate(int32_t no);

    /**
     * @brief 释放与变量绑定的寄存器
     * @param var  变量指针
     */
    void free(Value *var);

    /**
     * @brief 释放指定寄存器
     * @param no  寄存器号
     */
    void free(int32_t no);

    /// 查询当前占用情况（调试/分析用）
    const std::bitset<PlatformArm64::maxUsableRegNum>& currentBitmap() const { return regBitmap; }

    /// 查询历史使用情况（生成保存现场指令时使用）
    const std::bitset<PlatformArm64::maxUsableRegNum>& everUsedBitmap() const { return usedBitmap; }

	/// 内部工具：同时在 regBitmap 与 usedBitmap 中置位
    void bitmapSet(int32_t no);

private:
    std::bitset<PlatformArm64::maxUsableRegNum> regBitmap;   // 当前活跃寄存器位图
    std::bitset<PlatformArm64::maxUsableRegNum> usedBitmap;  // 曾经使用过的寄存器位图
    std::vector<Value*> regValues;                           // 当前活跃变量列表
};