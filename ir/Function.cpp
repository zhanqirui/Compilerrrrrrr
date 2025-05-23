///
/// @file Function.cpp
/// @brief 函数实现
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

#include <cstdlib>
#include <string>

#include "IRConstant.h"
#include "Function.h"
#include "PointerType.h"

/// @brief 指定函数名字、函数类型的构造函数
/// @param _name 函数名称
/// @param _type 函数类型
/// @param _builtin 是否是内置函数
Function::Function(std::string _name, FunctionType * _type, bool _builtin)
    : GlobalValue(_type, _name), builtIn(_builtin)
{
    returnType = _type->getReturnType();

    // 设置对齐大小
    setAlignment(1);
}

///
/// @brief 析构函数
/// @brief 释放函数占用的内存和IR指令代码
/// @brief 注意：IR指令代码并未释放，需要手动释放
Function::~Function()
{
    Delete();
}

/// @brief 获取函数返回类型
/// @return 返回类型
Type * Function::getReturnType()
{
    return returnType;
}

/// @brief 获取函数的形参列表
/// @return 形参列表
std::vector<FormalParam *> & Function::getParams()
{
    return params;
}

/// @brief 获取函数内的IR指令代码
/// @return IR指令代码
InterCode & Function::getInterCode()
{
    return code;
}

/// @brief 判断该函数是否是内置函数
/// @return true: 内置函数，false：用户自定义
bool Function::isBuiltin()
{
    return builtIn;
}
void Function::setBlockExitLabel(Instruction * inst)
{
    BlockExitLabel = inst;
}

/// @brief 获取函数出口指令
/// @return 出口Label指令
Instruction * Function::getBlockExitLabel()
{
    return BlockExitLabel;
}
int Function::getStride(const std::vector<int> & dims, int index)
{
    int stride = 1;
    for (int i = index + 1; i < dims.size(); ++i) {
        stride *= dims[i];
    }
    return stride;
}
/// @brief 递归处理多维数组
/// @param dims 当前维度信息
/// @param flattenedArray 展平后的数组
/// @param currentIndex 当前处理的维度索引
/// @param flatOffset 当前展平数组的偏移量
/// @return 返回多维数组的字符串表示
std::string Function::processMultiDimArray(Value * Var,
                                           const std::vector<int32_t> & dims,
                                           const std::vector<FlattenedArrayElement> & flattenedArray,
                                           size_t currentIndex,
                                           int32_t flatOffset)
{
    std::string result = "{";

    // 如果已经处理到最后一维
    if (currentIndex == dims.size() - 1) {
        for (int32_t i = 0; i < dims[currentIndex]; ++i) {
            int32_t flatIndex = flatOffset + i;
            bool found = false;

            // 查找展平数组中的值
            for (const auto & element: flattenedArray) {
                if (element.flatIndex == flatIndex) {

                    std::string x = (static_cast<const PointerType *>(Var->getType())->getRootType()->isIntegerType()
                                         ? std::to_string((int32_t) element.intValue)
                                         : std::to_string(element.floatValue)); // 找到值
                    result += x;
                    found = true;
                    break;
                }
            }

            // 如果找不到值，使用默认值 0
            if (!found) {
                result += "0";
            }

            // 添加逗号分隔符，最后一个元素不加逗号
            if (i < dims[currentIndex] - 1) {
                result += ", ";
            }
        }
    } else {
        // 递归处理下一维
        for (int32_t i = 0; i < dims[currentIndex]; ++i) {
            result += processMultiDimArray(Var,
                                           dims,
                                           flattenedArray,
                                           currentIndex + 1,
                                           flatOffset + i * getStride(dims, currentIndex));

            // 添加逗号分隔符，最后一个元素不加逗号
            if (i < dims[currentIndex] - 1) {
                result += ", ";
            }
        }
    }

    result += "}";
    return result;
}

/*
/// @brief 将所有内置函数转化成switch_case型
/// @param str

void Function::setDeclareString(std::string & str)
{
    static std::unordered_map<std::string, int> irMap = {{"@getint", 1},
                                                         {"@putint", 2},
                                                         {"@getch", 3},
                                                         {"@putch", 4},
                                                         {"@getarray", 5},
                                                         {"@putarray", 6},
                                                         {"@getfloat", 7},
                                                         {"@putfloat", 8},
                                                         {"@getfarray", 9},
                                                         {"@putfarray", 10},
                                                         {"@putstr", 11},
                                                         {"@putf", 12}};

    auto it = irMap.find(getIRName());
    if (it == irMap.end()) {
        str.clear(); // 未知内置函数，不设置任何内容
        return;
    }
    //具体的打印语句可能还需要做修改

    switch (it->second) {
        case 1:
            str = "declare i32 @getint(...) #1\n";
            break;
        case 2:
            str = "declare i32 @putint(...) #1\n";
            break;
        case 3:
            str = "declare i32 @getch(...) #1\n";
            break;
        case 4:
            str = "declare i32 @putch(...) #1\n";
            break;
        case 5:
            str = "declare i32 @getarray(...) #1\n";
            break;
        case 6:
            str = "declare i32 @putarray(...) #1\n";
            break;
        case 7:
            str = "declare i32 @getfloat(...) #1\n";
            break;
        case 8:
            str = "declare i32 @putfloat(...) #1\n";
            break;
        case 9:
            str = "declare i32 @getfarray(...) #1\n";
            break;
        case 10:
            str = "declare i32 @putfarray(...) #1\n";
            break;
        case 11:
            str = "declare i32 @putstr(...) #1\n";
            break;
        case 12:
            str = "declare i32 @putf(...) #1\n";
            break;
        default:
            str.clear();
            break;
    }
}
*/

/// @brief 函数指令信息输出
/// @param str 函数指令
void Function::toString(std::string & str)
{
    if (builtIn) {
        // 内置函数则不需要输出，由父函数的tostring解决

        return;
        // str = "declare " + getReturnType()->toString() + " " + getIRName() + "( " + ") #0\n";
    }

    // 输出函数头
    str = "define dso_local " + getReturnType()->toString() + " " + getIRName() + "(";

    bool firstParam = false;
    for (auto & param: params) {

        if (!firstParam) {
            firstParam = true;
        } else {
            str += ", ";
        }

        //先不考虑有默认值
        std::string param_str = param->getType()->toString() + " " + param->getIRName();

        str += param_str;
    }

    str += ") #0 ";

    str += "{\n";

    // 输出局部变量的名字与IR名字
    for (auto & var: this->varsVector) {
        // str += "\t";

        if (var->isConst()) {
            // 判断是否为 ConstVariable 类型并强转（前提是你确认变量来自该类）
            // Constant常量在LLVM IR中不需要打印出来
            // str += "Constant ";
        }

        // 局部变量和临时变量需要输出declare语句
        // str += "declare " + var->getType()->toString() + " " + var->getIRName();
        //修改为LLVM的alloca语句
        str += "  ";
        const std::vector<int32_t> dims = var->arraydimensionVector;
        if (!dims.empty()) {
            std::string arrayType = "";
            for (auto it = dims.begin(); it != dims.end(); ++it) {
                arrayType += "[" + std::to_string(*it) + " x ";
            }
            Type * baseType = var->getType(); // 获取类型
            PointerType * pointerType = dynamic_cast<PointerType *>(baseType);
            arrayType += pointerType->getRootType()->toString();
            for (size_t i = 0; i < dims.size(); ++i) {
                arrayType += "]";
            }
            str += var->getIRName() + " = alloca " + arrayType + ", align 16";
        } else {
            str += var->getIRName() + " = alloca " + var->getType()->toString() + ", " + "align 4";
        }
        std::string extraStr;
        std::string realName = var->getName();

        if (!realName.empty()) {
            //变量所处块信息在LLVM IR中不需要打印
            // str += " ; " + std::to_string(var->getScopeLevel()) + ":" + realName;
        }

        // ====== 新增：如果是常量变量，输出其值 ======

        str += "\n";
    }

    // 输出临时变量的declare形式
    // 遍历所有的线性IR指令，文本输出
    /*-----这一块还需要更改，临时变量需要更换，通过load指令先存临时变量而不是运算的结果，然后再存运算结果，然后再store------------------*/
    for (auto & inst: code.getInsts()) {

        if (inst->hasResultValue()) {

            // 局部变量和临时变量需要输出declare语句
            // str += "\tdeclare " + inst->getType()->toString() + " " + inst->getIRName() + "\n";
            // str += "\t" + inst->getIRName() + " = alloca " + inst->getType()->toString() + ", " + "align 4" + "\n";
        }
    }

    // 遍历所有的线性IR指令，文本输出
    for (auto & inst: code.getInsts()) {

        std::string instStr;
        inst->toString(instStr);

        if (!instStr.empty()) {

            // Label指令不加Tab键
            if (inst->getOp() == IRInstOperator::IRINST_OP_LABEL) {
                str += instStr + "\n";
            } else {
                str += "  " + instStr + "\n";
            }
        }
    }

    // 输出函数尾部
    str += "}\n";
}

/// @brief 设置函数出口指令
/// @param inst 出口Label指令
void Function::setExitLabel(Instruction * inst)
{
    exitLabel = inst;
}

/// @brief 获取函数出口指令
/// @return 出口Label指令
Instruction * Function::getExitLabel()
{
    return exitLabel;
}

/// @brief 设置函数返回值变量
/// @param val 返回值变量，要求必须是局部变量，不能是临时变量
void Function::setReturnValue(Value * val)
{
    returnValue = val;
}

/// @brief 获取函数返回值变量
/// @return 返回值变量
Value * Function::getReturnValue()
{
    return returnValue;
}

/// @brief 获取最大栈帧深度
/// @return 栈帧深度
int Function::getMaxDep()
{
    return maxDepth;
}

/// @brief 设置最大栈帧深度
/// @param dep 栈帧深度
void Function::setMaxDep(int dep)
{
    maxDepth = dep;

    // 设置函数栈帧被重定位标记，用于生成不同的栈帧保护代码
    relocated = true;
}

/// @brief 获取本函数需要保护的寄存器
/// @return 要保护的寄存器
std::vector<int32_t> & Function::getProtectedReg()
{
    return protectedRegs;
}

/// @brief 获取本函数需要保护的寄存器字符串
/// @return 要保护的寄存器
std::string & Function::getProtectedRegStr()
{
    return protectedRegStr;
}

/// @brief 获取函数调用参数个数的最大值
/// @return 函数调用参数个数的最大值
int Function::getMaxFuncCallArgCnt()
{
    return maxFuncCallArgCnt;
}

/// @brief 设置函数调用参数个数的最大值
/// @param count 函数调用参数个数的最大值
void Function::setMaxFuncCallArgCnt(int count)
{
    maxFuncCallArgCnt = count;
}

/// @brief 函数内是否存在函数调用
/// @return 是否存在函调用
bool Function::getExistFuncCall()
{
    return funcCallExist;
}

/// @brief 设置函数是否存在函数调用
/// @param exist true: 存在 false: 不存在
void Function::setExistFuncCall(bool exist)
{
    funcCallExist = exist;
}

/// @brief 新建变量型Value。先检查是否存在，不存在则创建，否则失败
/// @param name 变量ID
/// @param type 变量类型
/// @param scope_level 局部变量的作用域层级
LocalVariable *
Function::newLocalVarValue(Type * type, std::string name, int32_t scope_level, std::vector<int32_t> * _dimensions)
{
    // 创建变量并加入符号表
    LocalVariable * varValue = new LocalVariable(type, name, scope_level, _dimensions);

    // varsVector表中可能存在变量重名的信息
    varsVector.push_back(varValue);

    return varValue;
}
void Function::removeLocalVarByName(const std::string & name)
{
    for (auto it = varsVector.begin(); it != varsVector.end();) {
        if ((*it)->getName() == name) {
            delete *it;                // 如果你是 new 出来的对象，记得释放内存
            it = varsVector.erase(it); // 删除后返回下一个迭代器
        } else {
            ++it;
        }
    }
}

/// @brief 新建一个内存型的Value，并加入到符号表，用于后续释放空间
/// \param type 变量类型
/// \return 临时变量Value
MemVariable * Function::newMemVariable(Type * type)
{
    // 肯定唯一存在，直接插入即可
    MemVariable * memValue = new MemVariable(type);

    memVector.push_back(memValue);

    return memValue;
}

/// @brief 清理函数内申请的资源
void Function::Delete()
{
    // 清理IR指令
    code.Delete();

    // 清理Value
    for (auto & var: varsVector) {
        delete var;
    }

    varsVector.clear();
}
void Function::set_fun_return_Lable(LabelInstruction * LabelInst)
{
    return_Lable = LabelInst;
}
LabelInstruction * Function::get_fun_return_Lable()
{
    return return_Lable;
}
///
/// @brief 函数内的Value重命名
///
void Function::renameIR()
{
    // 内置函数忽略
    if (isBuiltin()) {
        return;
    }

    int32_t nameIndex = 0;

    // 形式参数重命名
    for (auto & param: this->params) {
        param->setIRName("%" + std::to_string(nameIndex++));
        // param->setIRName(IR_TEMP_VARNAME_PREFIX + std::to_string(nameIndex++));
    }
    for (auto inst: this->getInterCode().getInsts()) {
        if (inst->getOp() == IRInstOperator::IRINST_OP_ENTRY) {
            // inst->setIRName(IR_LABEL_PREFIX + std::to_string(nameIndex++));
            inst->setIRName("entry" + std::to_string(nameIndex++));
        }
    }
    // 局部变量重命名
    for (auto & var: this->varsVector) {

        // var->setIRName(IR_LOCAL_VARNAME_PREFIX + std::to_string(nameIndex++));
        var->setIRName("%" + std::to_string(nameIndex++));
    }

    // 遍历所有的指令进行命名
    for (auto inst: this->getInterCode().getInsts()) {
        if (inst->getOp() == IRInstOperator::IRINST_OP_LABEL) {
            // inst->setIRName(IR_LABEL_PREFIX + std::to_string(nameIndex++));
            inst->setIRName(std::to_string(nameIndex++));
        } else if (inst->hasResultValue()) {
            // inst->setIRName(IR_TEMP_VARNAME_PREFIX + std::to_string(nameIndex++));
            inst->setIRName("%" + std::to_string(nameIndex++));
        }
    }
}
void Function::BLOCK_SIMPLE_EN()
{
    // 内置函数忽略
    if (isBuiltin()) {
        return;
    }
    Instruction *left, *right;
    for (auto inst: this->getInterCode().getInsts()) {
        if (inst->getOp() == IRInstOperator::IRINST_OP_LABEL) {

        } else if (inst->hasResultValue()) {
        }
    }
}
///
/// @brief 获取统计的ARG指令的个数
/// @return int32_t 个数
///
int32_t Function::getRealArgcount()
{
    return this->realArgCount;
}

///
/// @brief 用于统计ARG指令个数的自增函数，个数加1
///
void Function::realArgCountInc()
{
    this->realArgCount++;
}

///
/// @brief 用于统计ARG指令个数的清零
///
void Function::realArgCountReset()
{
    this->realArgCount = 0;
}

void Function::set_block_entry_Lable(LabelInstruction * entryLabelInst)
{
    block_entry_Lable = entryLabelInst;
}
void Function::set_block_exit_Lable(LabelInstruction * exitLabelInst)
{
    block_exit_Lable = exitLabelInst;
}
LabelInstruction * Function::getblock_entry_Lable()
{
    return block_entry_Lable;
}
LabelInstruction * Function::getblock_exit_Lable()
{
    return block_exit_Lable;
}

void Function::set_ifelse_Lable1(LabelInstruction * LabelInst)
{
    ifelse_Lable1 = LabelInst;
}
void Function::set_ifelse_Lable2(LabelInstruction * LabelInst)
{
    ifelse_Lable2 = LabelInst;
}

LabelInstruction * Function::get_ifelse_Lable1()
{
    return ifelse_Lable1;
}
LabelInstruction * Function::get_ifelse_Lable2()
{
    return ifelse_Lable2;
}
void Function::set_ifelse_exit(LabelInstruction * LabelInst)
{
    ifelse_exitlabel = LabelInst;
}
LabelInstruction * Function::get_ifelse_exit()
{
    return ifelse_exitlabel;
}