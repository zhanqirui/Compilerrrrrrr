///
/// @file CodeGeneratorArm32.cpp
/// @brief ARM32的后端处理实现
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>新做
/// </table>
///
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "Function.h"
#include "Module.h"
#include "PlatformArm64.h"
#include "CodeGeneratorArm64.h"
#include "InstSelectorArm64.h"
#include "SimpleRegisterAllocator.h"
#include "ILocArm64.h"
#include "RegVariable.h"
#include "FuncCallInstruction.h"
#include "ArgInstruction.h"
#include "MoveInstruction.h"

/// @brief 构造函数
/// @param tab 符号表
CodeGeneratorArm64::CodeGeneratorArm64(Module * _module) : CodeGeneratorAsm(_module)
{}

/// @brief 析构函数
CodeGeneratorArm64::~CodeGeneratorArm64()
{}

/// @brief 产生汇编头部分
void CodeGeneratorArm64::genHeader()
{
    fprintf(fp, "%s\n", "	.arch armv8-a");
    // 可选: 输出文件名
    // fprintf(fp, ".file \"%s\"\n", module->getModuleName().c_str());
}

/// @brief 全局变量Section，主要包含初始化的和未初始化过的
void CodeGeneratorArm64::genDataSection()
{
    // 生成代码段
    fprintf(fp, "	.text\n");

    // 可直接操作文件指针fp进行写操作

    // 注意.bss和.data以及.text是不一样的，些指令都是切换段定义指令
	//.bss用来定义未初始化的全局变量
	// .data用来定义初始化的全局变量
	// .text用来定义代码段
    for (auto var: module->getGlobalVariables()) {
		Type* type = var->getType();
        std::string region = "";

		if(var->isConst()) {
			region = "section	.rodata";
		}
		else if(var->isInBSSSection()) {
			region = "bss";
		}
		else {
			region = "data";
		}

        int32_t size = type->isPointerType() ? var->getSize() : 4;
        fprintf(fp, "	.global %s\n", var->getName().c_str());
		fprintf(fp, "	.%s\n", region.c_str());
		fprintf(fp, "	.align %d\n", var->getAlignment());
		fprintf(fp, "	.type %s, %%object\n", var->getName().c_str());
		fprintf(fp, "	.size %s, %d\n\n", var->getName().c_str(), size);
		fprintf(fp, "%s:\n", var->getName().c_str());
		// TODO 后面设置初始化的值，具体请参考ARM的汇编
		if(var->isInBSSSection()) {
			fprintf(fp, "    .zero %d\n", size);
		}
		else
		{
			if(type->isIntegerType()) {
				fprintf(fp, "    .word %d\n", (var->real_int));
				
			}
			else if(type->isFloatType()) {
				fprintf(fp, "    .float %f\n", (var->real_float));
			}
			else if (type->isPointerType()) {
				const auto& flatted_array = var->flattenedArray;
				const auto& dim = var->arraydimensionVector;
			
				int unitSize = dim.empty() ? size / 4 : dim.back(); // 一行有多少元素（例如20）
				int totalElements = size / 4; // 总元素数
			
				int lastIndex = 0; // 上一个填充到的 flatIndex
				int currentRow = 0;
			
				for (const auto& elem : flatted_array) {
					// 每次补齐 gap 中的空元素
					while (lastIndex < elem.flatIndex) {
						// 若到了新的一行的起始
						if (lastIndex % unitSize == 0 && (elem.flatIndex - lastIndex) >= unitSize) {
							fprintf(fp, "    .zero %d\n", unitSize * 4);
							lastIndex += unitSize;
						} else {
							// 不满一整行，逐个填
							int gap = elem.flatIndex - lastIndex;
							fprintf(fp, "    .zero %d\n", gap * 4);
							lastIndex = elem.flatIndex;
						}
					}
			
					// 输出当前元素
					if (elem.is_use_val && elem.val != nullptr) {
						fprintf(fp, "    .word 0    // from val, please resolve\n");
					} else {
						fprintf(fp, "    .word %d\n", elem.intValue);
					}
					lastIndex = elem.flatIndex + 1;
			
					// 判断是否到达一行结尾，需要补齐该行末尾
					if (lastIndex % unitSize == 0) {
						// 已自动对齐，无需补
					}
				}
		
				int remainInRow = unitSize - (lastIndex % unitSize);
				if (remainInRow < unitSize) {
					fprintf(fp, "    .zero %d\n", remainInRow * 4);
					lastIndex += remainInRow;
				}
			
				// 补剩下完整的未初始化行
				if (lastIndex < totalElements) {
					fprintf(fp, "    .zero %d\n", (totalElements - lastIndex) * 4);
				}
			}
			
			else
			{
				printf("unsupport type in  global variable\n");
			}
		}
		
	}
}

///
/// @brief 获取IR变量相关信息字符串
/// @param str
///
void CodeGeneratorArm64::getIRValueStr(Value * val, std::string & str)
{
    std::string name = val->getName();
    std::string IRName = val->getIRName();
    int32_t regId = val->getRegId();
    int32_t baseRegId;
    int64_t offset;
    std::string showName;

    if (name.empty() && (!IRName.empty())) {
        showName = IRName;
    } else if ((!name.empty()) && IRName.empty()) {
        showName = IRName;
    } else if ((!name.empty()) && (!IRName.empty())) {
        showName = name + ":" + IRName;
    } else {
        showName = "";
    }

    if (regId != -1) {
        // 寄存器
        str += "\t@ " + showName + ":" + PlatformArm64::regName[regId];
    } else if (val->getMemoryAddr(&baseRegId, &offset)) {
        // 栈内寻址，[fp,#4]
        str += "\t@ " + showName + ":[" + PlatformArm64::regName[baseRegId] + ",#" + std::to_string(offset) + "]";
    }
}

/// @brief 针对函数进行汇编指令生成，放到.text代码段中
/// @param func 要处理的函数
void CodeGeneratorArm64::genCodeSection(Function * func)
{
    // 寄存器分配以及栈内局部变量的站内地址重新分配
    registerAllocation(func);

    // 获取函数的指令列表
    std::vector<Instruction *> & IrInsts = func->getInterCode().getInsts();

    // 汇编指令输出前要确保Label的名字有效，必须是程序级别的唯一，而不是函数内的唯一。要全局编号。
    for (auto inst: IrInsts) {
        if (inst->getOp() == IRInstOperator::IRINST_OP_LABEL) {
            inst->setName(IR_LABEL_PREFIX + std::to_string(labelIndex++));
        }
    }

    // ILOC代码序列
    ILocArm64 iloc(module);

    // 指令选择生成汇编指令
    InstSelectorArm64 instSelector(IrInsts, iloc, func, simpleRegisterAllocator);
    instSelector.setShowLinearIR(this->showLinearIR);
    instSelector.run();

    // 删除无用的Label指令
    iloc.deleteUsedLabel();

    // ILOC代码输出为汇编代码
    fprintf(fp, "\n.align %d\n", func->getAlignment());
    fprintf(fp, ".global %s\n", func->getName().c_str());
    fprintf(fp, ".type %s, %%function\n", func->getName().c_str());
    fprintf(fp, "%s:\n", func->getName().c_str());

    // 开启时输出IR指令作为注释
    if (this->showLinearIR) {

        // 输出有关局部变量的注释，便于查找问题
        for (auto localVar: func->getVarValues()) {
            std::string str;
            getIRValueStr(localVar, str);
            if (!str.empty()) {
                fprintf(fp, "//%s\n", str.c_str());
            }
        }

        // 输出指令关联的临时变量信息
        for (auto inst: func->getInterCode().getInsts()) {
            if (inst->hasResultValue()) {
                std::string str;
                getIRValueStr(inst, str);
                if (!str.empty()) {
                    fprintf(fp, "//%s\n", str.c_str());
                }
            }
        }
    }

    iloc.outPut(fp);
}

/// @brief 寄存器分配
/// @param func 函数指针
void CodeGeneratorArm64::registerAllocation(Function * func)
{
    // 内置函数不需要处理
    if (func->isBuiltin()) {
        return;
    }

    // ARM64平台寄存器约定：
    // x0-x7: 参数和返回值寄存器(调用者保存)
    // x8-x18: 临时寄存器(调用者保存)
    // x19-x28: 被调用者保存的寄存器
    // x29(fp): 帧指针
    // x30(lr): 链接寄存器(返回地址)
    // sp: 栈指针

    std::vector<int32_t> & protectedRegNo = func->getProtectedReg();
    protectedRegNo.clear();
    protectedRegNo.push_back(ARM64_FP_REG_NO);  // x29
    if (func->getExistFuncCall()) {
        protectedRegNo.push_back(ARM64_LR_REG_NO);  // x30
    }

    // 先分配局部变量的栈空间
    stackAlloc(func);
    
    // 再调整函数调用指令，为调用其他函数准备参数
    adjustFuncCallInsts(func);

    // 最后处理函数形参
    adjustFormalParamInsts(func);
}

/// @brief 寄存器分配前对函数内的指令进行调整，以便方便寄存器分配
/// @param func 要处理的函数
void CodeGeneratorArm64::adjustFormalParamInsts(Function * func)
{
    // 函数形参的前八个实参采用寄存器传值 (x0-x7)
    auto & params = func->getParams();

    // 形参的前八个通过寄存器来传值x0-x7
    for (int k = 0; k < (int) params.size() && k <= 7; k++) {
        // 前八个设置分配寄存器
        simpleRegisterAllocator.bitmapSet(k);
        params[k]->setRegId(k);
    }

    // 根据ARM64版C语言的调用约定，除前8个外的实参进行值传递
    // 这些参数位于调用者的栈帧中，通过FP+正偏移量访问
    int64_t param_offset = 16;  // 从FP+16开始访问参数(跳过保存的FP和LR)
    for (int k = 8; k < (int) params.size(); k++) {
        // ARM64架构下变量需要8字节对齐
        params[k]->setMemoryAddr(ARM64_FP_REG_NO, param_offset);  // 使用FP基址寄存器，正偏移量
        param_offset += 8;  // ARM64平台参数大小为8字节
    }
}

/// @brief 寄存器分配前对函数内的指令进行调整，以便方便寄存器分配
/// @param func 要处理的函数
void CodeGeneratorArm64::adjustFuncCallInsts(Function * func)
{
    // 当前函数的指令列表
    auto & insts = func->getInterCode().getInsts();

    // 获取已分配的局部变量栈帧大小
    int32_t local_vars_size = func->getMaxDep();
    
    // 为函数调用参数预留的栈空间从局部变量区域之后开始
    // 这样避免与局部变量区域冲突
    int param_area_base = local_vars_size;
	
    // 函数返回值用x0寄存器
    for (auto pIter = insts.begin(); pIter != insts.end(); pIter++) {
        // 检查是否是函数调用指令
        if (Instanceof(callInst, FuncCallInstruction *, *pIter)) {
            // 处理超过8个的参数，它们需要通过栈传递
            // 参数区域偏移量从局部变量区域之后开始
            int param_offset = param_area_base;
			int params_num = callInst->getOperandsNum();
            
            for (int32_t k = 8; k < callInst->getOperandsNum(); k++) {
                auto arg = callInst->getOperand(k);

                // 新建一个内存变量，用于栈传值到形参变量中
                // 注意：这里使用SP作为基址寄存器，偏移量从局部变量区域之后开始
                LocalVariable * newVal = func->newLocalVarValue(IntegerType::getTypeInt());
                newVal->setMemoryAddr(ARM64_SP_REG_NO, param_offset);  // 使用SP + 局部变量区域大小 + 参数偏移
                param_offset += 8;  // ARM64平台参数大小为8字节

                Instruction * assignInst = new MoveInstruction(func, newVal, arg);
                callInst->setOperand(k, newVal);
                pIter = insts.insert(pIter, assignInst);
                pIter++;
            }

            // 处理前8个参数，它们通过寄存器传递
            for (int k = 0; k < callInst->getOperandsNum() && k < 8; k++) {
                auto arg = callInst->getOperand(k);

                if (arg->getRegId() == k) {
                    // 寄存器已经正确，不需要额外处理
                    continue;
                } else {
                    // 创建临时变量，指定寄存器
                    Instruction * assignInst =
                        new MoveInstruction(func, PlatformArm64::intRegVal[k], callInst->getOperand(k));

                    simpleRegisterAllocator.bitmapSet(k);
                    callInst->setOperand(k, PlatformArm64::intRegVal[k]);
                    pIter = insts.insert(pIter, assignInst);
                    pIter++;
                }
            }

            // 处理函数返回值
            if (callInst->hasResultValue()) {
                if (callInst->getRegId() == 0) {
                    // 结果已在x0中，不需要额外处理
                } else {
                    // 将x0中的返回值移动到目标位置
                    Instruction * assignInst = new MoveInstruction(func, callInst, PlatformArm64::intRegVal[0]);
                    pIter = insts.insert(pIter + 1, assignInst);
                }
            }
        }
    }
    
    // 计算所有函数调用中需要的最大参数空间
    int max_args_space = 0;
    for (auto inst: insts) {
        if (Instanceof(callInst, FuncCallInstruction *, inst)) {
            int args_cnt = callInst->getOperandsNum();
            if (args_cnt > 8) {
                // 只计算超过8个参数后需要栈传递的部分
                int args_space = (args_cnt - 8) * 8;
                max_args_space = std::max(max_args_space, args_space);
            }
        }
    }
    
    // 记录调用其他函数时需要的最大参数数量
    func->setMaxFuncCallArgCnt(max_args_space / 8 + 8);
}

/// @brief 栈空间分配
/// @param func 要处理的函数
void CodeGeneratorArm64::stackAlloc(Function * func)
{
    // 确定使用哪种栈帧布局
    bool useFramePointer = !func->getProtectedReg().empty();
    
    // 栈变量分配起始偏移量
    int32_t var_offset = 0;
    
    // 获取函数变量列表
    std::vector<LocalVariable *> & vars = func->getVarValues();

    // 遍历所有局部变量进行栈空间分配
    for (auto var: vars) {
        // 只处理未分配寄存器且未分配内存地址的变量
        if ((var->getRegId() == -1) && (!var->getMemoryAddr())) {
            int32_t size;
            Type * type = var->getType();
            
            // 计算变量大小
            if(type->isPointerType()) {
                // 数组类型，计算总大小
                int32_t dims = 1;
                for(auto dim: var->arraydimensionVector) {
                    dims *= dim;
                }
				if(dims < 0)
				{
                    size = 8;
                }
				else
				{
					size = dims * 8;  // ARM64指针/数组元素大小为8字节
				}
            } else {
                size = var->getType()->getSize();
            }
            
            // 64位ARM平台按照8字节对齐
            size += (8 - size % 8) % 8;

            // 所有局部变量通过SP的正偏移量访问
            // 这与生成的标准汇编代码一致
            var->setMemoryAddr(ARM64_SP_REG_NO, var_offset);
            
            // 累加偏移量，确保下一个变量不会与当前变量重叠
            var_offset += size;
        }
    }

    // 遍历指令中临时变量，与局部变量采用相同的分配策略
    for (auto inst: func->getInterCode().getInsts()) {
        if (inst->hasResultValue() && inst->getRegId() == -1 && !inst->getMemoryAddr()) {
            int32_t size = inst->getType()->getSize();
            
            // 64位ARM平台按照8字节对齐
            size += (8 - size % 8) % 8;

            // 临时变量也通过SP的正偏移量访问
            inst->setMemoryAddr(ARM64_SP_REG_NO, var_offset);
            
            // 累加偏移量，确保不重叠
            var_offset += size;
        }
    }

    // 确保栈帧16字节对齐(ARM64 ABI要求)
    if (var_offset % 16 != 0) {
        var_offset += 16 - (var_offset % 16);
    }
    
    // 记录函数的局部变量区域总大小
    func->setMaxDep(var_offset);
}