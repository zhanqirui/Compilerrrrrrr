#include <algorithm>
#include "SimpleRegisterAllocator.h"

// 默认构造函数
SimpleRegisterAllocator::SimpleRegisterAllocator() {}

/**
 * 为变量分配寄存器
 * @param var 需要分配寄存器的变量
 * @param no 期望分配的寄存器编号，-1表示不指定
 * @return 分配的寄存器编号
 */
int SimpleRegisterAllocator::AllocateInt(Value * var, int32_t no) {
    // 如果变量已经分配了寄存器，直接返回
    if (var && (var->getLoadRegId() != -1)) {
        return var->getLoadRegId();
    }
    int32_t regno = -1;
    // 如果指定了寄存器编号且该寄存器空闲，则使用它
    if ((no != -1) && !regBitmap.test(no)) {
        regno = no;
    } else {
        // 否则查找第一个空闲的寄存器
        for (int k = 0; k < PlatformArm64::maxUsableRegNum; ++k) {
            if (!regBitmap.test(k)) {
                regno = k;
                break;
            }
        }
    }
    
    if (regno != -1) {
        // 找到空闲寄存器，标记为已使用
        bitmapSet(regno);
    } else {
        // 没有空闲寄存器，使用LRU策略替换
        // 取出最早分配的变量对应的寄存器
		if (regValues.empty()) {
			std::cout << "[ERROR] Register allocation failed: no free registers and no values to spill." << std::endl;
			abort(); // 或者 throw 异常
		}
        Value * oldestVar = regValues.front();
        regno = oldestVar->getLoadRegId();
        oldestVar->setLoadRegId(-1);
        regValues.erase(regValues.begin());
    }
    
    // 更新变量的寄存器信息并加入到已分配列表
    if (var) {
        var->setLoadRegId(regno);
        regValues.push_back(var);
    }
    return regno;
}

/**
 * 分配指定编号的寄存器
 * @param no 要分配的寄存器编号
 */
void SimpleRegisterAllocator::AllocateInt(int32_t no) {
    // 如果寄存器已被占用，先释放它
    if (regBitmap.test(no)) {
        free(no);
    }
    // 标记寄存器为已分配
    bitmapSet(no);
}

/**
 * 释放变量占用的寄存器
 * @param var 要释放寄存器的变量
 */
void SimpleRegisterAllocator::freeInt(Value * var) {
    if (var && (var->getLoadRegId() != -1)) {
        // 重置寄存器位图中的对应位
        regBitmap.reset(var->getLoadRegId());
        // 从寄存器-变量映射中移除该变量
        regValues.erase(std::find(regValues.begin(), regValues.end(), var));
        // 清除变量中的寄存器信息
        var->setLoadRegId(-1);
    }
}

/**
 * 释放指定编号的寄存器
 * @param no 要释放的寄存器编号
 */
void SimpleRegisterAllocator::freeInt(int32_t no) {
    if (no == -1) return;
    // 重置寄存器位图中的对应位
    regBitmap.reset(no);
    // 查找使用该寄存器的变量
    auto pIter = std::find_if(regValues.begin(), regValues.end(), [=](auto val) {
        return val->getLoadRegId() == no;
    });
    if (pIter != regValues.end()) {
        // 清除变量中的寄存器信息并从列表中移除
        (*pIter)->setLoadRegId(-1);
        regValues.erase(pIter);
    }
}

/**
 * 在位图中标记寄存器为已使用
 * @param no 要标记的寄存器编号
 */
void SimpleRegisterAllocator::bitmapSet(int32_t no) {
    // 标记当前使用位图
    regBitmap.set(no);
    // 记录历史使用情况
    usedBitmap.set(no);
}

// 新增：为浮点变量分配寄存器
int SimpleRegisterAllocator::AllocateFloat(Value * var, int32_t no) {
    if (var && (var->getLoadRegId() != -1)) {
        return var->getLoadRegId();
    }
    int32_t regno = -1;
    if ((no != -1) && !floatRegBitmap.test(no)) {
        regno = no;
    } else {
        for (int k = 0; k < PlatformArm64::maxUsableRegNum; ++k) {
            if (!floatRegBitmap.test(k)) {
                regno = k;
                break;
            }
        }
    }
    if (regno != -1) {
        floatBitmapSet(regno);
    } else {
        Value * oldestVar = floatRegValues.front();
        regno = oldestVar->getLoadRegId();
        oldestVar->setLoadRegId(-1);
        floatRegValues.erase(floatRegValues.begin());
    }
    if (var) {
        var->setLoadRegId(regno);
        floatRegValues.push_back(var);
    }
    return regno;
}

// 新增：分配指定编号的浮点寄存器
void SimpleRegisterAllocator::AllocateFloat(int32_t no) {
    if (floatRegBitmap.test(no)) {
        freeFloat(no);
    }
    floatBitmapSet(no);
}

// 新增：释放变量占用的浮点寄存器
void SimpleRegisterAllocator::freeFloat(Value * var) {
    if (var && (var->getLoadRegId() != -1)) {
        floatRegBitmap.reset(var->getLoadRegId());
        floatRegValues.erase(std::find(floatRegValues.begin(), floatRegValues.end(), var));
        var->setLoadRegId(-1);
    }
}

// 新增：释放指定编号的浮点寄存器
void SimpleRegisterAllocator::freeFloat(int32_t no) {
    if (no == -1) return;
    floatRegBitmap.reset(no);
    auto pIter = std::find_if(floatRegValues.begin(), floatRegValues.end(), [=](auto val) {
        return val->getLoadRegId() == no;
    });
    if (pIter != floatRegValues.end()) {
        (*pIter)->setLoadRegId(-1);
        floatRegValues.erase(pIter);
    }
}

// 新增：在位图中标记浮点寄存器为已使用
void SimpleRegisterAllocator::floatBitmapSet(int32_t no) {
    floatRegBitmap.set(no);
    floatUsedBitmap.set(no);
}
// 新增接口，用于指定释放的寄存器类型
void SimpleRegisterAllocator::free(int32_t no, bool is_float) {
	if(is_float) {
		freeFloat(no);
	} else {
		freeInt(no);
	}
}

void SimpleRegisterAllocator::free(Value * var, bool is_float) {
	if(is_float) {
		freeFloat(var);
	} else {
		freeInt(var);
	}
}


int SimpleRegisterAllocator::Allocate(bool is_float, Value * var, int32_t no) {
	if(is_float) {
		return AllocateFloat(var, no);
	} else {
		return AllocateInt(var, no);
	}
}

void SimpleRegisterAllocator::AllocateReg(int32_t no, bool is_float) {
	if(is_float) {
		AllocateFloat(no);
	} else {
		AllocateInt(no);
	}
}