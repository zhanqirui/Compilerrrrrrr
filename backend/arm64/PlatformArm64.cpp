#include "PlatformArm64.h"
#include "IntegerType.h"
#include "FloatType.h" // 新增，假设存在

const std::string PlatformArm64::regName[PlatformArm64::maxRegNum] = {
    "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7",
    "x8", "x9", "x10", "x11", "x12", "x13", "x14", "x15",
    "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23",
    "x24", "x25", "x26", "x27", "x28", "x29", "lr", "sp"
};

const std::string PlatformArm64::regNameW[PlatformArm64::maxRegNum] = {
	"w0", "w1", "w2", "w3", "w4", "w5", "w6", "w7",
	"w8", "w9", "w10", "w11", "w12", "w13", "w14", "w15",
	"w16", "w17", "w18", "w19", "w20", "w21", "w22", "w23",
	"w24", "w25", "w26", "w27", "w28", "w29",  // fp -> w29
	"lr" ,  // lr -> w30
	"sp"   // sp -> w31
};

const std::string PlatformArm64::regNameS[PlatformArm64::maxRegNum] = {
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "s12", "s13", "s14", "s15",
    "s16", "s17", "s18", "s19", "s20", "s21", "s22", "s23",
    "s24", "s25", "s26", "s27", "s28", "s29", "s30", "s31"
};

RegVariable * PlatformArm64::intRegVal[PlatformArm64::maxRegNum] = {
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[0], 0),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[1], 1),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[2], 2),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[3], 3),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[4], 4),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[5], 5),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[6], 6),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[7], 7),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[8], 8),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[9], 9),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[10], 10),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[11], 11),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[12], 12),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[13], 13),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[14], 14),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[15], 15),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[16], 16),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[17], 17),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[18], 18),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[19], 19),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[20], 20),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[21], 21),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[22], 22),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[23], 23),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[24], 24),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[25], 25),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[26], 26),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[27], 27),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[28], 28),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[29], 29), // fp
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[30], 30), // lr
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[31], 31), // sp
};

RegVariable * PlatformArm64::floatRegVal[PlatformArm64::maxRegNum] = {
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[0], 0),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[1], 1),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[2], 2),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[3], 3),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[4], 4),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[5], 5),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[6], 6),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[7], 7),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[8], 8),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[9], 9),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[10], 10),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[11], 11),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[12], 12),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[13], 13),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[14], 14),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[15], 15),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[16], 16),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[17], 17),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[18], 18),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[19], 19),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[20], 20),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[21], 21),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[22], 22),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[23], 23),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[24], 24),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[25], 25),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[26], 26),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[27], 27),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[28], 28),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[29], 29),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[30], 30),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regNameS[31], 31),
};

void PlatformArm64::roundLeftShiftTwoBit(unsigned int & num) {
    const unsigned int overFlow = num & 0xc0000000;
    num = (num << 2) | (overFlow >> 30);
}

// 将64位寄存器名(x0-x30)转换为32位形式(w0-w30)
std::string PlatformArm64::toWReg(const std::string& xreg) {
    // 仅当寄存器名以'x'开头时进行转换
    if (!xreg.empty() && xreg[0] == 'x') {
        return "w" + xreg.substr(1);
    }
    // 特殊处理sp和lr
    if (xreg == "sp") return "wsp";
    if (xreg == "lr") return "w30";
    
    // 无法转换则返回原名
    return xreg;
}

bool PlatformArm64::__constExpr(int64_t num) {
    uint64_t new_num = (uint64_t) num;
    for (int i = 0; i < 32; i++) {
        if (new_num <= 0xfff) return true;
        roundLeftShiftTwoBit((unsigned int&)new_num);
    }
    return false;
}

bool PlatformArm64::constExpr(int64_t num) {
    return __constExpr(num) || __constExpr(-num);
}

bool PlatformArm64::isDisp(int64_t num) {
    return num < 4096 && num > -4096;
}

bool PlatformArm64::isReg(std::string name) {
    for (int i = 0; i < maxRegNum; ++i) {
        if (name == regName[i]) return true;
    }
    return false;
}
