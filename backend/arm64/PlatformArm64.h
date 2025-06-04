///
/// @file PlatformArm64.h
/// @brief  ARM64平台相关头文件
/// @author zenglj
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
#pragma once

#include <string>
#include "RegVariable.h"

#define ARM64_SAVED_REG1  19
#define ARM64_SAVED_REG2  20

// 临时寄存器
#define ARM64_TMP_REG_NO 16

// 栈寄存器SP和FP
#define ARM64_SP_REG_NO 31
#define ARM64_FP_REG_NO 29

// 链接寄存器LR
#define ARM64_LR_REG_NO 30

#define ARM64_TMP_FLOAT_REG_NO 16

/// @brief ARM64平台信息
class PlatformArm64 {

    static void roundLeftShiftTwoBit(unsigned int & num);
    static bool __constExpr(int64_t num);

public:
    static bool constExpr(int64_t num);
    static bool isDisp(int64_t num);
    static bool isReg(std::string name);
    
    // 新增：将64位寄存器名(x0-x30)转换为32位形式(w0-w30)
    static std::string toWReg(const std::string& xreg);

    static const int maxRegNum = 32; // x0-x30, sp
    static const int maxUsableRegNum = 16; // x0-x15 可用通用寄存器

    static const std::string regName[maxRegNum];
	static const std::string regNameW[maxRegNum];
    static RegVariable * intRegVal[PlatformArm64::maxRegNum];

    // 新增：浮点数寄存器支持
    static const std::string regNameS[maxRegNum]; // s0-s31
    static RegVariable * floatRegVal[PlatformArm64::maxRegNum];
};
