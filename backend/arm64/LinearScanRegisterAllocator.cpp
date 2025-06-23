///
/// @file LinearScanRegisterAllocator.cpp
/// @brief 基于线性扫描的寄存器分配器
/// @author jimmy-lpl
/// @version 1.0
/// @date 2025-05-05
///
/// @copyright Copyright (c) 2024
///

#include <algorithm>
#include <climits>
#include "LinearScanRegisterAllocator.h"

LinearScanRegisterAllocator::LinearScanRegisterAllocator()
{}

int LinearScanRegisterAllocator::Allocate(Value *var, int32_t no)
{
    if (var && (var->getLoadRegId() != -1)) {
        return var->getLoadRegId();
    }

    int32_t regno = -1;

    // 尝试分配指定寄存器
    if ((no != -1) && !regBitmap.test(no)) {
        regno = no;
    } else {
        // 查找空闲寄存器
        for (int k = 0; k < PlatformArm64::maxUsableRegNum; ++k) {
            if (!regBitmap.test(k)) {
                regno = k;
                break;
            }
        }
    }

    if (regno == -1) {
        // 需要溢出：选择活跃结束最早的变量
        Value *spillVar = nullptr;
        int earliestEnd = INT_MAX;

        for (auto *v : regValues) {
            if (v->getLiveEnd() < earliestEnd) {
                earliestEnd = v->getLiveEnd();
                spillVar = v;
            }
        }

        if (spillVar) {
            regno = spillVar->getLoadRegId();
            spillVar->setLoadRegId(-1);
            regValues.erase(std::remove(regValues.begin(), regValues.end(), spillVar), regValues.end());
            regBitmap.reset(regno);
        }
    }

    if (regno != -1) {
        bitmapSet(regno);
        if (var) {
            var->setLoadRegId(regno);
            regValues.push_back(var);
        }
    }

    return regno;
}

void LinearScanRegisterAllocator::Allocate(int32_t no)
{
    if (regBitmap.test(no)) {
        free(no);
    }
    bitmapSet(no);
}

void LinearScanRegisterAllocator::free(Value *var)
{
    if (var && var->getLoadRegId() != -1) {
        regBitmap.reset(var->getLoadRegId());
        regValues.erase(std::remove(regValues.begin(), regValues.end(), var), regValues.end());
        var->setLoadRegId(-1);
    }
}

void LinearScanRegisterAllocator::free(int32_t no)
{
    if (no == -1) return;

    regBitmap.reset(no);
    auto it = std::find_if(regValues.begin(), regValues.end(), [no](Value *v) {
        return v->getLoadRegId() == no;
    });

    if (it != regValues.end()) {
        (*it)->setLoadRegId(-1);
        regValues.erase(it);
    }
}

void LinearScanRegisterAllocator::bitmapSet(int32_t no)
{
    regBitmap.set(no);
    usedBitmap.set(no);
}