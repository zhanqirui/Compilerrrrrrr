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
                fprintf(fp, "%s\n", str.c_str());
            }
        }

        // 输出指令关联的临时变量信息
        for (auto inst: func->getInterCode().getInsts()) {
            if (inst->hasResultValue()) {
                std::string str;
                getIRValueStr(inst, str);
                if (!str.empty()) {
                    fprintf(fp, "%s\n", str.c_str());
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

    // 最简单/朴素的寄存器分配策略：局部变量和临时变量都保存在栈内，全局变量在静态存储.data区中
    // R0,R1,R2和R3寄存器不需要保护，可直接使用
    // SP寄存器预留，不需要保护，但需要保证值的正确性
    // R4-R10, fp(11), lx(14)都需要保护，没有函数调用的函数可不用保护lx寄存器
    // 被保留的寄存器主要有：
    //  (1) FP寄存器用于栈寻址，即R11
    //  (2) LX寄存器用于函数调用，即R14。没有函数调用的函数可不用保护lx寄存器
    //  (3) R10寄存器用于立即数过大时要通过寄存器寻址，这里简化处理进行预留

    std::vector<int32_t> & protectedRegNo = func->getProtectedReg();
    protectedRegNo.clear();
    protectedRegNo.push_back(ARM64_FP_REG_NO);
    if (func->getExistFuncCall()) {
        protectedRegNo.push_back(ARM64_LR_REG_NO);
    }

    // 调整函数调用指令，主要是前四个寄存器传值，后面用栈传递
    // 为了更好的进行寄存器分配，可以进行对函数调用的指令进行预处理
    // 当然也可以不做处理，不过性能更差。这个处理是可选的。
    adjustFuncCallInsts(func);

    // 为局部变量和临时变量在栈内分配空间，指定偏移，进行栈空间的分配
    stackAlloc(func);

    // 函数形参要求前四个寄存器分配，后面的参数采用栈传递，实现实参的值传递给形参
    // 这一步是必须的
    adjustFormalParamInsts(func);

#if 0
    // 临时输出调整后的IR指令，用于查看当前的寄存器分配、栈内变量分配、实参入栈等信息的正确性
    std::string irCodeStr;
    func->toString(irCodeStr);
    std::cout << irCodeStr << std::endl;
#endif
}

/// @brief 寄存器分配前对函数内的指令进行调整，以便方便寄存器分配
/// @param func 要处理的函数
void CodeGeneratorArm64::adjustFormalParamInsts(Function * func)
{
    // 函数形参的前四个实参值临时变量采用的是寄存器传值
    // 前四个之后通过栈传递

    // 请注意这里所得的所有形参都是对应的实参的值关联的临时变量
    // 如果不是不能使用这里的代码
    auto & params = func->getParams();

    // 形参的前八个通过寄存器来传值R0-R7
    for (int k = 0; k < (int) params.size() && k <= 7; k++) {

        // 前四个设置分配寄存器
		simpleRegisterAllocator.bitmapSet(k);
        params[k]->setRegId(k);
    }

    // 根据ARM版C语言的调用约定，除前4个外的实参进行值传递，逆序入栈
    int64_t fp_esp = func->getMaxDep() + (func->getProtectedReg().size() * 4);
    for (int k = 4; k < (int) params.size(); k++) {

        // 目前假定变量大小都是4字节。实际要根据类型来计算

        params[k]->setMemoryAddr(ARM64_FP_REG_NO, fp_esp);

        // 增加4字节
        fp_esp += 4;
    }
}

/// @brief 寄存器分配前对函数内的指令进行调整，以便方便寄存器分配
/// @param func 要处理的函数
void CodeGeneratorArm64::adjustFuncCallInsts(Function * func)
{
    std::vector<Instruction *> newInsts;

    // 当前函数的指令列表
    auto & insts = func->getInterCode().getInsts();

    // 函数返回值用R0寄存器，若函数调用有返回值，则赋值R0到对应寄存器
    for (auto pIter = insts.begin(); pIter != insts.end(); pIter++) {

        // 检查是否是函数调用指令，并且含有返回值
        if (Instanceof(callInst, FuncCallInstruction *, *pIter)) {

            // 实参前八个要寄存器传值，其它参数通过栈传递

            // 前八个的后面参数采用栈传递
            int esp = 0;
            for (int32_t k = 8; k < callInst->getOperandsNum(); k++) {

                auto arg = callInst->getOperand(k);

                // 新建一个内存变量，用于栈传值到形参变量中
                LocalVariable * newVal = func->newLocalVarValue(IntegerType::getTypeInt());
                newVal->setMemoryAddr(ARM64_SP_REG_NO, esp);
                esp += 8;

                Instruction * assignInst = new MoveInstruction(func, newVal, arg);

                callInst->setOperand(k, newVal);

                // 函数调用指令前插入后，pIter仍指向函数调用指令
                pIter = insts.insert(pIter, assignInst);
                pIter++;
            }

            for (int k = 0; k < callInst->getOperandsNum() && k < 8; k++) {

                // 检查实参的类型是否是临时变量。
                // 如果是临时变量，该变量可更改为寄存器变量即可，或者设置寄存器号
                // 如果不是，则必须开辟一个寄存器变量，然后赋值即可
                auto arg = callInst->getOperand(k);

                if (arg->getRegId() == k) {
                    // 则说明寄存器已经是实参传递的寄存器，不用创建赋值指令
                    continue;
                } else {
                    // 创建临时变量，指定寄存器
                    Instruction * assignInst =
                        new MoveInstruction(func, PlatformArm64::intRegVal[k], callInst->getOperand(k));

                    simpleRegisterAllocator.bitmapSet(k);
                    callInst->setOperand(k, PlatformArm64::intRegVal[k]);

                    // 函数调用指令前插入后，pIter仍指向函数调用指令
                    pIter = insts.insert(pIter, assignInst);
                    pIter++;
                }
            }

            for (int k = 0; k < callInst->getOperandsNum(); k++) {

                auto arg = callInst->getOperand(k);

                // 再产生ARG指令
                pIter = insts.insert(pIter, new ArgInstruction(func, arg));
                pIter++;
            }

            // 有arg指令后可不用参数，展示不删除
            // args.clear();

            // 赋值指令
            if (callInst->hasResultValue()) {

                if (callInst->getRegId() == 0) {
                    // 结果变量的寄存器和返回值寄存器一样，则什么都不需要做
                    ;
                } else {
                    // 其它情况，需要产生赋值指令
                    // 新建一个赋值操作
                    Instruction * assignInst = new MoveInstruction(func, callInst, PlatformArm64::intRegVal[0]);

                    // 函数调用指令的下一个指令的前面插入指令，因为有Exit指令，+1肯定有效
                    pIter = insts.insert(pIter + 1, assignInst);
                }
            }
        }
    }
}

/// @brief 栈空间分配
/// @param func 要处理的函数
void CodeGeneratorArm64::stackAlloc(Function * func)
{
    // 遍历函数内的所有指令，查找没有寄存器分配的变量，然后进行栈内空间分配

    // 这里对临时变量和局部变量都在栈上进行分配,但形参对应实参的临时变量(FormalParam类型)不需要考虑

    int32_t sp_esp = 0;

    // 获取函数变量列表
    std::vector<LocalVariable *> & vars = func->getVarValues();

    for (auto var: vars) {

        // 对于简单类型的寄存器分配策略，假定临时变量和局部变量都保存在栈中，属于内存
        // 而对于图着色等，临时变量一般是寄存器，局部变量也可能修改为寄存器
        // TODO 考虑如何进行分配使得临时变量尽量保存在寄存器中，作为优化点考虑

        // regId不为-1，则说明该变量分配为寄存器
        // baseRegNo不等于-1，则说明该变量肯定在栈上，属于内存变量，之前肯定已经分配过
        if ((var->getRegId() == -1) && (!var->getMemoryAddr())) {

            int32_t size;
            // 该变量没有分配寄存器
			Type * type = var->getType();
			if(type->isPointerType()) {
                int32_t dims = 1;
                for(auto dim: var->arraydimensionVector) {
					dims *= dim;
				}
				size = dims * 4;
			}	
			else
			{
				size = var->getType()->getSize();
			}
            

            // // 32位ARM平台按照4字节的大小整数倍分配局部变量
            // size += (4 - size % 4) % 4;
			// 64位arm平台
			// 64位ARM平台按照8字节的大小整数倍分配局部变量
			size += (8 - size % 8) % 8;


            // 这里要注意检查变量栈的偏移范围。一般采用机制寄存器+立即数方式间接寻址
            // 若立即数满足要求，可采用基址寄存器+立即数变量的方式访问变量
            // 否则，需要先把偏移量放到寄存器中，然后机制寄存器+偏移寄存器来寻址
            // 之后需要对所有使用到该Value的指令在寄存器分配前要变换。

            // 局部变量偏移设置
            var->setMemoryAddr(ARM64_FP_REG_NO, sp_esp);

            // 累计当前作用域大小
            sp_esp += size;
        }
    }

    // 遍历指令中临时变量
    for (auto inst: func->getInterCode().getInsts()) {

        if (inst->hasResultValue()) {
            // 有值

            int32_t size = inst->getType()->getSize();

            // 32位ARM平台按照4字节的大小整数倍分配局部变量
            size += (8 - size % 8) % 8;

            // 这里要注意检查变量栈的偏移范围。一般采用机制寄存器+立即数方式间接寻址
            // 若立即数满足要求，可采用基址寄存器+立即数变量的方式访问变量
            // 否则，需要先把偏移量放到寄存器中，然后机制寄存器+偏移寄存器来寻址
            // 之后需要对所有使用到该Value的指令在寄存器分配前要变换。

            // 局部变量偏移设置
            inst->setMemoryAddr(ARM64_FP_REG_NO, sp_esp);

            // 累计当前作用域大小
            sp_esp += size;
        }
    }

    // 设置函数的最大栈帧深度，在加上实参内存传值的空间
    // 请注意若支持浮点数，则必须保持栈内空间8字节对齐
    // --- 保证16字节对齐 ---
    if (sp_esp % 16 != 0) {
        sp_esp += 16 - (sp_esp % 16);
    }
    func->setMaxDep(sp_esp);
}
