#include <algorithm>
#include "SimpleRegisterAllocator.h"

SimpleRegisterAllocator::SimpleRegisterAllocator() {}

int SimpleRegisterAllocator::Allocate(Value * var, int32_t no) {
    if (var && (var->getLoadRegId() != -1)) {
        return var->getLoadRegId();
    }
    int32_t regno = -1;
    if ((no != -1) && !regBitmap.test(no)) {
        regno = no;
    } else {
        for (int k = 0; k < PlatformArm64::maxUsableRegNum; ++k) {
            if (!regBitmap.test(k)) {
                regno = k;
                break;
            }
        }
    }
    if (regno != -1) {
        bitmapSet(regno);
    } else {
        Value * oldestVar = regValues.front();
        regno = oldestVar->getLoadRegId();
        oldestVar->setLoadRegId(-1);
        regValues.erase(regValues.begin());
    }
    if (var) {
        var->setLoadRegId(regno);
        regValues.push_back(var);
    }
    return regno;
}

void SimpleRegisterAllocator::Allocate(int32_t no) {
    if (regBitmap.test(no)) {
        free(no);
    }
    bitmapSet(no);
}

void SimpleRegisterAllocator::free(Value * var) {
    if (var && (var->getLoadRegId() != -1)) {
        regBitmap.reset(var->getLoadRegId());
        regValues.erase(std::find(regValues.begin(), regValues.end(), var));
        var->setLoadRegId(-1);
    }
}

void SimpleRegisterAllocator::free(int32_t no) {
    if (no == -1) return;
    regBitmap.reset(no);
    auto pIter = std::find_if(regValues.begin(), regValues.end(), [=](auto val) {
        return val->getLoadRegId() == no;
    });
    if (pIter != regValues.end()) {
        (*pIter)->setLoadRegId(-1);
        regValues.erase(pIter);
    }
}

void SimpleRegisterAllocator::bitmapSet(int32_t no) {
    regBitmap.set(no);
    usedBitmap.set(no);
}
