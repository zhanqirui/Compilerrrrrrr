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
#include "CastInstruction.h"
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
	translator_handlers[IRInstOperator::IRINST_OP_BITCAST] = &InstSelectorArm64::translate_bitcast;
	translator_handlers[IRInstOperator::IRINST_OP_CAST] = &InstSelectorArm64::translate_cast;
    translator_handlers[IRInstOperator::IRINST_OP_MEMSET] = &InstSelectorArm64::translate_memset;
	translator_handlers[IRInstOperator::IRINST_OP_ZEXT] = &InstSelectorArm64::translate_ZEXT;

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

    // 新增：注册浮点数相关指令
    translator_handlers[IRInstOperator::IRINST_OP_ADD_F] = &InstSelectorArm64::translate_fadd;
    translator_handlers[IRInstOperator::IRINST_OP_SUB_F] = &InstSelectorArm64::translate_fsub;
    translator_handlers[IRInstOperator::IRINST_OP_MUL_F] = &InstSelectorArm64::translate_fmul;
    translator_handlers[IRInstOperator::IRINST_OP_DIV_F] = &InstSelectorArm64::translate_fdiv;
    translator_handlers[IRInstOperator::IRINST_OP_EQ_F]  = &InstSelectorArm64::translate_feq;
    translator_handlers[IRInstOperator::IRINST_OP_NE_F]  = &InstSelectorArm64::translate_fne;
    translator_handlers[IRInstOperator::IRINST_OP_LT_F]  = &InstSelectorArm64::translate_flt;
    translator_handlers[IRInstOperator::IRINST_OP_LE_F]  = &InstSelectorArm64::translate_fle;
    translator_handlers[IRInstOperator::IRINST_OP_GT_F]  = &InstSelectorArm64::translate_fgt;
    translator_handlers[IRInstOperator::IRINST_OP_GE_F]  = &InstSelectorArm64::translate_fge;
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
    protectedRegStr.clear();

    for (size_t i = 0; i < protectedRegNo.size(); ++i) {
        if (i > 0) protectedRegStr += ",";
        protectedRegStr += PlatformArm64::regName[protectedRegNo[i]];
    }

    // 确保 protectedRegNo 包含 x29(fp) 和 x30(lr)
    bool has_fp = false, has_lr = false;
    for (auto reg : protectedRegNo) {
        if (reg == 29) has_fp = true;
        if (reg == 30) has_lr = true;
    }
    if (!has_fp) protectedRegNo.push_back(29);
    if (!has_lr) protectedRegNo.push_back(30);

    // 保存 fp/lr 到栈中：stp x29, x30, [sp, #-16]!
    iloc.inst("stp", "x29", "x30", "[sp, #-16]!");
    iloc.inst("mov", "x29", "sp");

    // 保存剩余保护寄存器到 [sp, #offset] 处（注意不改变sp）
    int offset = 0;
    for (size_t i = 0; i < protectedRegNo.size(); ++i) {
        int reg = protectedRegNo[i];
        if (reg == 29 || reg == 30) continue;
        if (i + 1 < protectedRegNo.size()) {
            int reg2 = protectedRegNo[i + 1];
            if (reg2 != 29 && reg2 != 30) {
                iloc.inst("stp",
                    PlatformArm64::regName[reg],
                    PlatformArm64::regName[reg2],
                    "[sp, #" + iloc.toStr(offset, false) + "]");
                offset += 16;
                i++;
                continue;
            }
        }
        iloc.inst("str", PlatformArm64::regName[reg],
                  "[sp, #" + iloc.toStr(offset, false) + "]");
        offset += 8;
    }

    // 分配局部变量空间和栈上传递参数的空间（注意16字节对齐）
    int local_var_space = func->getMaxDep();
    int funcCallArgCnt = std::max(func->getMaxFuncCallArgCnt() - 8, 0);
    int extra_space = local_var_space + funcCallArgCnt * 8;
    if (extra_space % 16 != 0) {
        extra_space = ((extra_space + 15) / 16) * 16;
    }

    if (extra_space <= 504) {
        iloc.inst("sub", "sp", "sp", iloc.toStr(extra_space, false));
    } else {
        int temp = simpleRegisterAllocator.Allocate();
        iloc.load_imm(temp, extra_space);
        iloc.inst("sub", "sp", "sp", PlatformArm64::regName[temp]);
        simpleRegisterAllocator.free(temp);
    }

    // 保存函数参数值（寄存器→局部变量）
    for (int i = 0; i < inst->getOperandsNum(); ++i) {
        Value * arg = inst->getOperand(i);
        int32_t reg_id = arg->getRegId();
        if (reg_id != -1) {
            iloc.store_var(reg_id, arg, ARM64_TMP_REG_NO);
        } else {
            int tmp = simpleRegisterAllocator.Allocate();
            iloc.load_var(tmp, arg);
            iloc.store_var(tmp, arg, ARM64_TMP_REG_NO);
            simpleRegisterAllocator.free(tmp);
        }
    }
}


void InstSelectorArm64::translate_exit(Instruction * inst) {
    // 如果有返回值，把返回值放入 x0
    if (inst->getOperandsNum()) {
        Value * retVal = inst->getOperand(0);
        iloc.load_var(0, retVal);  // x0 = return value
    }

    auto & protectedRegNo = func->getProtectedReg();

    // 计算局部变量空间和额外参数空间
    int local_var_space = func->getMaxDep();
    int funcCallArgCnt = std::max(func->getMaxFuncCallArgCnt() - 8, 0);
    int extra_space = local_var_space + funcCallArgCnt * 8;
    if (extra_space % 16 != 0) {
        extra_space = ((extra_space + 15) / 16) * 16;
    }

    // 1. 恢复保护寄存器（x29/x30 除外），从 sp+0 开始偏移
    int offset = 0;
    for (size_t i = 0; i < protectedRegNo.size(); ++i) {
        int reg = protectedRegNo[i];
        if (reg == 29 || reg == 30) continue;
        if (i + 1 < protectedRegNo.size()) {
            int reg2 = protectedRegNo[i + 1];
            if (reg2 != 29 && reg2 != 30) {
                iloc.inst("ldp",
                    PlatformArm64::regName[reg],
                    PlatformArm64::regName[reg2],
                    "[sp, #" + iloc.toStr(offset, false) + "]");
                offset += 16;
                i++;
                continue;
            }
        }
        iloc.inst("ldr", PlatformArm64::regName[reg],
                  "[sp, #" + iloc.toStr(offset, false) + "]");
        offset += 8;
    }

    // 2. 恢复sp到fp位置（撤销 extra_space 的分配）
    iloc.inst("mov", "sp", "x29");

    // 3. 恢复fp和lr，并释放16字节空间
    iloc.inst("ldp", "x29", "x30", "[sp], #16");

    // 4. 返回
    iloc.inst("ret", "");
}




void InstSelectorArm64::translate_assign(Instruction * inst) {
    Value * result = inst->getOperand(0);
    Value * arg1 = inst->getOperand(1);
    int32_t arg1_regId = arg1->getRegId();
    int32_t result_regId = result->getRegId();

	bool is_float_var = arg1->getType()->isFloatType();
	bool is_int_var = arg1->getType()->isIntegerType();
	//新增对数组复制的特殊处理
	if(Instanceof(GepInst, GetElementPtrInstruction *, result)) 
	{	
		//储存右值到R1,右值有可能是浮点数
		int32_t temp_regno1 = simpleRegisterAllocator.Allocate(is_float_var);
		//储存地址到R2
		int32_t temp_regno2 = simpleRegisterAllocator.Allocate();
		//右值可能是浮点数
		iloc.load_var(temp_regno1, arg1, is_float_var);
		//地址一定是整数
		iloc.load_var(temp_regno2, GepInst);
		if(is_float_var)
		{
			iloc.inst("str", PlatformArm64::regNameS[temp_regno1], "[" + PlatformArm64::regName[temp_regno2] + ", #0]");
		}
		else if(is_int_var)
		{
			iloc.inst("str", PlatformArm64::regNameW[temp_regno1], "[" + PlatformArm64::regName[temp_regno2] + ", #0]");
		}
		else
		{
			printf("Error: Unsupported type for array assignment.\n");
			exit(1);
		}
		simpleRegisterAllocator.free(temp_regno1, is_float_var);
		simpleRegisterAllocator.free(temp_regno2, is_float_var);

	}
	else
	{
		if (arg1_regId != -1) {
			iloc.store_var(arg1_regId, result, ARM64_TMP_REG_NO, is_float_var);
		} else if (result_regId != -1) {
			iloc.load_var(result_regId, arg1, is_float_var);
		} else {
			// 如果是浮点类型，使用AllocateFloat，否则使用Allocate
			int32_t temp_regno = simpleRegisterAllocator.Allocate(is_float_var);
			int32_t result_regno = simpleRegisterAllocator.Allocate(false, result);
			iloc.load_var(temp_regno, arg1, is_float_var);
			iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO, is_float_var);
			simpleRegisterAllocator.free(temp_regno, is_float_var);
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

	bool is_float_var = arg1->getType()->isFloatType();
    bool is_param = arg1->isParam();
    //新增对数组Load的特殊处理
	if(Instanceof(GepInst, GetElementPtrInstruction *, arg1)) 
	{	
		//储存地址到x0
		int32_t temp_regno = simpleRegisterAllocator.Allocate(); // reg_allocator
		iloc.load_var(temp_regno, GepInst);
		if(!is_float_var)
		{
			//从[x0]中取出值到x0
			iloc.inst("ldr", PlatformArm64::regName[temp_regno], "[" + PlatformArm64::regName[temp_regno] + ", #0]");
			//把x0保存到result
			iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO);
		}
		else
		{
            int32_t temp_regno1 = simpleRegisterAllocator.Allocate(true);
            //从[x0]中取出值到s0
			iloc.inst("ldr", PlatformArm64::regNameS[temp_regno1], "[" + PlatformArm64::regName[temp_regno] + ", #0]");
			//把s0保存到result
			iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO, true);
			simpleRegisterAllocator.free(temp_regno1, true);
		}
			
		simpleRegisterAllocator.free(temp_regno);
	}
	else
	{
		if (arg1_regId != -1) {
			iloc.store_var(arg1_regId, result, ARM64_TMP_REG_NO, is_float_var);
		} else if (result_regId != -1) {
			iloc.load_var(result_regId, arg1, is_float_var, is_param);
		} else {
			int32_t temp_regno = simpleRegisterAllocator.Allocate(is_float_var);
			int32_t result_regno = simpleRegisterAllocator.Allocate(false, result);
			iloc.load_var(temp_regno, arg1, is_float_var, is_param);
			iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO, is_float_var);
			simpleRegisterAllocator.free(temp_regno, is_float_var);
		}
	}
    

}
// GEP和下一个Load的偏移都是112....
void InstSelectorArm64::translate_gep(Instruction * inst) {

	Instanceof(gepInst, GetElementPtrInstruction *, inst);
	Value * arg1 = gepInst->getOperand(0);
	Value * arg2 = gepInst->getOperand(1);
    Instanceof(castInst, BitcastInstruction *, arg1);

	Value * base_addr = castInst->getOperand(0);

	Value * result = gepInst;
	int32_t base_addr_regId = base_addr->getRegId();
    int32_t result_regId = result->getRegId();

    if (base_addr_regId != -1) {
        iloc.store_var(base_addr_regId, result, ARM64_TMP_REG_NO);
    } else if (result_regId != -1) {
        iloc.load_var(result_regId, base_addr);
    } else {
        int32_t temp_regno = simpleRegisterAllocator.Allocate();
		int32_t offset_regno = simpleRegisterAllocator.Allocate();
		//取出基地址
        iloc.load_var(temp_regno, base_addr);
		//把index存到offset_regno
		iloc.load_var(offset_regno, arg2);
		iloc.inst("lsl", PlatformArm64::regName[offset_regno], PlatformArm64::regName[offset_regno], "#2");
		// 计算具体地址
		iloc.inst("add", PlatformArm64::regName[temp_regno], PlatformArm64::regName[temp_regno], PlatformArm64::regName[offset_regno]);
        iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO);
        simpleRegisterAllocator.free(temp_regno);
		simpleRegisterAllocator.free(offset_regno);
    }

}

void InstSelectorArm64::translate_bitcast(Instruction * inst) {
	//bitcast 不生成对应指令，因为它只是一个 类型层面的转换，不改变内存地址或数据布局。
}

void InstSelectorArm64::translate_cast(Instruction * inst) {
	// cast指令用于将一个值转换为另一个类型
	// 这里假设只处理整数类型的转换
	Instanceof(castInst, CastInstruction *, inst);

    CastInstruction::CastKind castKind = castInst->kind;
    Value * src = castInst->getOperand(0);
	Value * dst = castInst;
	int32_t src_regId = src->getRegId();
	int32_t dst_regId = dst->getRegId();

	bool is_float_var = src->getType()->isFloatType();

	if (src_regId != -1) {
		iloc.store_var(src_regId, dst, ARM64_TMP_REG_NO, is_float_var);
	} else if (dst_regId != -1) {
		iloc.load_var(dst_regId, src, is_float_var);
	} else {
		int32_t temp_regno = simpleRegisterAllocator.Allocate(is_float_var);
		iloc.load_var(temp_regno, src, is_float_var);
		if(castKind == CastInstruction::CastKind::FPTOUI)
		{
			// 浮点到整数转换
			iloc.inst("fcvtzs", PlatformArm64::regNameS[temp_regno], PlatformArm64::regNameS[temp_regno]);
		}
		else if(castKind == CastInstruction::CastKind::UITOFP)
		{
			// 整数到浮点转换
			iloc.inst("scvtf", PlatformArm64::regNameW[temp_regno], PlatformArm64::regNameW[temp_regno]);
		}
		else if(castKind == CastInstruction::CastKind::SITOFP)
		{
			iloc.inst("scvtf", PlatformArm64::regNameW[temp_regno], PlatformArm64::regNameW[temp_regno]);
		}
		else if(castKind == CastInstruction::CastKind::FPTOSI)
		{
			iloc.inst("fcvtzs", PlatformArm64::regNameS[temp_regno], PlatformArm64::regNameS[temp_regno]);
		}
		else
		{
			printf("Error: Unsupported cast kind.\n");
			exit(1);

		}
		iloc.store_var(temp_regno, dst, ARM64_TMP_REG_NO, is_float_var);
		simpleRegisterAllocator.free(temp_regno, is_float_var);
	}
}

void InstSelectorArm64::translate_memset(Instruction * inst) {
    Instanceof(memsetInst, MemsetInstruction *, inst);
    
    // 提取 memset 的目标地址
    Value * op1 = memsetInst->getOperand(0);
    Instanceof(castInst, Instruction *, op1);
    Value * addr = castInst->getOperand(0);
    int32_t addr_reg = addr->getRegId();
	bool is_param = addr->isParam();

    if (addr_reg == -1) {
        addr_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(addr_reg, addr, is_param);
    }

    int64_t len = memsetInst->getSize();

    iloc.inst("sub", "sp", "sp", "#32");  // 分配栈空间
    iloc.inst("str", "x0", "[sp, #0]");
    iloc.inst("str", "x1", "[sp, #8]");
    iloc.inst("str", "x2", "[sp, #16]");
    iloc.inst("str", "lr", "[sp, #24]");

    iloc.inst("mov", "x0", PlatformArm64::regName[addr_reg]);                 // dest
    iloc.inst("mov", "w1", "#0");                                             // value
    iloc.inst("mov", "x2", "#" + std::to_string(len));                        // size
    iloc.inst("bl", "memset");

    iloc.inst("ldr", "x0", "[sp, #0]");
    iloc.inst("ldr", "x1", "[sp, #8]");
    iloc.inst("ldr", "x2", "[sp, #16]");
    iloc.inst("ldr", "lr", "[sp, #24]");
    iloc.inst("add", "sp", "sp", "#32");  // 回收栈空间

    // 回收 addr 寄存器
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
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate(false, dst);
    iloc.inst("add", PlatformArm64::regNameW[dst_reg], PlatformArm64::regNameW[lhs_reg], PlatformArm64::regNameW[rhs_reg]);
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
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate(false, dst);
    iloc.inst("sub", PlatformArm64::regNameW[dst_reg], PlatformArm64::regNameW[lhs_reg], PlatformArm64::regNameW[rhs_reg]);
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
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate(false, dst);
    iloc.inst("mul", PlatformArm64::regNameW[dst_reg], PlatformArm64::regNameW[lhs_reg], PlatformArm64::regNameW[rhs_reg]);
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
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate(false, dst);
    iloc.inst("sdiv", PlatformArm64::regNameW[dst_reg], PlatformArm64::regNameW[lhs_reg], PlatformArm64::regNameW[rhs_reg]);
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
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate(false, dst);
    iloc.inst("sdiv", PlatformArm64::regNameW[tmp_div], PlatformArm64::regNameW[lhs_reg], PlatformArm64::regNameW[rhs_reg]);
    iloc.inst("mul", PlatformArm64::regNameW[tmp_mul], PlatformArm64::regNameW[tmp_div], PlatformArm64::regNameW[rhs_reg]);
    iloc.inst("sub", PlatformArm64::regNameW[dst_reg], PlatformArm64::regNameW[lhs_reg], PlatformArm64::regNameW[tmp_mul]);
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
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate(false, dst);
	// 这里应该是32位寄存器进行比较，而不是64位寄存器，所以修改成Wx
    iloc.inst("cmp", PlatformArm64::toWReg(PlatformArm64::regName[lhs_reg]), PlatformArm64::toWReg(PlatformArm64::regName[rhs_reg]));
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
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate(false, dst);
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
	if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate(false, dst);
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
    if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate(false, dst);
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
	Value * funcVal = inst;
	int n = inst->getOperandsNum();
	int stack_arg_count = std::max(0, n - 8);
	int stack_arg_size = stack_arg_count * 8;
	if (stack_arg_size % 16 != 0) stack_arg_size = (stack_arg_size + 15) / 16 * 16;
	if (stack_arg_size > 0) {
		if(stack_arg_size <= 504) {
			iloc.inst("sub", "sp", "sp", iloc.toStr(stack_arg_size, false));
		} else {
			iloc.load_imm(ARM64_TMP_REG_NO, stack_arg_size);
			iloc.inst("sub", "sp", "sp", PlatformArm64::regName[ARM64_TMP_REG_NO]);
			simpleRegisterAllocator.free(ARM64_TMP_REG_NO);
		}
	}
	
	for (int i = 0; i < n; ++i) {
		Value * arg = inst->getOperand(i);
		int32_t reg = arg->getRegId();
		if (reg == -1) {
			reg = simpleRegisterAllocator.Allocate();
			iloc.load_var(reg, arg);
		}
	
		if (i < 8) {
			iloc.inst("mov", PlatformArm64::regName[i], PlatformArm64::regName[reg]);
		} else {
			std::string offset = iloc.toStr((i - 8) * 8, false);
			iloc.inst("str", PlatformArm64::regName[reg], "[sp, #" + offset + "]");
		}
		if (arg->getRegId() == -1) simpleRegisterAllocator.free(reg);
	}
	
	Instanceof(funcInst, FuncCallInstruction *, funcVal);
	iloc.inst("bl", funcInst->calledFunction->getName());
	
	if (stack_arg_size > 0) {
		if(stack_arg_size <= 504) {
			iloc.inst("add", "sp", "sp", iloc.toStr(stack_arg_size, false));
		} else {
			iloc.load_imm(ARM64_TMP_REG_NO, stack_arg_size);
			iloc.inst("add", "sp", "sp", PlatformArm64::regName[ARM64_TMP_REG_NO]);
			simpleRegisterAllocator.free(ARM64_TMP_REG_NO);
		}
	}
	
	// 返回值处理
	if (n > 0) {
		Value * ret = inst->getOperand(0);
		iloc.store_var(0, ret, ARM64_TMP_REG_NO);
	}
	
}

// 实参
void InstSelectorArm64::translate_arg(Instruction * inst) {
    // 通常参数传递已在translate_func_call处理
    
}

void InstSelectorArm64::translate_ZEXT(Instruction * inst) {
	// ZEXT指令用于将较小的整数类型扩展为较大的整数类型
	// 这里假设操作数0为源操作数，操作数1为目标操作数
	Value * src = inst->getOperand(0);
    Value * dst = inst;
    int32_t src_reg = src->getRegId();
	if (src_reg == -1) {
		src_reg = simpleRegisterAllocator.Allocate();
		iloc.load_var(src_reg, src);
	}
	iloc.store_var(src_reg, dst, ARM64_TMP_REG_NO);
	if (src->getRegId() == -1) simpleRegisterAllocator.free(src_reg);

}

// 浮点二元运算
void InstSelectorArm64::translate_fadd(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
    Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) { lhs_reg = simpleRegisterAllocator.AllocateFloat(lhs); iloc.load_var(lhs_reg, lhs); }
    if (rhs_reg == -1) { rhs_reg = simpleRegisterAllocator.AllocateFloat(rhs); iloc.load_var(rhs_reg, rhs); }
    if (dst_reg == -1) dst_reg = simpleRegisterAllocator.AllocateFloat(dst);
    iloc.inst("fadd", PlatformArm64::regNameS[dst_reg], PlatformArm64::regNameS[lhs_reg], PlatformArm64::regNameS[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.freeFloat(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.freeFloat(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.freeFloat(dst_reg);
}

void InstSelectorArm64::translate_fsub(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
    Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) { lhs_reg = simpleRegisterAllocator.AllocateFloat(lhs); iloc.load_var(lhs_reg, lhs); }
    if (rhs_reg == -1) { rhs_reg = simpleRegisterAllocator.AllocateFloat(rhs); iloc.load_var(rhs_reg, rhs); }
    if (dst_reg == -1) dst_reg = simpleRegisterAllocator.AllocateFloat(dst);
    iloc.inst("fsub", PlatformArm64::regNameS[dst_reg], PlatformArm64::regNameS[lhs_reg], PlatformArm64::regNameS[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.freeFloat(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.freeFloat(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.freeFloat(dst_reg);
}

void InstSelectorArm64::translate_fmul(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
    Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) { lhs_reg = simpleRegisterAllocator.AllocateFloat(lhs); iloc.load_var(lhs_reg, lhs); }
    if (rhs_reg == -1) { rhs_reg = simpleRegisterAllocator.AllocateFloat(rhs); iloc.load_var(rhs_reg, rhs); }
    if (dst_reg == -1) dst_reg = simpleRegisterAllocator.AllocateFloat(dst);
    iloc.inst("fmul", PlatformArm64::regNameS[dst_reg], PlatformArm64::regNameS[lhs_reg], PlatformArm64::regNameS[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.freeFloat(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.freeFloat(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.freeFloat(dst_reg);
}

void InstSelectorArm64::translate_fdiv(Instruction * inst) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
    Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    if (lhs_reg == -1) { lhs_reg = simpleRegisterAllocator.AllocateFloat(lhs); iloc.load_var(lhs_reg, lhs); }
    if (rhs_reg == -1) { rhs_reg = simpleRegisterAllocator.AllocateFloat(rhs); iloc.load_var(rhs_reg, rhs); }
    if (dst_reg == -1) dst_reg = simpleRegisterAllocator.AllocateFloat(dst);
    iloc.inst("fdiv", PlatformArm64::regNameS[dst_reg], PlatformArm64::regNameS[lhs_reg], PlatformArm64::regNameS[rhs_reg]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.freeFloat(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.freeFloat(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.freeFloat(dst_reg);
}


// 浮点比较通用实现
void InstSelectorArm64::translate_fcmp(Instruction * inst, IRInstOperator op) {
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
    Value * dst = inst;
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    int32_t dst_reg = dst->getRegId();
    if (lhs_reg == -1) { lhs_reg = simpleRegisterAllocator.AllocateFloat(lhs); iloc.load_var(lhs_reg, lhs); }
    if (rhs_reg == -1) { rhs_reg = simpleRegisterAllocator.AllocateFloat(rhs); iloc.load_var(rhs_reg, rhs); }
    if (dst_reg == -1) dst_reg = simpleRegisterAllocator.Allocate(dst); // 结果是int
    iloc.inst("fcmp", PlatformArm64::regNameS[lhs_reg], PlatformArm64::regNameS[rhs_reg]);
    // 浮点条件码映射
    const char* cond = nullptr;
    switch (op) {
        case IRInstOperator::IRINST_OP_EQ_F: cond = "eq"; break;
        case IRInstOperator::IRINST_OP_NE_F: cond = "ne"; break;
        case IRInstOperator::IRINST_OP_LT_F: cond = "lt"; break;
        case IRInstOperator::IRINST_OP_LE_F: cond = "le"; break;
        case IRInstOperator::IRINST_OP_GT_F: cond = "gt"; break;
        case IRInstOperator::IRINST_OP_GE_F: cond = "ge"; break;
        default: cond = "al"; break;
    }
    iloc.inst("cset", PlatformArm64::regName[dst_reg], cond);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    if (lhs->getRegId() == -1) simpleRegisterAllocator.freeFloat(lhs_reg);
    if (rhs->getRegId() == -1) simpleRegisterAllocator.freeFloat(rhs_reg);
    if (dst->getRegId() == -1) simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_feq(Instruction * inst) { translate_fcmp(inst, IRInstOperator::IRINST_OP_EQ_F); }
void InstSelectorArm64::translate_fne(Instruction * inst) { translate_fcmp(inst, IRInstOperator::IRINST_OP_NE_F); }
void InstSelectorArm64::translate_flt(Instruction * inst) { translate_fcmp(inst, IRInstOperator::IRINST_OP_LT_F); }
void InstSelectorArm64::translate_fle(Instruction * inst) { translate_fcmp(inst, IRInstOperator::IRINST_OP_LE_F); }
void InstSelectorArm64::translate_fgt(Instruction * inst) { translate_fcmp(inst, IRInstOperator::IRINST_OP_GT_F); }
void InstSelectorArm64::translate_fge(Instruction * inst) { translate_fcmp(inst, IRInstOperator::IRINST_OP_GE_F); }