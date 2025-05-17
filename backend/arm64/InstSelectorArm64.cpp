#include <cstdio>
#include "Common.h"
#include "ILocArm64.h"
#include "InstSelectorArm64.h"
#include "PlatformArm64.h"
#include "PointerType.h"
#include "RegVariable.h"
#include "Function.h"
#include "LabelInstruction.h"
#include "GotoInstruction.h"
#include "FuncCallInstruction.h"
#include "MoveInstruction.h"
#include "MemsetInstruction.h"
#include "GetElementPtrInstruction.h"
#include "BitcastInstruction.h"
#define Instanceof(res, type, var) auto res = dynamic_cast<type>(var)

InstSelectorArm64::InstSelectorArm64(vector<Instruction *> & _irCode,
                                     ILocArm64 & _iloc,
                                     Function * _func,
                                     SimpleRegisterAllocator & allocator)
    : ir(_irCode), iloc(_iloc), func(_func), simpleRegisterAllocator(allocator)
{
    translator_handlers[IRInstOperator::IRINST_OP_ENTRY] = &InstSelectorArm64::translate_entry;
    translator_handlers[IRInstOperator::IRINST_OP_EXIT] = &InstSelectorArm64::translate_exit;
    translator_handlers[IRInstOperator::IRINST_OP_LABEL] = &InstSelectorArm64::translate_label;
    translator_handlers[IRInstOperator::IRINST_OP_GOTO] = &InstSelectorArm64::translate_goto;
    translator_handlers[IRInstOperator::IRINST_OP_ASSIGN] = &InstSelectorArm64::translate_assign;
	translator_handlers[IRInstOperator::IRINST_OP_STORE] = &InstSelectorArm64::translate_store;
	translator_handlers[IRInstOperator::IRINST_OP_LOAD] = &InstSelectorArm64::translate_load;
	translator_handlers[IRInstOperator::IRINST_OP_GEP] = &InstSelectorArm64::translate_gep;
	translator_handlers[IRInstOperator::IRINST_OP_CAST] = &InstSelectorArm64::translate_cast;
    translator_handlers[IRInstOperator::IRINST_OP_MEMSET] = &InstSelectorArm64::translate_memset;

    // 新增：注册算术/逻辑/分支/函数相关指令
    translator_handlers[IRInstOperator::IRINST_OP_ADD_I] = &InstSelectorArm64::translate_add;
    translator_handlers[IRInstOperator::IRINST_OP_SUB_I] = &InstSelectorArm64::translate_sub;
    translator_handlers[IRInstOperator::IRINST_OP_MUL_I] = &InstSelectorArm64::translate_mul;
    translator_handlers[IRInstOperator::IRINST_OP_DIV_I] = &InstSelectorArm64::translate_div;
    translator_handlers[IRInstOperator::IRINST_OP_GT_I]  = &InstSelectorArm64::translate_gt;
    translator_handlers[IRInstOperator::IRINST_OP_LT_I]  = &InstSelectorArm64::translate_lt;
    translator_handlers[IRInstOperator::IRINST_OP_LE_I]  = &InstSelectorArm64::translate_le;
    translator_handlers[IRInstOperator::IRINST_OP_GE_I]  = &InstSelectorArm64::translate_ge;
    translator_handlers[IRInstOperator::IRINST_OP_EQ_I]  = &InstSelectorArm64::translate_eq;
    translator_handlers[IRInstOperator::IRINST_OP_NE_I]  = &InstSelectorArm64::translate_ne;
    translator_handlers[IRInstOperator::IRINST_OP_AND_I] = &InstSelectorArm64::translate_and;
    translator_handlers[IRInstOperator::IRINST_OP_OR_I]  = &InstSelectorArm64::translate_or;
    translator_handlers[IRInstOperator::IRINST_OP_NOT_I] = &InstSelectorArm64::translate_not;
    translator_handlers[IRInstOperator::IRINST_OP_MOD_I] = &InstSelectorArm64::translate_mod;
    translator_handlers[IRInstOperator::IRINST_OP_BRANCH_I] = &InstSelectorArm64::translate_branch;
    translator_handlers[IRInstOperator::IRINST_OP_FUNC_CALL] = &InstSelectorArm64::translate_func_call;
    translator_handlers[IRInstOperator::IRINST_OP_ARG] = &InstSelectorArm64::translate_arg;
}

InstSelectorArm64::~InstSelectorArm64() {}

void InstSelectorArm64::run() {
    for (auto inst: ir) {
        if (!inst->isDead()) {
            translate(inst);
        }
    }
}

void InstSelectorArm64::translate(Instruction * inst) {
    IRInstOperator op = inst->getOp();
    auto pIter = translator_handlers.find(op);
    if (pIter == translator_handlers.end()) {
        printf("Translate: Operator(%d) not support", (int) op);
        return;
    }
    if (showLinearIR) {
        outputIRInstruction(inst);
    }
    (this->*(pIter->second))(inst);
}

void InstSelectorArm64::outputIRInstruction(Instruction * inst) {
    std::string irStr;
    inst->toString(irStr);
    if (!irStr.empty()) {
        iloc.comment(irStr);
    }
}

void InstSelectorArm64::translate_nop(Instruction * inst) {
    (void) inst;
    iloc.nop();
}

void InstSelectorArm64::translate_label(Instruction * inst) {
    Instanceof(labelInst, LabelInstruction *, inst);
    iloc.label(labelInst->getName());
}

void InstSelectorArm64::translate_goto(Instruction * inst) {
    Instanceof(gotoInst, GotoInstruction *, inst);
    iloc.jump(gotoInst->getTarget()->getName());
}

void InstSelectorArm64::translate_entry(Instruction * inst) {
    auto & protectedRegNo = func->getProtectedReg();
    auto & protectedRegStr = func->getProtectedRegStr();
    bool first = true;
    for (auto regno: protectedRegNo) {
        if (first) {
            protectedRegStr = PlatformArm64::regName[regno];
            first = false;
        } else {
            protectedRegStr += "," + PlatformArm64::regName[regno];
        }
    }

    // 计算总栈帧大小（含保护寄存器空间，保证16字节对齐）
    int funcCallArgCnt = func->getMaxFuncCallArgCnt() - 8;
    funcCallArgCnt = std::max(funcCallArgCnt, 0);
    int off = func->getMaxDep();
    off += funcCallArgCnt * 8;
    int save_size = 0;
    if (protectedRegNo.size() == 2) save_size = 16;
    else if (protectedRegNo.size() == 1) save_size = 8;
    int frame_size = off + save_size;
    if (frame_size % 16 != 0) frame_size += 16 - (frame_size % 16);

    // 保存fp/lr并分配栈帧
    if (protectedRegNo.size() == 2) {
        iloc.inst("stp", PlatformArm64::regName[protectedRegNo[0]], PlatformArm64::regName[protectedRegNo[1]], "[sp, #-" + iloc.toStr(save_size, false) + "]!");
    } else if (protectedRegNo.size() == 1) {
        iloc.inst("str", PlatformArm64::regName[protectedRegNo[0]], "[sp, #-" + iloc.toStr(save_size, false) + "]!");
    }

	iloc.inst("sub", PlatformArm64::regName[ARM64_SP_REG_NO], PlatformArm64::regName[ARM64_SP_REG_NO], iloc.toStr(frame_size - save_size, false));

    // 设置fp = sp
    iloc.inst("mov", PlatformArm64::regName[ARM64_FP_REG_NO], PlatformArm64::regName[ARM64_SP_REG_NO]);

	int paramsNum = inst->getOperandsNum();
	if (paramsNum) {
		for (int i = 0; i < paramsNum; ++i) {
			Value * arg = inst->getOperand(i);
			int32_t arg_regId = arg->getRegId();
			if (arg_regId != -1) {
				iloc.store_var(arg_regId, arg, ARM64_TMP_REG_NO);
			} else {
				int32_t temp_regno = simpleRegisterAllocator.Allocate();
				iloc.load_var(temp_regno, arg);
				iloc.store_var(temp_regno, arg, ARM64_TMP_REG_NO);
				simpleRegisterAllocator.free(temp_regno);
			}
		}
	}
}

void InstSelectorArm64::translate_exit(Instruction * inst) {
    if (inst->getOperandsNum()) {
        Value * retVal = inst->getOperand(0);
        iloc.load_var(0, retVal);
    }
    auto & protectedRegNo = func->getProtectedReg();

    int funcCallArgCnt = func->getMaxFuncCallArgCnt() - 8;
    funcCallArgCnt = std::max(funcCallArgCnt, 0);
    int off = func->getMaxDep();
    off += funcCallArgCnt * 8;
    int save_size = 0;
    if (protectedRegNo.size() == 2) save_size = 16;
    else if (protectedRegNo.size() == 1) save_size = 8;
    int frame_size = off + save_size;
    if (frame_size % 16 != 0) frame_size += 16 - (frame_size % 16);

	iloc.inst("mov", PlatformArm64::regName[ARM64_SP_REG_NO], PlatformArm64::regName[ARM64_FP_REG_NO]);
	iloc.inst("add", PlatformArm64::regName[ARM64_SP_REG_NO], PlatformArm64::regName[ARM64_SP_REG_NO], iloc.toStr(frame_size - save_size, false));

    // 恢复fp/lr并回收栈帧
    if (protectedRegNo.size() == 2) {
        iloc.inst("ldp", PlatformArm64::regName[protectedRegNo[0]], PlatformArm64::regName[protectedRegNo[1]], "[sp], #" + iloc.toStr(save_size, false));
    } else if (protectedRegNo.size() == 1) {
        iloc.inst("ldr", PlatformArm64::regName[protectedRegNo[0]], "[sp], #" + iloc.toStr(save_size, false));
    }
    iloc.inst("ret", "");
}

void InstSelectorArm64::translate_assign(Instruction * inst) {
    Value * result = inst->getOperand(0);
    Value * arg1 = inst->getOperand(1);
    int32_t arg1_regId = arg1->getRegId();
    int32_t result_regId = result->getRegId();

	//新增对数组复制的特殊处理
	if(Instanceof(GepInst, GetElementPtrInstruction *, result)) 
	{	
		//储存立即数到R1
		int32_t temp_regno1 = simpleRegisterAllocator.Allocate();
		//储存地址到R2
		int32_t temp_regno2 = simpleRegisterAllocator.Allocate();
		iloc.load_var(temp_regno1, arg1);
		iloc.load_var(temp_regno2, GepInst);

		iloc.inst("str", PlatformArm64::regName[temp_regno1], "[" + PlatformArm64::regName[temp_regno2] + ", #0]");

		iloc.store_var(temp_regno1, GepInst, ARM64_TMP_REG_NO);
		simpleRegisterAllocator.free(temp_regno1);
		simpleRegisterAllocator.free(temp_regno2);

	}
	else
	{
		if (arg1_regId != -1) {
			iloc.store_var(arg1_regId, result, ARM64_TMP_REG_NO);
		} else if (result_regId != -1) {
			iloc.load_var(result_regId, arg1);
		} else {
			int32_t temp_regno = simpleRegisterAllocator.Allocate();
			iloc.load_var(temp_regno, arg1);
			iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO);
			simpleRegisterAllocator.free(temp_regno);
		}
	}

}

void InstSelectorArm64::translate_store(Instruction * inst) {
	
	translate_assign(inst);
}

void InstSelectorArm64::translate_load(Instruction * inst) {
	Value * arg1 = inst->getOperand(0);
	Value * result = inst;
	int32_t arg1_regId = arg1->getRegId();
    int32_t result_regId = result->getRegId();
	//新增对数组Load的特殊处理
	if(Instanceof(GepInst, GetElementPtrInstruction *, arg1)) 
	{	
		//储存地址到x0
		int32_t temp_regno = simpleRegisterAllocator.Allocate();
		iloc.load_var(temp_regno, GepInst);
		//从[x0]中取出值到x0
		iloc.inst("ldr", PlatformArm64::regName[temp_regno], "[" + PlatformArm64::regName[temp_regno] + ", #0]");
		//把x0保存到result
		iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO);
		simpleRegisterAllocator.free(temp_regno);
	}
	else
	{
		if (arg1_regId != -1) {
			iloc.store_var(arg1_regId, result, ARM64_TMP_REG_NO);
		} else if (result_regId != -1) {
			iloc.load_var(result_regId, arg1);
		} else {
			int32_t temp_regno = simpleRegisterAllocator.Allocate();
			iloc.load_var(temp_regno, arg1);
			iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO);
			simpleRegisterAllocator.free(temp_regno);
		}
	}
    

}

void InstSelectorArm64::translate_gep(Instruction * inst) {

	Instanceof(gepInst, GetElementPtrInstruction *, inst);
	Value * arg1 = gepInst->getOperand(0);
    Instanceof(castInst, BitcastInstruction *, arg1);

	Value * base_addr = castInst->getOperand(0);

	Value * result = gepInst;
	int32_t base_addr_regId = base_addr->getRegId();
    int32_t result_regId = result->getRegId();
	//计算偏移量
	int64_t offset = 0;
    int dims = gepInst->getIndexces()[0];
	//所有类型的元素大小都是4
	offset += dims * 4;

    if (base_addr_regId != -1) {
        iloc.store_var(base_addr_regId, result, ARM64_TMP_REG_NO);
    } else if (result_regId != -1) {
        iloc.load_var(result_regId, base_addr);
    } else {
        int32_t temp_regno = simpleRegisterAllocator.Allocate();
        iloc.load_var(temp_regno, base_addr);
		// 计算具体地址
		iloc.inst("add", PlatformArm64::regName[temp_regno], PlatformArm64::regName[temp_regno], iloc.toStr(offset, false));
        iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO);
        simpleRegisterAllocator.free(temp_regno);
    }

}

void InstSelectorArm64::translate_cast(Instruction * inst) {
	//cast 不生成对应指令，因为它只是一个 类型层面的转换，不改变内存地址或数据布局。
}

void InstSelectorArm64::translate_memset(Instruction * inst) {
	Instanceof(memsetInst, MemsetInstruction *, inst);
    // memset指令用于将一段内存设置为0
	// 目标地址，但是源操作数存在memsetInst->getOperand(0)中的operand中
    Value * op1 = memsetInst->getOperand(0);  
	Instanceof(castInst, Instruction *, op1);
	Value * addr = castInst->getOperand(0);
    int32_t addr_reg = addr->getRegId();
    int32_t tmp_reg = ARM64_TMP_REG_NO;
    
    if (addr_reg == -1) {
        addr_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(addr_reg, addr);
    }
    
    // 使用零寄存器和stp指令优化内存初始化
    iloc.inst("mov", PlatformArm64::regName[tmp_reg], "#0");
	
    int64_t len = memsetInst->getSize();
	int aligned16_len = (len / 16) * 16;  // 可用 stp 写入的长度
    int remainder = len - aligned16_len;
	int aligned8_len = (remainder / 8) * 8;  // 可用 str 写入的长度
	int rest = remainder - aligned8_len;  // 剩余的长度

    // 先使用 stp 写入对齐部分
    for (int offset = 0; offset < aligned16_len; offset += 16) {
        iloc.inst("stp",
                  PlatformArm64::regName[tmp_reg],
                  PlatformArm64::regName[tmp_reg],
                  "[" + PlatformArm64::regName[addr_reg] + ", #" + std::to_string(offset) + "]");
    }
	// 再使用 stp 写入对齐部分
	if(aligned8_len) {
		iloc.inst("str",
					PlatformArm64::regName[tmp_reg],
					"[" + PlatformArm64::regName[addr_reg] + ", #" + std::to_string(aligned16_len) + "]");
	}
	if(rest)
	{
		iloc.inst("str",
			"wzr",
			"[" + PlatformArm64::regName[addr_reg] + ", #" + std::to_string(aligned16_len + aligned8_len) + "]");
	}
    
    
    if (addr->getRegId() == -1) {
        simpleRegisterAllocator.free(addr_reg);
    }
}

// 算术二元指令
void InstSelectorArm64::translate_add(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("add", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_sub(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("sub", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_mul(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("mul", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_div(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("sdiv", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_mod(Instruction * inst) {
    // a % b = a - (a / b) * b
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    int32_t tmp_div = simpleRegisterAllocator.Allocate();
    int32_t tmp_mul = simpleRegisterAllocator.Allocate();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("sdiv", PlatformArm64::regName[tmp_div], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.inst("mul", PlatformArm64::regName[tmp_mul], PlatformArm64::regName[tmp_div], PlatformArm64::regName[rhs_reg]);
    iloc.inst("sub", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[tmp_mul]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    simpleRegisterAllocator.free(tmp_div);
    simpleRegisterAllocator.free(tmp_mul);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

// ARMv8-A A64条件码映射
static const char* getA64Cond(IRInstOperator op) {
    switch (op) {
        case IRInstOperator::IRINST_OP_GT_I: return "gt"; // signed greater than
        case IRInstOperator::IRINST_OP_LT_I: return "lt"; // signed less than
        case IRInstOperator::IRINST_OP_GE_I: return "ge"; // signed greater or equal
        case IRInstOperator::IRINST_OP_LE_I: return "le"; // signed less or equal
        case IRInstOperator::IRINST_OP_EQ_I: return "eq"; // equal
        case IRInstOperator::IRINST_OP_NE_I: return "ne"; // not equal
        default: return "al"; // always (should not happen)
    }
}

// 关系运算通用实现
void InstSelectorArm64::translate_cmp(Instruction * inst, IRInstOperator op) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) { lhs_reg = simpleRegisterAllocator.Allocate(); iloc.load_var(lhs_reg, lhs); }
    if (rhs_reg == -1) { rhs_reg = simpleRegisterAllocator.Allocate(); iloc.load_var(rhs_reg, rhs); }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("cmp", PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.inst("cset", PlatformArm64::regName[dst_reg], getA64Cond(op));
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

// 替换原有宏和函数
void InstSelectorArm64::translate_gt(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_GT_I); }   // 大于
void InstSelectorArm64::translate_lt(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_LT_I); }   // 小于
void InstSelectorArm64::translate_le(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_LE_I); }   // 小于等于
void InstSelectorArm64::translate_ge(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_GE_I); }   // 大于等于
void InstSelectorArm64::translate_eq(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_EQ_I); }   // 等于
void InstSelectorArm64::translate_ne(Instruction * inst)  { translate_cmp(inst, IRInstOperator::IRINST_OP_NE_I); }   // 不等于

// 分支指令（b.cond格式）
void InstSelectorArm64::translate_branch(Instruction * inst) {
    // 假设操作数0为条件，1为true label，2为false label
    Value * cond = inst->getOperand(0);
    Value * trueLabel = inst->getOperand(1);
    Value * falseLabel = inst->getOperand(2);
    int32_t cond_reg = cond->getRegId();
    if (cond_reg == -1) {
        cond_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(cond_reg, cond);
    }
    // 先cmp #0
    iloc.inst("cmp", PlatformArm64::regName[cond_reg], "#0");
    // b.ne trueLabel
    iloc.inst("b.ne", trueLabel->getName());
    // b falseLabel
    iloc.inst("b", falseLabel->getName());
    if (cond->getRegId() == -1) simpleRegisterAllocator.free(cond_reg);
}

// 逻辑运算
void InstSelectorArm64::translate_and(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("and", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_or(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
	Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("orr", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_not(Instruction * inst) {
    Value * dst = inst->getOperand(0);
    Value * src = inst->getOperand(1);
    int32_t dst_reg = dst->getRegId();
    int32_t src_reg = src->getRegId();
    if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate();
    if (src_reg == -1) {
        src_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(src_reg, src);
    }
    iloc.inst("mvn", PlatformArm64::regName[dst_reg], PlatformArm64::regName[src_reg], "");
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (src->getRegId() == -1) simpleRegisterAllocator.free(src_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

// 函数调用
void InstSelectorArm64::translate_func_call(Instruction * inst) {
    // 假设操作数0为函数名，1~n为参数
    Value * funcVal = inst;
    int n = inst->getOperandsNum();
    for (int i = 0; i < n; ++i) {
        Value * arg = inst->getOperand(i);
        int32_t reg = arg->getRegId();
        if (reg == -1) {
            reg = simpleRegisterAllocator.Allocate();
            iloc.load_var(reg, arg);
        }
        // // ARM64前8个参数寄存器x0-x7
        // if (i < 8) {
        //     iloc.inst("mov", PlatformArm64::regName[i], PlatformArm64::regName[reg], "");
        // } else {
        //     // 超过8个参数，按ABI入栈
        //     // 这里只做注释，实际实现需完善
        //     iloc.comment("TODO: 参数" + std::to_string(i) + "入栈");
        // }
        if (arg->getRegId() == -1) simpleRegisterAllocator.free(reg);
    }
    iloc.inst("bl", funcVal->getIRName());
    // 返回值默认在x0
    if (n > 0) {
        Value * ret = inst->getOperand(0);
        iloc.store_var(0, ret, ARM64_TMP_REG_NO);
    }
}

// 实参
void InstSelectorArm64::translate_arg(Instruction * inst) {
    // 通常参数传递已在translate_func_call处理
    outputIRInstruction(inst);
}
