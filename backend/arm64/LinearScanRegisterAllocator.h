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

#include "PlatformArm64.h"   // 提供 maxUsableRegNum

class Value;                 // 前向声明，避免循环依赖

class LinearScanRegisterAllocator {
public:
    LinearScanRegisterAllocator();

    /**
     * @brief 为变量分配寄存器
     * @param var  需要装载到寄存器的变量；nullptr 表示仅按寄存器号分配
     * @param no   希望使用的寄存器号，-1 表示不指定
     * @return     成功返回寄存器号，失败返回 -1
     */
    int AllocateInt(Value *var = nullptr, int32_t no = -1);

    /**
     * @brief 直接标记指定寄存器为已占用（不与变量绑定）
     * @param no  寄存器号
     */
    void AllocateInt(int32_t no);

    /**
     * @brief 释放与变量绑定的寄存器
     * @param var  变量指针
     */
    void freeInt(Value *var);

    /**
     * @brief 释放指定寄存器
     * @param no  寄存器号
     */
    void freeInt(int32_t no);

    /**
     * @brief 为浮点变量分配寄存器
     * @param var  需要装载到寄存器的变量；nullptr 表示仅按寄存器号分配
     * @param no   希望使用的寄存器号，-1 表示不指定
     * @return     成功返回寄存器号，失败返回 -1
     */
    int AllocateFloat(Value *var = nullptr, int32_t no = -1);

    /**
     * @brief 直接标记指定浮点寄存器为已占用（不与变量绑定）
     * @param no  寄存器号
     */
    void AllocateFloat(int32_t no);

    /**
     * @brief 释放与变量绑定的浮点寄存器
     * @param var  变量指针
     */
    void freeFloat(Value *var);

    /**
     * @brief 释放指定浮点寄存器
     * @param no  寄存器号
     */
    void freeFloat(int32_t no);

    /**
     * @brief 统一的寄存器分配接口，根据is_float参数决定分配整数或浮点寄存器
     * @param is_float 是否分配浮点寄存器
     * @param var 需要装载到寄存器的变量
     * @param no 希望使用的寄存器号
     * @return 成功返回寄存器号，失败返回 -1
     */
    int Allocate(bool is_float = false, Value *var = nullptr, int32_t no = -1);

    /**
     * @brief 统一的寄存器分配接口（不与变量绑定）
     * @param no 寄存器号
     * @param is_float 是否为浮点寄存器
     */
    void AllocateReg(int32_t no, bool is_float = false);

    /**
     * @brief 统一的寄存器释放接口
     * @param var 变量指针
     * @param is_float 是否为浮点寄存器
     */
    void free(Value *var, bool is_float = false);

    /**
     * @brief 统一的寄存器释放接口
     * @param no 寄存器号
     * @param is_float 是否为浮点寄存器
     */
    void free(int32_t no, bool is_float = false);

    /**
     * @brief 设置当前处理的指令信息（用于调试日志）
     * @param instIdx 指令索引
     * @param instStr 指令字符串表示
     */
    void setCurrentInstruction(int instIdx, const std::string& instStr);

    /**
     * @brief 设置调试模式开关
     * @param enable 是否启用调试日志
     */
    void setDebugMode(bool enable) { debugEnabled = enable; }

    /**
     * @brief 获取调试模式状态
     * @return 当前调试模式状态
     */
    bool isDebugEnabled() const { return debugEnabled; }

    /**
     * @brief 测试调试功能是否正常工作
     */
    void testDebugFunction();

    /**
     * @brief 重置分配器状态，为新函数准备
     */
    void reset();

    /**
     * @brief 重置浮点寄存器状态
     */
    void resetFloatRegisters();

    /**
     * @brief 重置整数寄存器状态
     */
    void resetIntRegisters();

    /// 查询当前整数寄存器占用情况（调试/分析用）
    const BitMap<PlatformArm64::maxUsableRegNum>& currentIntBitmap() const { return regBitmap; }

    /// 查询整数寄存器历史使用情况（生成保存现场指令时使用）
    const BitMap<PlatformArm64::maxUsableRegNum>& everUsedIntBitmap() const { return usedBitmap; }

    /// 查询当前浮点寄存器占用情况（调试/分析用）
    const BitMap<PlatformArm64::maxUsableRegNum>& currentFloatBitmap() const { return floatRegBitmap; }

    /// 查询浮点寄存器历史使用情况（生成保存现场指令时使用）
    const BitMap<PlatformArm64::maxUsableRegNum>& everUsedFloatBitmap() const { return floatUsedBitmap; }

	/// 内部工具：在整数寄存器位图中置位
	void bitmapSet(int32_t no);

	/// 内部工具：在浮点寄存器位图中置位
	void floatBitmapSet(int32_t no);

private:

    // 整数寄存器管理
    BitMap<PlatformArm64::maxUsableRegNum> regBitmap;   //!< 当前活跃整数寄存器位图
    BitMap<PlatformArm64::maxUsableRegNum> usedBitmap;  //!< 曾经使用过的整数寄存器位图
    std::vector<Value*> regValues;                           //!< 当前活跃整数变量列表

    // 浮点寄存器管理
    BitMap<PlatformArm64::maxUsableRegNum> floatRegBitmap;   //!< 当前活跃浮点寄存器位图
    BitMap<PlatformArm64::maxUsableRegNum> floatUsedBitmap;  //!< 曾经使用过的浮点寄存器位图
    std::vector<Value*> floatRegValues;                           //!< 当前活跃浮点变量列表

    // 调试信息
    int currentInstIdx;
    std::string currentInstStr;
    bool debugEnabled;  // 调试开关
};