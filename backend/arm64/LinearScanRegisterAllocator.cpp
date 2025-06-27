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
#include <fstream>
#include <ctime>
#include "LinearScanRegisterAllocator.h"

// 调试日志文件 - 修改为清空模式
static std::ofstream debugLog;

LinearScanRegisterAllocator::LinearScanRegisterAllocator()
{
    // 以清空模式打开日志文件，这样每次运行都会清空之前的日志
    if (debugLog.is_open()) {
        debugLog.close();
    }
    
    debugLog.open("/home/rui/minic_test/register_allocator_debug.log", std::ios::out | std::ios::trunc);
    // 写入时间戳
    std::time_t now = std::time(0);
    debugLog << "=== LinearScanRegisterAllocator initialized at " << std::ctime(&now);
    debugLog.flush();
    
    // 初始化调试信息
    currentInstIdx = -1;
    currentInstStr = "";
    debugEnabled = false;  // 默认关闭调试
}

int LinearScanRegisterAllocator::AllocateInt(Value *var, int32_t no)
{
    if (!debugEnabled) {
        // 简化版本，不输出调试信息
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
            // 需要溢出：根据线性扫描算法选择合适的变量
            if (regValues.empty()) {
                return -1;
            }
            
            Value *spillVar = nullptr;
            int earliestEnd = INT_MAX;

            if (!var) {
                // 临时分配：选择结束最早的变量
                for (auto *v : regValues) {
                    if (v->getLiveEnd() < earliestEnd) {
                        earliestEnd = v->getLiveEnd();
                        spillVar = v;
                    }
                }
            } else {
                // 有具体变量：选择结束最早且早于当前变量开始的变量
                for (auto *v : regValues) {
                    if (v->getLiveEnd() < earliestEnd && v->getLiveEnd() <= var->getLiveBegin()) {
                        earliestEnd = v->getLiveEnd();
                        spillVar = v;
                    }
                }
                
                if (!spillVar) {
                    return -1;
                }
            }

            if (spillVar && spillVar->getLoadRegId() != -1) {
                regno = spillVar->getLoadRegId();
                spillVar->setLoadRegId(-1);
                regValues.erase(std::remove(regValues.begin(), regValues.end(), spillVar), regValues.end());
                regBitmap.reset(regno);
            } else {
                return -1;
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

    // 调试模式：输出详细信息
    // 记录当前指令信息
    if (currentInstIdx != -1 && !currentInstStr.empty()) {
        debugLog << "=== INSTRUCTION [" << currentInstIdx << "] ===" << std::endl;
        debugLog << "INST: " << currentInstStr << std::endl;
    }
    
    debugLog << "DEBUG: AllocateInt called - var=" << var << ", requested_reg=" << no << std::endl;
    
    // 添加状态一致性检查
    debugLog << "DEBUG: Performing consistency check..." << std::endl;
    for (int i = 0; i < PlatformArm64::maxUsableRegNum; ++i) {
        bool bitmapOccupied = regBitmap.test(i);
        bool hasActiveVar = false;
        Value* activeVar = nullptr;
        
        for (auto* v : regValues) {
            if (v->getLoadRegId() == i) {
                hasActiveVar = true;
                activeVar = v;
                break;
            }
        }
        
        if (bitmapOccupied && !hasActiveVar) {
            debugLog << "DEBUG: INCONSISTENCY - Register " << i << " marked as occupied but no active variable" << std::endl;
        } else if (!bitmapOccupied && hasActiveVar) {
            debugLog << "DEBUG: INCONSISTENCY - Register " << i << " has active variable " << activeVar << " but not marked as occupied" << std::endl;
        }
    }
    
    if (var && (var->getLoadRegId() != -1)) {
        debugLog << "DEBUG: Variable already has register " << var->getLoadRegId() << std::endl;
        return var->getLoadRegId();
    }

    int32_t regno = -1;

    // 打印当前状态
    debugLog << "DEBUG: Current int register bitmap: ";
    for (int i = 0; i < PlatformArm64::maxUsableRegNum; ++i) {
        debugLog << (regBitmap.test(i) ? "1" : "0");
    }
    debugLog << std::endl;
    debugLog << "DEBUG: Active int variables count: " << regValues.size() << std::endl;
    for (size_t i = 0; i < regValues.size(); ++i) {
        debugLog << "DEBUG: Active var[" << i << "]: " << regValues[i] 
                 << ", reg=" << regValues[i]->getLoadRegId() 
                 << ", liveEnd=" << regValues[i]->getLiveEnd() << std::endl;
    }

    // 尝试分配指定寄存器
    if ((no != -1) && !regBitmap.test(no)) {
        regno = no;
        debugLog << "DEBUG: Allocated requested register " << regno << std::endl;
    } else {
        // 查找空闲寄存器
        for (int k = 0; k < PlatformArm64::maxUsableRegNum; ++k) {
            if (!regBitmap.test(k)) {
                regno = k;
                debugLog << "DEBUG: Found free register " << regno << std::endl;
                break;
            }
        }
    }

    if (regno == -1) {
        debugLog << "DEBUG: No free registers, need to spill" << std::endl;
        
        // 需要溢出：根据线性扫描算法选择合适的变量
        if (regValues.empty()) {
            // 没有活跃变量，但所有寄存器都被占用，这种情况不应该发生
            debugLog << "ERROR: No active variables but all registers occupied - state inconsistency!" << std::endl;
            debugLog << "DEBUG: Checking bitmap vs active list mismatch:" << std::endl;
            for (int i = 0; i < PlatformArm64::maxUsableRegNum; ++i) {
                if (regBitmap.test(i)) {
                    debugLog << "DEBUG: Register " << i << " is marked as occupied but no active variable found" << std::endl;
                }
            }
            debugLog.flush();
            return -1;
        }
        
        Value *spillVar = nullptr;
        int earliestEnd = INT_MAX;

        // 对于var为空的情况（临时寄存器分配），选择结束最早的变量溢出
        // 对于var不为空的情况，需要比较生存期
        if (!var) {
            debugLog << "DEBUG: Temporary allocation - finding earliest ending variable" << std::endl;
            // 临时分配：选择结束最早的变量
            for (auto *v : regValues) {
                if (v->getLiveEnd() < earliestEnd) {
                    earliestEnd = v->getLiveEnd();
                    spillVar = v;
                }
            }
            if (spillVar) {
                debugLog << "DEBUG: Selected spill candidate (temp): " << spillVar 
                         << ", reg=" << spillVar->getLoadRegId() 
                         << ", liveEnd=" << spillVar->getLiveEnd() << std::endl;
            }
        } else {
            debugLog << "DEBUG: Variable allocation - var liveBegin=" << var->getLiveBegin() 
                     << ", liveEnd=" << var->getLiveEnd() << std::endl;
            // 有具体变量：选择结束最早且早于当前变量开始的变量
            for (auto *v : regValues) {
                debugLog << "DEBUG: Checking spill candidate: " << v 
                         << ", reg=" << v->getLoadRegId() 
                         << ", liveEnd=" << v->getLiveEnd() << std::endl;
                if (v->getLiveEnd() < earliestEnd && v->getLiveEnd() <= var->getLiveBegin()) {
                    earliestEnd = v->getLiveEnd();
                    spillVar = v;
                    debugLog << "DEBUG: New best spill candidate: " << spillVar << std::endl;
                }
            }
            
            // 如果没找到合适的溢出变量，说明当前变量与所有已分配变量生存期重叠
            // 根据线性扫描算法，应该拒绝分配
            if (!spillVar) {
                debugLog << "WARNING: Cannot allocate register due to live range conflicts - all active variables overlap with requested variable" << std::endl;
                debugLog.flush();
                return -1;
            }
        }

        if (spillVar && spillVar->getLoadRegId() != -1) {
            regno = spillVar->getLoadRegId();
            debugLog << "DEBUG: Spilling variable " << spillVar << " from register " << regno << std::endl;
            spillVar->setLoadRegId(-1);
            regValues.erase(std::remove(regValues.begin(), regValues.end(), spillVar), regValues.end());
            regBitmap.reset(regno);
        } else {
            debugLog << "ERROR: No valid spillable variable found - spillVar=" << spillVar << std::endl;
            if (spillVar) {
                debugLog << "DEBUG: spillVar regId=" << spillVar->getLoadRegId() << std::endl;
            }
            debugLog.flush();
            return -1;
        }
    }

    if (regno != -1) {
        debugLog << "DEBUG: Final allocation: register " << regno << std::endl;
        bitmapSet(regno);
        if (var) {
            var->setLoadRegId(regno);
            regValues.push_back(var);
            debugLog << "DEBUG: Variable " << var << " assigned to register " << regno << std::endl;
        } else {
            debugLog << "DEBUG: Temporary register " << regno << " allocated" << std::endl;
        }
    }

    debugLog << "DEBUG: AllocateInt finished - returned register " << regno << std::endl << std::endl;
    debugLog.flush();
    return regno;
}

void LinearScanRegisterAllocator::AllocateInt(int32_t no)
{
    if (regBitmap.test(no)) {
        freeInt(no);
    }
    bitmapSet(no);
}

void LinearScanRegisterAllocator::freeInt(Value *var)
{
    if (debugEnabled) {
        debugLog << "DEBUG: freeInt(Value*) called - var=" << var;
    }
    
    if (var && var->getLoadRegId() != -1) {
        int regId = var->getLoadRegId();
        if (debugEnabled) {
            debugLog << ", releasing register " << regId << std::endl;
        }
        regBitmap.reset(var->getLoadRegId());
        regValues.erase(std::remove(regValues.begin(), regValues.end(), var), regValues.end());
        var->setLoadRegId(-1);
        if (debugEnabled) {
            debugLog << "DEBUG: Register " << regId << " freed successfully" << std::endl;
        }
    } else {
        if (debugEnabled) {
            debugLog << ", no register to free (regId=" << (var ? var->getLoadRegId() : -2) << ")" << std::endl;
        }
    }
    
    if (debugEnabled) {
        debugLog << std::endl;
        debugLog.flush();
    }
}

void LinearScanRegisterAllocator::freeInt(int32_t no)
{
    if (debugEnabled) {
        debugLog << "DEBUG: freeInt(int32_t) called - register=" << no;
    }
    
    if (no == -1) {
        if (debugEnabled) {
            debugLog << ", invalid register number" << std::endl;
        }
        return;
    }

    if (debugEnabled) {
        debugLog << std::endl;
    }
    
    regBitmap.reset(no);
    auto it = std::find_if(regValues.begin(), regValues.end(), [no](Value *v) {
        return v->getLoadRegId() == no;
    });

    if (it != regValues.end()) {
        if (debugEnabled) {
            debugLog << "DEBUG: Found variable " << *it << " using register " << no << ", removing from active list" << std::endl;
        }
        (*it)->setLoadRegId(-1);
        regValues.erase(it);
    } else {
        if (debugEnabled) {
            debugLog << "DEBUG: No variable found using register " << no << " in active list" << std::endl;
        }
    }
    
    if (debugEnabled) {
        debugLog << "DEBUG: Register " << no << " freed" << std::endl;
		debugLog << std::endl;
        debugLog.flush();
    }
}

int LinearScanRegisterAllocator::AllocateFloat(Value *var, int32_t no)
{
    if (!debugEnabled) {
        // 简化版本，不输出调试信息
        if (var && (var->getLoadRegId() != -1)) {
            return var->getLoadRegId();
        }

        int32_t regno = -1;

        // 尝试分配指定寄存器
        if ((no != -1) && !floatRegBitmap.test(no)) {
            regno = no;
        } else {
            // 查找空闲寄存器
            for (int k = 0; k < PlatformArm64::maxUsableRegNum; ++k) {
                if (!floatRegBitmap.test(k)) {
                    regno = k;
                    break;
                }
            }
        }

        if (regno == -1) {
            // 需要溢出：根据线性扫描算法选择合适的变量
            if (floatRegValues.empty()) {
                return -1;
            }
            
            Value *spillVar = nullptr;
            int earliestEnd = INT_MAX;

            if (!var) {
                // 临时分配：选择结束最早的变量
                for (auto *v : floatRegValues) {
                    if (v->getLiveEnd() < earliestEnd) {
                        earliestEnd = v->getLiveEnd();
                        spillVar = v;
                    }
                }
            } else {
                // 有具体变量：选择结束最早且早于当前变量开始的变量
                for (auto *v : floatRegValues) {
                    if (v->getLiveEnd() < earliestEnd && v->getLiveEnd() <= var->getLiveBegin()) {
                        earliestEnd = v->getLiveEnd();
                        spillVar = v;
                    }
                }
                
                if (!spillVar) {
                    return -1;
                }
            }

            if (spillVar && spillVar->getLoadRegId() != -1) {
                regno = spillVar->getLoadRegId();
                spillVar->setLoadRegId(-1);
                floatRegValues.erase(std::remove(floatRegValues.begin(), floatRegValues.end(), spillVar), floatRegValues.end());
                floatRegBitmap.reset(regno);
            } else {
                return -1;
            }
        }

        if (regno != -1) {
            floatBitmapSet(regno);
            if (var) {
                var->setLoadRegId(regno);
                floatRegValues.push_back(var);
            }
        }

        return regno;
    }

    // 调试模式：输出详细信息
    // 记录当前指令信息
    if (currentInstIdx != -1 && !currentInstStr.empty()) {
        debugLog << "=== INSTRUCTION [" << currentInstIdx << "] ===" << std::endl;
        debugLog << "INST: " << currentInstStr << std::endl;
    }
    
    debugLog << "DEBUG: AllocateFloat called - var=" << var << ", requested_reg=" << no << std::endl;
    
    // 添加状态一致性检查
    debugLog << "DEBUG: Performing consistency check..." << std::endl;
    for (int i = 0; i < PlatformArm64::maxUsableRegNum; ++i) {
        bool bitmapOccupied = floatRegBitmap.test(i);
        bool hasActiveVar = false;
        Value* activeVar = nullptr;
        
        for (auto* v : floatRegValues) {
            if (v->getLoadRegId() == i) {
                hasActiveVar = true;
                activeVar = v;
                break;
            }
        }
        
        if (bitmapOccupied && !hasActiveVar) {
            debugLog << "DEBUG: INCONSISTENCY - Register " << i << " marked as occupied but no active variable" << std::endl;
        } else if (!bitmapOccupied && hasActiveVar) {
            debugLog << "DEBUG: INCONSISTENCY - Register " << i << " has active variable " << activeVar << " but not marked as occupied" << std::endl;
        }
    }
    
    if (var && (var->getLoadRegId() != -1)) {
        debugLog << "DEBUG: Variable already has register " << var->getLoadRegId() << std::endl;
        return var->getLoadRegId();
    }

    int32_t regno = -1;

    // 打印当前状态
    debugLog << "DEBUG: Current float register bitmap: ";
    for (int i = 0; i < PlatformArm64::maxUsableRegNum; ++i) {
        debugLog << (floatRegBitmap.test(i) ? "1" : "0");
    }
    debugLog << std::endl;
    debugLog << "DEBUG: Active float variables count: " << floatRegValues.size() << std::endl;
    for (size_t i = 0; i < floatRegValues.size(); ++i) {
        debugLog << "DEBUG: Active var[" << i << "]: " << floatRegValues[i] 
                 << ", reg=" << floatRegValues[i]->getLoadRegId() 
                 << ", liveEnd=" << floatRegValues[i]->getLiveEnd() << std::endl;
    }

    // 尝试分配指定寄存器
    if ((no != -1) && !floatRegBitmap.test(no)) {
        regno = no;
        debugLog << "DEBUG: Allocated requested register " << regno << std::endl;
    } else {
        // 查找空闲寄存器
        for (int k = 0; k < PlatformArm64::maxUsableRegNum; ++k) {
            if (!floatRegBitmap.test(k)) {
                regno = k;
                debugLog << "DEBUG: Found free register " << regno << std::endl;
                break;
            }
        }
    }

    if (regno == -1) {
        debugLog << "DEBUG: No free registers, need to spill" << std::endl;
        
        // 需要溢出：根据线性扫描算法选择合适的变量
        if (floatRegValues.empty()) {
            // 没有活跃变量，但所有寄存器都被占用，这种情况不应该发生
            debugLog << "ERROR: No active variables but all registers occupied - state inconsistency!" << std::endl;
            debugLog << "DEBUG: Checking bitmap vs active list mismatch:" << std::endl;
            for (int i = 0; i < PlatformArm64::maxUsableRegNum; ++i) {
                if (floatRegBitmap.test(i)) {
                    debugLog << "DEBUG: Register " << i << " is marked as occupied but no active variable found" << std::endl;
                }
            }
            debugLog.flush();
            return -1;
        }
        
        Value *spillVar = nullptr;
        int earliestEnd = INT_MAX;

        // 对于var为空的情况（临时寄存器分配），选择结束最早的变量溢出
        // 对于var不为空的情况，需要比较生存期
        if (!var) {
            debugLog << "DEBUG: Temporary allocation - finding earliest ending variable" << std::endl;
            // 临时分配：选择结束最早的变量
            for (auto *v : floatRegValues) {
                if (v->getLiveEnd() < earliestEnd) {
                    earliestEnd = v->getLiveEnd();
                    spillVar = v;
                }
            }
            if (spillVar) {
                debugLog << "DEBUG: Selected spill candidate (temp): " << spillVar 
                         << ", reg=" << spillVar->getLoadRegId() 
                         << ", liveEnd=" << spillVar->getLiveEnd() << std::endl;
            }
        } else {
            debugLog << "DEBUG: Variable allocation - var liveBegin=" << var->getLiveBegin() 
                     << ", liveEnd=" << var->getLiveEnd() << std::endl;
            // 有具体变量：选择结束最早且早于当前变量开始的变量
            for (auto *v : floatRegValues) {
                debugLog << "DEBUG: Checking spill candidate: " << v 
                         << ", reg=" << v->getLoadRegId() 
                         << ", liveEnd=" << v->getLiveEnd() << std::endl;
                if (v->getLiveEnd() < earliestEnd && v->getLiveEnd() <= var->getLiveBegin()) {
                    earliestEnd = v->getLiveEnd();
                    spillVar = v;
                    debugLog << "DEBUG: New best spill candidate: " << spillVar << std::endl;
                }
            }
            
            // 如果没找到合适的溢出变量，说明当前变量与所有已分配变量生存期重叠
            // 根据线性扫描算法，应该拒绝分配
            if (!spillVar) {
                debugLog << "WARNING: Cannot allocate register due to live range conflicts - all active variables overlap with requested variable" << std::endl;
                debugLog.flush();
                return -1;
            }
        }

        if (spillVar && spillVar->getLoadRegId() != -1) {
            regno = spillVar->getLoadRegId();
            debugLog << "DEBUG: Spilling variable " << spillVar << " from register " << regno << std::endl;
            spillVar->setLoadRegId(-1);
            floatRegValues.erase(std::remove(floatRegValues.begin(), floatRegValues.end(), spillVar), floatRegValues.end());
            floatRegBitmap.reset(regno);
        } else {
            debugLog << "ERROR: No valid spillable variable found - spillVar=" << spillVar << std::endl;
            if (spillVar) {
                debugLog << "DEBUG: spillVar regId=" << spillVar->getLoadRegId() << std::endl;
            }
            debugLog.flush();
            return -1;
        }
    }

    if (regno != -1) {
        debugLog << "DEBUG: Final allocation: register " << regno << std::endl;
        floatBitmapSet(regno);
        if (var) {
            var->setLoadRegId(regno);
            floatRegValues.push_back(var);
            debugLog << "DEBUG: Variable " << var << " assigned to register " << regno << std::endl;
        } else {
            debugLog << "DEBUG: Temporary register " << regno << " allocated" << std::endl;
        }
    }

    debugLog << "DEBUG: AllocateFloat finished - returned register " << regno << std::endl << std::endl;
    debugLog.flush();
    return regno;
}

void LinearScanRegisterAllocator::AllocateFloat(int32_t no)
{
    if (floatRegBitmap.test(no)) {
        freeFloat(no);
    }
    floatBitmapSet(no);
}

void LinearScanRegisterAllocator::freeFloat(Value *var)
{
    if (debugEnabled) {
        debugLog << "DEBUG: freeFloat(Value*) called - var=" << var;
    }
    
    if (var && var->getLoadRegId() != -1) {
        int regId = var->getLoadRegId();
        if (debugEnabled) {
            debugLog << ", releasing register " << regId << std::endl;
        }
        floatRegBitmap.reset(var->getLoadRegId());
        floatRegValues.erase(std::remove(floatRegValues.begin(), floatRegValues.end(), var), floatRegValues.end());
        var->setLoadRegId(-1);
        if (debugEnabled) {
            debugLog << "DEBUG: Register " << regId << " freed successfully" << std::endl;
        }
    } else {
        if (debugEnabled) {
            debugLog << ", no register to free (regId=" << (var ? var->getLoadRegId() : -2) << ")" << std::endl;
        }
    }
    
    if (debugEnabled) {
        debugLog.flush();
    }
}

void LinearScanRegisterAllocator::freeFloat(int32_t no)
{
    if (debugEnabled) {
        debugLog << "DEBUG: freeFloat(int32_t) called - register=" << no;
    }
    
    if (no == -1) {
        if (debugEnabled) {
            debugLog << ", invalid register number" << std::endl;
        }
        return;
    }

    if (debugEnabled) {
        debugLog << std::endl;
    }
    
    floatRegBitmap.reset(no);
    auto it = std::find_if(floatRegValues.begin(), floatRegValues.end(), [no](Value *v) {
        return v->getLoadRegId() == no;
    });

    if (it != floatRegValues.end()) {
        if (debugEnabled) {
            debugLog << "DEBUG: Found variable " << *it << " using register " << no << ", removing from active list" << std::endl;
        }
        (*it)->setLoadRegId(-1);
        floatRegValues.erase(it);
    } else {
        if (debugEnabled) {
            debugLog << "DEBUG: No variable found using register " << no << " in active list" << std::endl;
        }
    }
    
    if (debugEnabled) {
        debugLog << "DEBUG: Register " << no << " freed" << std::endl;
        debugLog.flush();
    }
}

int LinearScanRegisterAllocator::Allocate(bool is_float, Value *var, int32_t no)
{
    if (is_float) {
        return AllocateFloat(var, no);
    } else {
        return AllocateInt(var, no);
    }
}

void LinearScanRegisterAllocator::AllocateReg(int32_t no, bool is_float)
{
    if (is_float) {
        AllocateFloat(no);
    } else {
        AllocateInt(no);
    }
}

void LinearScanRegisterAllocator::free(Value *var, bool is_float)
{
    if (is_float) {
        freeFloat(var);
    } else {
        freeInt(var);
    }
}

void LinearScanRegisterAllocator::free(int32_t no, bool is_float)
{
    if (is_float) {
        freeFloat(no);
    } else {
        freeInt(no);
    }
}

void LinearScanRegisterAllocator::bitmapSet(int32_t no)
{
    regBitmap.set(no);
    usedBitmap.set(no);
}

void LinearScanRegisterAllocator::floatBitmapSet(int32_t no)
{
    floatRegBitmap.set(no);
    floatUsedBitmap.set(no);
}

void LinearScanRegisterAllocator::setCurrentInstruction(int instIdx, const std::string& instStr)
{
    currentInstIdx = instIdx;
    currentInstStr = instStr;
}

void LinearScanRegisterAllocator::testDebugFunction()
{
    if (!debugLog.is_open()) {
        debugLog.open("/home/rui/minic_test/register_allocator_debug.log", std::ios::app);
    }
    
    debugLog << "\n=== DEBUG FUNCTION TEST ===" << std::endl;
    debugLog << "Debug enabled: " << (debugEnabled ? "YES" : "NO") << std::endl;
    debugLog << "Current instruction index: " << currentInstIdx << std::endl;
    debugLog << "Current instruction string: " << currentInstStr << std::endl;
    debugLog << "Test message from LinearScanRegisterAllocator" << std::endl;
    debugLog.flush();
}

void LinearScanRegisterAllocator::reset()
{
    if (debugEnabled && !debugLog.is_open()) {
        debugLog.open("/home/rui/minic_test/register_allocator_debug.log", std::ios::app);
    }
    
    if (debugEnabled) {
        debugLog << "\n=== RESETTING REGISTER ALLOCATOR FOR NEW FUNCTION ===" << std::endl;
        debugLog << "Previous state - Int active vars: " << regValues.size() 
                 << ", Float active vars: " << floatRegValues.size() << std::endl;
    }
    
    // 重置整数寄存器状态
    resetIntRegisters();
    
    // 重置浮点寄存器状态
    resetFloatRegisters();
    
    // 重置调试信息
    currentInstIdx = -1;
    currentInstStr = "";
    
    if (debugEnabled) {
        debugLog << "Register allocator reset completed" << std::endl;
        debugLog.flush();
    }
}

void LinearScanRegisterAllocator::resetFloatRegisters()
{
    // 清理所有活跃变量的寄存器绑定
    for (auto* var : floatRegValues) {
        if (var) {
            var->setLoadRegId(-1);
        }
    }
    
    // 清空活跃变量列表
    floatRegValues.clear();
    
    // 重置当前占用位图（但保留历史使用记录）
    floatRegBitmap.resetall();
    
    if (debugEnabled) {
        debugLog << "DEBUG: Float registers reset completed" << std::endl;
    }
}

void LinearScanRegisterAllocator::resetIntRegisters()
{
    // 清理所有活跃变量的寄存器绑定
    for (auto* var : regValues) {
        if (var) {
            var->setLoadRegId(-1);
        }
    }
    
    // 清空活跃变量列表
    regValues.clear();
    
    // 重置当前占用位图（但保留历史使用记录）
    regBitmap.resetall();
    
    if (debugEnabled) {
        debugLog << "DEBUG: Int registers reset completed" << std::endl;
    }
}