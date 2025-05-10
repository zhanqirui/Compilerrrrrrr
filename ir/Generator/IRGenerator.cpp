///
/// @file IRGenerator.cpp
/// @brief AST遍历产生线性IR的源文件
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-09-29 <td>1.0     <td>zenglj  <td>新建
/// </table>
///
#include <cstdint>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <AttrType.h>
#include "AST.h"
#include "Common.h"
#include "Function.h"
#include "IRCode.h"
#include "IRGenerator.h"
#include "Module.h"
#include "PointerType.h"
#include "EntryInstruction.h"
#include "LabelInstruction.h"
#include "ExitInstruction.h"
#include "MoveInstruction.h"
#include "GotoInstruction.h"
#include "FuncCallInstruction.h"
#include "ArgInstruction.h"
#include "BinaryInstruction.h"
#include "StoreInstruction.h"
#include "BranchifCondition.h"
#include "UnaryInstruction.h"
/// @brief 构造函数
/// @param _root AST的根
/// @param _module 符号表
IRGenerator::IRGenerator(ast_node * _root, Module * _module) : root(_root), module(_module)
{
    /* 叶子节点 */
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_LITERAL_UINT] = &IRGenerator::ir_leaf_node_uint;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_TYPE] = &IRGenerator::ir_leaf_node_type;
    ast2ir_handlers[ast_operator_type::AST_OP_LVAL] = &IRGenerator::ir_leaf_node_var_id;

    /* 表达式运算， 加减 */
    ast2ir_handlers[ast_operator_type::AST_OP_EXP] = &IRGenerator::ir_visitExp;
    ast2ir_handlers[ast_operator_type::AST_OP_ADD_EXP] = &IRGenerator::ir_add;
    ast2ir_handlers[ast_operator_type::AST_OP_MUL_EXP] = &IRGenerator::ir_mul;
    ast2ir_handlers[ast_operator_type::AST_OP_REL_EXP] = &IRGenerator::ir_visitConfExp;
    ast2ir_handlers[ast_operator_type::AST_OP_EQ_EXP] = &IRGenerator::ir_visitConfExp;
    ast2ir_handlers[ast_operator_type::AST_OP_LAND_EXP] = &IRGenerator::ir_visitLogitExp;
    ast2ir_handlers[ast_operator_type::AST_OP_LOR_EXP] = &IRGenerator::ir_visitLogitExp;
    ast2ir_handlers[ast_operator_type::AST_OP_CONST_EXP] = &IRGenerator::ir_visitExp;
    // 一元表达式AST_OP_UNARY_EXP
    ast2ir_handlers[ast_operator_type::AST_OP_UNARY_EXP] = &IRGenerator::ir_visitUNARYExp;
    ast2ir_handlers[ast_operator_type::AST_OP_UNARY_OP] = &IRGenerator::ir_visitUNARYOP;
    // const 数组
    ast2ir_handlers[ast_operator_type::AST_OP_CONST_DECL] = &IRGenerator::ir_const_declare;
    // 数组访问
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_ACCESS] = &IRGenerator::ir_array_acess;
    /* 语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_ASSIGN_STMT] = &IRGenerator::ir_assign;
    ast2ir_handlers[ast_operator_type::AST_OP_RETURN] = &IRGenerator::ir_return;
    /* 变量定义语句 */

    ast2ir_handlers[ast_operator_type::AST_OP_VAR_DECL] = &IRGenerator::ir_variable_declare;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_VAR_DEF] = &IRGenerator::ir_array_var_def_declare;
    ast2ir_handlers[ast_operator_type::AST_OP_VAR_DEF] = &IRGenerator::ir_var_def;
    //初始化
    ast2ir_handlers[ast_operator_type::AST_OP_SCALAR_INIT] = &IRGenerator::ir_scalar_init;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_INIT_VAL] = &IRGenerator::ir_scalar_init;
    ast2ir_handlers[ast_operator_type::AST_OP_SCALAR_CONST_INIT] = &IRGenerator::ir_scalar_init;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_CONST_DEF] = &IRGenerator::ir_scalar_init;

    /* 函数定义 */
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_DEF] = &IRGenerator::ir_function_define;
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGenerator::ir_function_formal_params;
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_CALL] = &IRGenerator::ir_func_call; // 注册函数调用
    /* 语句块 */
    ast2ir_handlers[ast_operator_type::AST_OP_BLOCK] = &IRGenerator::ir_block;
    ast2ir_handlers[ast_operator_type::AST_OP_IF_ELSE_STMT] = &IRGenerator::ir_if_else;
    ast2ir_handlers[ast_operator_type::AST_OP_NESTED_BLOCK] = &IRGenerator::ir_nested_block;
    ast2ir_handlers[ast_operator_type::AST_OP_WHILE] = &IRGenerator::ir_while;

    /* 编译单元 */
    ast2ir_handlers[ast_operator_type::AST_OP_COMPILE_UNIT] = &IRGenerator::ir_compile_unit;

    /*常量int,float的定义*/
    ast2ir_handlers[ast_operator_type::AST_OP_CONST_DEF] = &IRGenerator::ir_const_def;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_CONST_DEF] = &IRGenerator::ir_const_array_var_def_declare;
}

/// @brief 遍历抽象语法树产生线性IR，保存到IRCode中
/// @param root 抽象语法树
/// @param IRCode 线性IR
/// @return true: 成功 false: 失败
bool IRGenerator::run()
{
    ast_node * node;

    // 从根节点进行遍历
    node = ir_visit_ast_node(root);

    return node != nullptr;
}

/// @brief 根据AST的节点运算符查找对应的翻译函数并执行翻译动作
/// @param node AST节点
/// @return 成功返回node节点，否则返回nullptr
ast_node * IRGenerator::ir_visit_ast_node(ast_node * node)
{
    // 空节点
    if (nullptr == node) {
        return nullptr;
    }

    bool result;

    std::unordered_map<ast_operator_type, ast2ir_handler_t>::const_iterator pIter;
    pIter = ast2ir_handlers.find(node->node_type);
    if (pIter == ast2ir_handlers.end()) {
        // 没有找到，则说明当前不支持
        result = (this->ir_default)(node);
    } else {
        result = (this->*(pIter->second))(node);
    }

    if (!result) {
        // 语义解析错误，则出错返回
        node = nullptr;
    }

    return node;
}

/// @brief 未知节点类型的节点处理
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_default(ast_node * node)
{
    // 未知的节点
    printf("Unkown node(%d)\n", (int) node->node_type);
    return true;
}

/// @brief 编译单元AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_compile_unit(ast_node * node)
{
    module->setCurrentFunction(nullptr);
    ast_node * son_node;
    for (auto son: node->sons) {
        if (son->node_type == ast_operator_type::AST_OP_FUNC_DEF) { // 遍历编译单元，要么是函数定义，要么是语句
            son_node = ir_visit_ast_node(son);
        } else {
            son_node = ir_global(son);
        }
        if (!son_node) {
            // TODO 自行追加语义错误处理
            return false;
        }
    }

    return true;
}

/// @brief 函数定义AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_function_define(ast_node * node)
{
    bool result;

    // 创建一个函数，用于当前函数处理
    if (module->getCurrentFunction()) {
        // 函数中嵌套定义函数，这是不允许的，错误退出
        // TODO 自行追加语义错误处理
        return false;
    }

    // 函数定义的AST包含四个孩子
    // 第一个孩子：函数返回类型
    // 第二个孩子：函数名字
    // 第三个孩子：形参列表
    // 第四个孩子：函数体即block
    ast_node * type_node = node->sons[0];
    ast_node * name_node = node->sons[1];
    ast_node * param_node = node->sons[2];
    ast_node * block_node = node->sons[3];

    // 创建一个新的函数定义
    Function * newFunc = module->newFunction(name_node->name, type_node->type);
    if (!newFunc) {
        // 新定义的函数已经存在，则失败返回。
        // TODO 自行追加语义错误处理
        return false;
    }

    // 当前函数设置有效，变更为当前的函数
    module->setCurrentFunction(newFunc);

    // 进入函数的作用域
    module->enterScope();

    // 获取函数的IR代码列表，用于后面追加指令用，注意这里用的是引用传值
    InterCode & irCode = newFunc->getInterCode();

    // 这里也可增加一个函数入口Label指令，便于后续基本块划分

    // 创建并加入Entry入口指令
    irCode.addInst(new EntryInstruction(newFunc));

    // 创建出口指令并不加入出口指令，等函数内的指令处理完毕后加入出口指令
    LabelInstruction * entryLabelInst = new LabelInstruction(newFunc);

    // 函数出口指令保存到函数信息中，因为在语义分析函数体时return语句需要跳转到函数尾部，需要这个label指令
    newFunc->setExitLabel(entryLabelInst);

    // 遍历形参，没有IR指令，不需要追加
    result = ir_function_formal_params(param_node);
    if (!result) {
        // 形参解析失败
        // TODO 自行追加语义错误处理
        return false;
    }
    node->blockInsts.addInst(param_node->blockInsts);

    // --- 新增：将形参寄存器赋值给局部变量 ---
    {
        Function * curFunc = module->getCurrentFunction();
        if (curFunc) {
            auto & params = curFunc->getParams();
            auto & locals = curFunc->getVarValues();
            for (auto * param: params) {
                if (!param)
                    continue;
                // 查找同名局部变量
                for (auto * local: locals) {
                    if (local && local->getName() == param->getName()) {
                        // %lX = %tX
                        node->blockInsts.addInst(new MoveInstruction(curFunc, local, param));
                        break;
                    }
                }
            }
        }
    }
    // --- 新增结束 ---

    // 新建一个Value，用于保存函数的返回值，如果没有返回值可不用申请
    LocalVariable * retValue = nullptr;
    if (!type_node->type->isVoidType()) {

        // 保存函数返回值变量到函数信息中，在return语句翻译时需要设置值到这个变量中
        retValue = static_cast<LocalVariable *>(module->newVarValue(type_node->type));
    }
    newFunc->setReturnValue(retValue);

    // 函数内已经进入作用域，内部不再需要做变量的作用域管理
    block_node->needScope = false;

    // 遍历block
    result = ir_block(block_node);
    if (!result) {
        // block解析失败
        // TODO 自行追加语义错误处理
        return false;
    }

    // IR指令追加到当前的节点中
    node->blockInsts.addInst(block_node->blockInsts);

    // 此时，所有指令都加入到当前函数中，也就是node->blockInsts

    // node节点的指令移动到函数的IR指令列表中
    irCode.addInst(node->blockInsts);

    // 添加函数出口Label指令，主要用于return语句跳转到这里进行函数的退出
    irCode.addInst(entryLabelInst);

    // 函数出口指令
    irCode.addInst(new ExitInstruction(newFunc, retValue));

    // 恢复成外部函数
    module->setCurrentFunction(nullptr);

    // 退出函数的作用域
    module->leaveScope();

    return true;
}

/// @brief 形式参数AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_function_formal_params(ast_node * node)
{
    Function * curFunc = module->getCurrentFunction();
    std::vector<FormalParam *> paramList;
    // 依次处理每个形参
    for (auto param_node: node->sons) {
        if (!param_node)
            continue;
        Type * param_type = param_node->type;
        std::string param_name = param_node->name;
        Value * var = nullptr;
        if (param_node->is_array) {
            PointerType * ptrType = PointerType::getNonConstPointerType(
                param_node->array_element_type ? param_node->array_element_type : param_type);
            var = module->newVarValue(ptrType, param_name);
        } else {
            var = module->newVarValue(param_type, param_name);
        }
        param_node->val = var;
        // 构造FormalParam并加入列表（只传type和name）
        FormalParam * formal = new FormalParam(param_type, param_name);
        paramList.push_back(formal);
    }
    // 批量加入参数
    if (curFunc)
        curFunc->addParams(paramList);
    return true;
}

/// @brief 语句块（含函数体）AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_block(ast_node * node)
{
    // 进入作用域
    if (node->needScope) {
        module->enterScope();
    }

    std::vector<ast_node *>::iterator pIter;
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        ast_node * temp = ir_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }

        node->blockInsts.addInst(temp->blockInsts);
    }

    // 离开作用域
    if (node->needScope) {
        module->leaveScope();
    }

    return true;
}
/// @brief 语句块（含函数体）AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_nested_block(ast_node * node)
{
    // 进入作用域
    if (node->needScope) {
        module->enterScope();
    }
    Function * currentFunc = module->getCurrentFunction();
    LabelInstruction * entryLabelInst = new LabelInstruction(currentFunc);
    node->blockInsts.addInst(entryLabelInst);

    std::vector<ast_node *>::iterator pIter;
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        ast_node * temp = ir_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }

        node->blockInsts.addInst(temp->blockInsts);
    }
    node->val = entryLabelInst;
    // 离开作用域
    if (node->needScope) {
        module->leaveScope();
    }

    return true;
}
bool IRGenerator::ir_if_else(ast_node * node)
{
    // 进入作用域
    if (node->needScope) {
        module->enterScope();
    }
    Function * currentFunc = module->getCurrentFunction();
    LabelInstruction * entryLabelInst = new LabelInstruction(currentFunc);
    node->blockInsts.addInst(entryLabelInst);
    ast_node * cond = ir_visit_ast_node(node->sons[0]);
    // cond->blocks是放的最后计算的变量，%t2= icmp gt %l1,100中的t2.
    node->blockInsts.addInst(cond->blockInsts);

    ast_node * branch1 = ir_visit_ast_node(node->sons[1]);
    ast_node * branch2;
    LabelInstruction * exitLabelInst;
    BranchifCondition * branch_Inst;
    // 可能不存在else分支，只有单if
    if (node->sons[2]) {
        branch2 = ir_visit_ast_node(node->sons[2]);
        branch_Inst = new BranchifCondition(module->getCurrentFunction(), cond->val, branch1->val, branch2->val);
        node->blockInsts.addInst(branch_Inst);
        node->blockInsts.addInst(branch1->blockInsts);
        node->blockInsts.addInst(branch2->blockInsts);
    } else {
        exitLabelInst = new LabelInstruction(currentFunc);
        branch_Inst = new BranchifCondition(module->getCurrentFunction(), cond->val, branch1->val, exitLabelInst);
        node->blockInsts.addInst(branch_Inst);
        node->blockInsts.addInst(branch1->blockInsts);
        node->blockInsts.addInst(exitLabelInst);

    } // branch1->val是一个label指令
    node->val = entryLabelInst;
    // 离开作用域
    if (node->needScope) {
        module->leaveScope();
    }

    return true;
}
bool IRGenerator::ir_while(ast_node * node)
{
    // 进入作用域
    if (node->needScope) {
        module->enterScope();
    }
    Function * currentFunc = module->getCurrentFunction();
    LabelInstruction * entryLabelInst = new LabelInstruction(currentFunc);
    LabelInstruction * exitLabelInst = new LabelInstruction(currentFunc);
    node->blockInsts.addInst(entryLabelInst);

    ast_node * cond = ir_visit_ast_node(node->sons[0]);
    // cond->blocks是放的最后计算的变量，%t2= icmp gt %l1,100中的t2.
    node->blockInsts.addInst(cond->blockInsts);
    // nested_block->val是语块的的一个label，也就是开头
    ast_node * nested_block = ir_visit_ast_node(node->sons[1]);

    // nested_block->val是一个label指令
    BranchifCondition * branch_Inst;
    branch_Inst = new BranchifCondition(module->getCurrentFunction(), cond->val, nested_block->val, exitLabelInst);
    node->blockInsts.addInst(branch_Inst);
    node->blockInsts.addInst(nested_block->blockInsts);
    node->blockInsts.addInst(new GotoInstruction(currentFunc, entryLabelInst));
    node->val = entryLabelInst;
    node->blockInsts.addInst(exitLabelInst);
    // 离开作用域
    if (node->needScope) {
        module->leaveScope();
    }

    return true;
}
/// @brief return节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_return(ast_node * node)
{
    ast_node * right = nullptr;

    // return语句可能没有没有表达式，也可能有，因此这里必须进行区分判断
    if (!node->sons.empty()) {

        ast_node * son_node = node->sons[0];

        // 返回的表达式的指令保存在right节点中
        right = ir_visit_ast_node(son_node);
        if (!right) {

            // 某个变量没有定值
            return false;
        }
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
    Function * currentFunc = module->getCurrentFunction();

    // 返回值存在时则移动指令到node中
    if (right) {

        // 创建临时变量保存IR的值，以及线性IR指令
        node->blockInsts.addInst(right->blockInsts);
        // 返回值赋值到函数返回值变量上，然后跳转到函数的尾部
        node->blockInsts.addInst(new MoveInstruction(currentFunc, currentFunc->getReturnValue(), right->val));

        node->val = right->val;
    } else {
        // 没有返回值
        node->val = nullptr;
    }

    // 跳转到函数的尾部出口指令上
    node->blockInsts.addInst(new GotoInstruction(currentFunc, currentFunc->getExitLabel()));

    node->val = right->val;

    // TODO 设置类型

    return true;
}

/// @brief 类型叶子节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_type(ast_node * node)
{
    // 不需要做什么，直接从节点中获取即可。

    return true;
}

/// @brief 无符号整数字面量叶子节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_uint(ast_node * node)
{
    // 根据类型创建对应的常量
    if (node->type->isIntegerType()) {
        // 创建整数常量
        ConstInt * val = module->newConstInt((int32_t) node->integer_val);
        node->val = val;
    } else if (node->type->isFloatType()) {
        // 创建浮点常量
        ConstFloat * val = module->newConstFloat((float) node->float_val);
        node->val = val;
    } else {
        std::cerr << "Error: Unsupported type for leaf node" << std::endl;
        return false;
    }

    return true;
}
//@brief 处理左值，例如return x当中的x
//传入的是exp，exp后跟一个lval，lval后是一个c
bool IRGenerator::ir_leaf_value_uint(ast_node * node)
{
    Value * val;

    // 查找ID型Value
    // 变量，则需要在符号表中查找对应的值

    // val = module->findVarValue(node->sons[0]->name);
    val = module->findVar(node->sons[0]->name);

    node->val = val;

    return true;
}
/// @brief 整数加 减法AST节点翻译成线性中间IR,要根据op来判断加减
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败

bool IRGenerator::ir_add(ast_node * node)
{
    Op op = node->op_type;
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];
    float op1 = src1_node->type->isFloatType() ? src1_node->float_val : src1_node->integer_val;
    float op2 = src2_node->type->isFloatType() ? src2_node->float_val : src2_node->integer_val;
    // 优化x=2+3变成x=5
    if (src1_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT &&
        src2_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        if (src1_node->type->isFloatType() || src2_node->type->isFloatType()) {
            ConstFloat * val = module->newConstFloat((op == Op::ADD) ? (op1 + op2) : (op1 - op2));
            node->val = val;
            node->type = src1_node->type->isFloatType() ? src1_node->type : src2_node->type;
            return true;
        } else {
            ConstInt * val = module->newConstInt((op == Op::ADD) ? ((int) op1 + (int) op2) : ((int) op1 - (int) op2));
            node->val = val;
            node->type = src1_node->type;
            return true;
        }
    }
    // 针对const进行优化
    Value * Var1 = nullptr;
    Value * Var2 = nullptr;
    float leftV;
    float rightV;
    if (!src1_node->name.empty()) {
        Var1 = module->findVar(src1_node->name);
        if (Var1->isConst()) {
            if (Var1->type->isIntegerType())
                leftV = Var1->real_int;
            else {
                leftV = Var1->real_float;
            }
        }
    }
    if (!src2_node->name.empty()) {
        Var2 = module->findVar(src2_node->name);
        if (Var2->isConst()) {
            if (Var2->type->isIntegerType())
                rightV = Var2->real_int;
            else {
                rightV = Var2->real_float;
            }
        }
    }
    if (Var1 && Var1->isConst() && Var2 && Var2->isConst()) {
        if (Var1->type->isFloatType() || Var2->type->isFloatType()) {
            ConstFloat * val = module->newConstFloat((op == Op::ADD) ? leftV + rightV : leftV - rightV);
            node->val = val;
            node->type = src1_node->type->isFloatType() ? src1_node->type : src2_node->type;
            return true;
        } else {
            ConstInt * val =
                module->newConstInt((op == Op::ADD) ? (int) leftV + (int) rightV : (int) leftV - (int) rightV);
            node->val = val;
            node->type = src1_node->type;
            return true;
        }
        return true;
    }
    if (src1_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT ||
        src2_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        if (Var1 && Var1->isConst()) {
            if (Var1->type->isFloatType() || src1_node->type->isFloatType()) {
                ConstFloat * val = module->newConstFloat((op == Op::ADD) ? (leftV + op2) : (leftV - op2));
                node->val = val;
                node->type = src1_node->type->isFloatType() ? src1_node->type : src2_node->type;
                return true;
            } else {
                ConstInt * val =
                    module->newConstInt((op == Op::ADD) ? ((int) leftV + (int) op2) : ((int) leftV - (int) op2));
                node->val = val;
                node->type = src1_node->type;
                return true;
            }
            return true;
        } else if (Var2 && Var2->isConst()) {
            if (src1_node->type->isFloatType() || Var2->type->isFloatType()) {
                ConstFloat * val = module->newConstFloat((op == Op::ADD) ? (op1 + rightV) : (op1 - rightV));
                node->val = val;
                node->type = src1_node->type->isFloatType() ? src1_node->type : src2_node->type;
                return true;
            } else {
                ConstInt * val =
                    module->newConstInt((op == Op::ADD) ? ((int) op1 + (int) rightV) : ((int) op1 - (int) rightV));
                node->val = val;
                node->type = src1_node->type;
                return true;
            }
            return true;
        }
    }

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    BinaryInstruction * addInst;
    StoreInstruction * LstoInst = nullptr;
    StoreInstruction * RstoInst = nullptr;
    if (left->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        LstoInst = new StoreInstruction(module->getCurrentFunction(), left->val, true);
    }
    if (right->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {

        RstoInst = new StoreInstruction(module->getCurrentFunction(), right->val, true);
    }
    IRInstOperator irOp = (op == Op::ADD) ? IRInstOperator::IRINST_OP_ADD_I : IRInstOperator::IRINST_OP_SUB_I;
    addInst = new BinaryInstruction(module->getCurrentFunction(),
                                    irOp,
                                    LstoInst ? LstoInst : left->val,
                                    RstoInst ? RstoInst : right->val,
                                    IntegerType::getTypeInt());

    // BinaryInstruction->getIRName();
    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    if (LstoInst) {
        node->blockInsts.addInst(LstoInst);
    }
    node->blockInsts.addInst(right->blockInsts);
    if (RstoInst) {
        node->blockInsts.addInst(RstoInst);
    }
    node->blockInsts.addInst(addInst);

    node->val = addInst;

    return true;
}
/// @brief 整数乘 除法AST节点翻译成线性中间IR,要根据op来判断乘除
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_visitUNARYExp(ast_node * node)
{

    ast_node * src1_node = node->sons[0];
    Op op = src1_node->op_type;
    ast_node * src2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数是单目运算符，不用处理
    // ast_node * left = ir_visit_ast_node(src1_node);
    // if (!left) {
    //     // 某个变量没有定值
    //     return false;
    // }

    // 加法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    UnaryInstruction * UnaryInst;
    StoreInstruction * RstoInst = nullptr;
    if (right->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        RstoInst = new StoreInstruction(module->getCurrentFunction(), right->val, true);
    }
    UnaryInst = new UnaryInstruction(module->getCurrentFunction(),
                                     RstoInst ? RstoInst : right->val,
                                     IntegerType::getTypeInt(),
                                     (op == Op::NOT)   ? "NOT"
                                     : (op == Op::POS) ? "POS"
                                                       : "NEG");

    node->blockInsts.addInst(right->blockInsts);
    if (RstoInst) {
        node->blockInsts.addInst(RstoInst);
    }
    node->blockInsts.addInst(UnaryInst);

    node->val = UnaryInst;

    return true;
}
bool IRGenerator::ir_visitUNARYOP(ast_node * node)
{
    Op op = node->op_type;
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    BinaryInstruction * mulInst;
    StoreInstruction * LstoInst = nullptr;
    StoreInstruction * RstoInst = nullptr;

    if (left->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        LstoInst = new StoreInstruction(module->getCurrentFunction(), left->val, true);
    }
    if (right->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        RstoInst = new StoreInstruction(module->getCurrentFunction(), right->val, true);
    }
    IRInstOperator irOp = (op == Op::MUL) ? IRInstOperator::IRINST_OP_MUL_I : IRInstOperator::IRINST_OP_MOD_I;
    mulInst = new BinaryInstruction(module->getCurrentFunction(),
                                    irOp,
                                    LstoInst ? LstoInst : left->val,
                                    RstoInst ? RstoInst : right->val,
                                    IntegerType::getTypeInt());

    node->blockInsts.addInst(left->blockInsts);
    if (LstoInst) {
        node->blockInsts.addInst(LstoInst);
    }
    node->blockInsts.addInst(right->blockInsts);
    if (RstoInst) {
        node->blockInsts.addInst(RstoInst);
    }
    node->blockInsts.addInst(mulInst);

    node->val = mulInst;

    return true;
}
bool IRGenerator::ir_mul(ast_node * node)
{
    Op op = node->op_type;
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];
    float op1 = src1_node->type->isFloatType() ? src1_node->float_val : src1_node->integer_val;
    float op2 = src2_node->type->isFloatType() ? src2_node->float_val : src2_node->integer_val;
    // 优化x=2+3变成x=5
    if (src1_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT &&
        src2_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        if (src1_node->type->isFloatType() || src2_node->type->isFloatType()) {
            ConstFloat * val = module->newConstFloat((op == Op::MUL)   ? (op1 * op2)
                                                     : (op == Op::DIV) ? (op1 / op2)
                                                                       : ((int) op1 % (int) op2));
            node->val = val;
            node->type = src1_node->type->isFloatType() ? src1_node->type : src2_node->type;
            return true;
        } else {
            ConstInt * val = module->newConstInt((op == Op::MUL)   ? ((int) op1 * (int) op2)
                                                 : (op == Op::DIV) ? ((int) op1 / (int) op2)
                                                                   : ((int) op1 % (int) op2));
            node->val = val;
            node->type = src1_node->type;
            return true;
        }
    }
    // 针对const进行优化
    Value * Var1 = nullptr;
    Value * Var2 = nullptr;
    float leftV;
    float rightV;
    if (!src1_node->name.empty()) {
        Var1 = module->findVar(src1_node->name);
        if (Var1->isConst()) {
            if (Var1->type->isIntegerType())
                leftV = Var1->real_int;
            else {
                leftV = Var1->real_float;
            }
        }
    }
    if (!src2_node->name.empty()) {
        Var2 = module->findVar(src2_node->name);
        if (Var2->isConst()) {
            if (Var2->type->isIntegerType())
                rightV = Var2->real_int;
            else {
                rightV = Var2->real_float;
            }
        }
    }
    if (Var1 && Var1->isConst() && Var2 && Var2->isConst()) {
        if (Var1->type->isFloatType() || Var2->type->isFloatType()) {
            ConstFloat * val = module->newConstFloat((op == Op::MUL)   ? leftV * rightV
                                                     : (op == Op::DIV) ? (leftV / rightV)
                                                                       : (int) leftV % (int) rightV);
            node->val = val;
            node->type = src1_node->type->isFloatType() ? src1_node->type : src2_node->type;
            return true;
        } else {
            ConstInt * val = module->newConstInt((op == Op::MUL)   ? ((int) leftV * (int) rightV)
                                                 : (op == Op::DIV) ? ((int) leftV / (int) rightV)
                                                                   : ((int) leftV % (int) rightV));
            node->val = val;
            node->type = src1_node->type;
            return true;
        }
        return true;
    }
    if (src1_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT ||
        src2_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        if (Var1 && Var1->isConst()) {
            if (Var1->type->isFloatType() || src1_node->type->isFloatType()) {
                ConstFloat * val = module->newConstFloat((op == Op::MUL)   ? (leftV * op2)
                                                         : (op == Op::DIV) ? (leftV / op2)
                                                                           : ((int) leftV % (int) op2));
                node->val = val;
                node->type = src1_node->type->isFloatType() ? src1_node->type : src2_node->type;
                return true;
            } else {
                ConstInt * val = module->newConstInt((op == Op::MUL)   ? ((int) leftV * (int) op2)
                                                     : (op == Op::DIV) ? ((int) leftV / (int) op2)
                                                                       : ((int) leftV % (int) op2));
                node->val = val;
                node->type = src1_node->type;
                return true;
            }
        } else if (Var2 && Var2->isConst()) {
            if (src1_node->type->isFloatType() || Var2->type->isFloatType()) {
                ConstFloat * val = module->newConstFloat((op == Op::MUL)   ? (op1 * rightV)
                                                         : (op == Op::DIV) ? (op1 / rightV)
                                                                           : ((int) op1 % (int) rightV));
                node->val = val;
                node->type = src1_node->type->isFloatType() ? src1_node->type : src2_node->type;
                return true;
            } else {
                ConstInt * val = module->newConstInt((op == Op::MUL)   ? ((int) op1 * (int) rightV)
                                                     : (op == Op::DIV) ? ((int) op1 / (int) rightV)
                                                                       : ((int) op1 % (int) rightV));
                node->val = val;
                node->type = src1_node->type;
                return true;
            }
            return true;
        }
    }

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    BinaryInstruction * mulInst;
    StoreInstruction * LstoInst = nullptr;
    StoreInstruction * RstoInst = nullptr;

    if (left->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        LstoInst = new StoreInstruction(module->getCurrentFunction(), left->val, true);
    }
    if (right->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        RstoInst = new StoreInstruction(module->getCurrentFunction(), right->val, true);
    }
    IRInstOperator irOp = (op == Op::MUL)   ? IRInstOperator::IRINST_OP_MUL_I
                          : (op == Op::DIV) ? IRInstOperator::IRINST_OP_DIV_I
                                            : IRInstOperator::IRINST_OP_MOD_I;
    mulInst = new BinaryInstruction(module->getCurrentFunction(),
                                    irOp,
                                    LstoInst ? LstoInst : left->val,
                                    RstoInst ? RstoInst : right->val,
                                    IntegerType::getTypeInt());

    node->blockInsts.addInst(left->blockInsts);
    if (LstoInst) {
        node->blockInsts.addInst(LstoInst);
    }
    node->blockInsts.addInst(right->blockInsts);
    if (RstoInst) {
        node->blockInsts.addInst(RstoInst);
    }
    node->blockInsts.addInst(mulInst);

    node->val = mulInst;

    return true;
}

/// @brief 处理表达式节点AST，生成相应的IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_visitExp(ast_node * node)
{
    // 判断当前节点是否为空
    if (!node) {
        return false;
    }
    ast_node * temp = ir_visit_ast_node(node->sons[0]);
    // 如果当前节点是叶子节点，直接生成IR
    node->val = temp->val;
    node->blockInsts.addInst(temp->blockInsts);
    return true;
}
bool IRGenerator::ir_visitLogitExp(ast_node * node)
{
    // 判断当前节点是否为空
    if (!node) {
        return false;
    }
    ast_operator_type Node_Type = node->node_type;
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];
    int op1 = src1_node->integer_val;
    int op2 = src2_node->integer_val;
    // 优化x=2+3变成x=5
    if (src1_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT &&
        src2_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        ConstFloat * val =
            module->newConstFloat((Node_Type == ast_operator_type::AST_OP_LAND_EXP) ? (op1 && op2) : (op1 || op2));
        node->val = val;
        node->type = src1_node->type->isFloatType() ? src1_node->type : src2_node->type;
        return true;
    }
    // 针对const进行优化
    Value * Var1 = nullptr;
    Value * Var2 = nullptr;
    int leftV;
    int rightV;
    if (!src1_node->name.empty()) {
        Var1 = module->findVar(src1_node->name);
        if (Var1->isConst()) {
            leftV = Var1->real_int;
        }
    }
    if (!src2_node->name.empty()) {
        Var2 = module->findVar(src2_node->name);
        if (Var2->isConst()) {
            rightV = Var2->real_int;
        }
    }
    if (Var1 && Var1->isConst() && Var2 && Var2->isConst()) {
        ConstInt * val = module->newConstInt(
            (Node_Type == ast_operator_type::AST_OP_LAND_EXP) ? (int) leftV && (int) rightV : (int) leftV || (int) op2);
        node->val = val;
        node->type = src1_node->type;
        return true;
    }
    if (src1_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT ||
        src2_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        if (Var1 && Var1->isConst()) {
            ConstInt * val =
                module->newConstInt((Node_Type == ast_operator_type::AST_OP_LAND_EXP) ? ((int) leftV && (int) op2)
                                                                                      : ((int) leftV || (int) op2));
            node->val = val;
            node->type = src1_node->type;
            return true;
        } else if (Var2 && Var2->isConst()) {
            ConstInt * val =
                module->newConstInt((Node_Type == ast_operator_type::AST_OP_LAND_EXP) ? ((int) op1 && (int) rightV)
                                                                                      : ((int) op1 || (int) rightV));
            node->val = val;
            node->type = src1_node->type;
            return true;
        }
    }
    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    BinaryInstruction * mulInst;
    StoreInstruction * LstoInst = nullptr;
    StoreInstruction * RstoInst = nullptr;

    if (left->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        LstoInst = new StoreInstruction(module->getCurrentFunction(), left->val, true);
    }
    if (right->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        RstoInst = new StoreInstruction(module->getCurrentFunction(), right->val, true);
    }
    IRInstOperator irOp = (node->node_type == ast_operator_type::AST_OP_LAND_EXP) ? IRInstOperator::IRINST_OP_AND_I
                                                                                  : IRInstOperator::IRINST_OP_OR_I;

    mulInst = new BinaryInstruction(module->getCurrentFunction(),
                                    irOp,
                                    LstoInst ? LstoInst : left->val,
                                    RstoInst ? RstoInst : right->val,
                                    IntegerType::getTypeInt());

    node->blockInsts.addInst(left->blockInsts);
    if (LstoInst) {
        node->blockInsts.addInst(LstoInst);
    }
    node->blockInsts.addInst(right->blockInsts);
    if (RstoInst) {
        node->blockInsts.addInst(RstoInst);
    }
    node->blockInsts.addInst(mulInst);

    node->val = mulInst;
    return true;
}
bool IRGenerator::ir_visitConfExp(ast_node * node)
{
    // 判断当前节点是否为空
    if (!node) {
        return false;
    }
    Op op = node->op_type;
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];
    int op1 = src1_node->integer_val;
    int op2 = src2_node->integer_val;
    // 优化x=2+3变成x=5
    if (src1_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT &&
        src2_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        ConstFloat * val = module->newConstFloat((op == Op::GT)    ? (op1 > op2)
                                                 : (op == Op::LT)  ? (op1 < op2)
                                                 : (op == Op::EQ)  ? (op1 == op2)
                                                 : (op == Op::NE)  ? (op1 != op2)
                                                 : (op == Op::GE)  ? (op1 >= op2)
                                                 : (op == Op::LE)  ? (op1 <= op2)
                                                 : (op == Op::AND) ? (op1 && op2)
                                                 : (op == Op::OR)  ? (op1 || op2)
                                                                   : 0.0f);
        node->val = val;
        node->type = src1_node->type->isFloatType() ? src1_node->type : src2_node->type;
        return true;
    }
    // 针对const进行优化
    Value * Var1 = nullptr;
    Value * Var2 = nullptr;
    int leftV;
    int rightV;
    if (!src1_node->name.empty()) {
        Var1 = module->findVar(src1_node->name);
        if (Var1->isConst()) {
            leftV = Var1->real_int;
        }
    }
    if (!src2_node->name.empty()) {
        Var2 = module->findVar(src2_node->name);
        if (Var2->isConst()) {
            rightV = Var2->real_int;
        }
    }
    if (Var1 && Var1->isConst() && Var2 && Var2->isConst()) {
        ConstInt * val = module->newConstInt((op == Op::GT)    ? ((int) leftV > (int) rightV)
                                             : (op == Op::LT)  ? ((int) leftV < (int) rightV)
                                             : (op == Op::EQ)  ? ((int) leftV == (int) rightV)
                                             : (op == Op::NE)  ? ((int) leftV != (int) rightV)
                                             : (op == Op::GE)  ? ((int) leftV >= (int) rightV)
                                             : (op == Op::LE)  ? ((int) leftV <= (int) rightV)
                                             : (op == Op::AND) ? ((int) leftV && (int) rightV)
                                             : (op == Op::OR)  ? ((int) leftV || (int) rightV)
                                                               : 0);
        node->val = val;
        node->type = src1_node->type;
        return true;
    }
    if (src1_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT ||
        src2_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        if (Var1 && Var1->isConst()) {
            ConstInt * val = module->newConstInt((op == Op::GT)    ? ((int) leftV > (int) op2)
                                                 : (op == Op::LT)  ? ((int) leftV < (int) op2)
                                                 : (op == Op::EQ)  ? ((int) leftV == (int) op2)
                                                 : (op == Op::NE)  ? ((int) leftV != (int) op2)
                                                 : (op == Op::GE)  ? ((int) leftV >= (int) op2)
                                                 : (op == Op::LE)  ? ((int) leftV <= (int) op2)
                                                 : (op == Op::AND) ? ((int) leftV && (int) op2)
                                                 : (op == Op::OR)  ? ((int) leftV || (int) op2)
                                                                   : 0);
            node->val = val;
            node->type = src1_node->type;
            return true;
        } else if (Var2 && Var2->isConst()) {
            ConstInt * val = module->newConstInt((op == Op::GT)    ? ((int) op1 > (int) rightV)
                                                 : (op == Op::LT)  ? ((int) op1 < (int) rightV)
                                                 : (op == Op::EQ)  ? ((int) op1 == (int) rightV)
                                                 : (op == Op::NE)  ? ((int) op1 != (int) rightV)
                                                 : (op == Op::GE)  ? ((int) op1 >= (int) rightV)
                                                 : (op == Op::LE)  ? ((int) op1 <= (int) rightV)
                                                 : (op == Op::AND) ? ((int) op1 && (int) rightV)
                                                 : (op == Op::OR)  ? ((int) op1 || (int) rightV)
                                                                   : 0);
            node->val = val;
            node->type = src2_node->type;
            return true;
        }
    }
    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    BinaryInstruction * mulInst;
    StoreInstruction * LstoInst = nullptr;
    StoreInstruction * RstoInst = nullptr;

    if (left->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        LstoInst = new StoreInstruction(module->getCurrentFunction(), left->val, true);
    }
    if (right->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        RstoInst = new StoreInstruction(module->getCurrentFunction(), right->val, true);
    }
    IRInstOperator irOp = (op == Op::GT)    ? IRInstOperator::IRINST_OP_GT_I
                          : (op == Op::EQ)  ? IRInstOperator::IRINST_OP_EQ_I
                          : (op == Op::LT)  ? IRInstOperator::IRINST_OP_LT_I
                          : (op == Op::LE)  ? IRInstOperator::IRINST_OP_LE_I
                          : (op == Op::GE)  ? IRInstOperator::IRINST_OP_GE_I
                          : (op == Op::NE)  ? IRInstOperator::IRINST_OP_NE_I
                          : (op == Op::AND) ? IRInstOperator::IRINST_OP_AND_I
                          : (op == Op::OR)  ? IRInstOperator::IRINST_OP_OR_I
                                            : IRInstOperator::IRINST_OP_DIV_I;
    mulInst = new BinaryInstruction(module->getCurrentFunction(),
                                    irOp,
                                    LstoInst ? LstoInst : left->val,
                                    RstoInst ? RstoInst : right->val,
                                    IntegerType::getTypeInt());

    node->blockInsts.addInst(left->blockInsts);
    if (LstoInst) {
        node->blockInsts.addInst(LstoInst);
    }
    node->blockInsts.addInst(right->blockInsts);
    if (RstoInst) {
        node->blockInsts.addInst(RstoInst);
    }
    node->blockInsts.addInst(mulInst);

    node->val = mulInst;
    return true;
}
bool IRGenerator::ir_const_declare(ast_node * node)
{
    // 不需要做什么，直接从节点中获取即可。
    // 判断当前节点是否为空
    if (!node) {
        return false;
    }

    std::vector<ast_node *>::iterator pIter;
    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        ast_node * temp = ir_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }

        node->blockInsts.addInst(temp->blockInsts);
    }
    return true;
}

bool IRGenerator::ir_declare_statment(ast_node * node)
{
    bool result = false;

    for (auto & child: node->sons) {

        // 遍历每个变量声明
        result = ir_variable_declare(child);
        if (!result) {
            break;
        }
    }

    return result;
}

/// @brief 变量定声明节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败

// 传进来var-decl 声明
bool IRGenerator::ir_variable_declare(ast_node * node)
{
    if (!node) {
        return false;
    }

    std::vector<ast_node *>::iterator pIter;
    // 第一个儿子是声明i32或f32
    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        ast_node * temp = ir_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }

        node->blockInsts.addInst(temp->blockInsts);
    }
    return true;
}
// #赋值语句
bool IRGenerator::ir_assign(ast_node * node)
{
    ast_node * son1_node = node->sons[0];
    ast_node * son2_node = node->sons[1];

    // 赋值节点，自右往左运算

    // 赋值运算符的左侧操作数
    ast_node * left = ir_visit_ast_node(son1_node);

    if (!left) {
        // 某个变量没有定值
        // 这里缺省设置变量不存在则创建，因此这里不会错误
        return false;
    }

    if (left->val->isConst()) {
        printf("const variable can not be assigned.");
        return false;
    }

    // 赋值运算符的右侧操作数
    ast_node * right = ir_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    MoveInstruction * movInst = nullptr;

    movInst = new MoveInstruction(module->getCurrentFunction(), left->val, right->val);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(movInst);

    // 这里假定赋值的类型是一致的

    node->val = movInst;

    return true;
}

// AST_OP_SCALAR_INIT
bool IRGenerator::ir_scalar_init(ast_node * node)
{
    ast_node * left_val_node = node->parent;
    ast_node * right_node = node->sons[0];

    // 赋值运算符的右侧操作数
    ast_node * right = ir_visit_ast_node(right_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    if (left_val_node->node_type == ast_operator_type::AST_OP_CONST_DEF) {
        left_val_node->val->real_float = right->val->real_float;
        left_val_node->val->real_int = right->val->real_int;
    }
    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    MoveInstruction * movInst = new MoveInstruction(module->getCurrentFunction(), left_val_node->val, right->val);

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left_val_node->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(movInst);
    // 这里假定赋值的类型是一致的
    node->val = movInst;
    return true;
}

bool IRGenerator::ir_var_def(ast_node * node)
{
    if (!node) {
        return false;
    }
    node->val = module->newVarValue(node->parent->sons[0]->type, node->sons[0]->name);
    if (node->sons.size() > 1) {
        ast_node * temp = ir_visit_ast_node(node->sons[1]);
        node->blockInsts.addInst(temp->blockInsts);
    }

    return true;
}
//数组初始化时展平函数
void IRGenerator::flatten_array_init(std::string name,
                                     ast_node * node,
                                     std::vector<InitElement> & flat_init_list,
                                     std::vector<int> & index_counters,
                                     std::vector<int> & dimensions,
                                     int & now_rank,
                                     int & large_rank,
                                     int & level)
{
    if (!node)
        return;
    for (int i = 0; i < dimensions.size(); i++) {
        if (index_counters[i] >= dimensions[i]) {
            std::cerr << "It 's out of range when you initialize a number in dimensions:" << i << std::endl;
            return;
        }
    }

    // 最底层：形如 =(常量) 的 scalar_init
    if ((node->node_type == ast_operator_type::AST_OP_SCALAR_CONST_INIT ||
         node->node_type == ast_operator_type::AST_OP_SCALAR_INIT) &&
        !node->sons.empty()) {

        ast_node * exp_node = node->sons[0];
        ast_node * element_node = ir_visit_ast_node(exp_node);

        node->blockInsts.addInst(element_node->blockInsts);
        if (!element_node || !element_node->val) {
            std::cerr << "Error: array init element is not a constant!" << std::endl;
            return;
        }
        int linear_index = 0;
        int before_dim_total = 1;
        for (int i = index_counters.size() - 1; i >= 0; i--) {
            linear_index += index_counters[i] * before_dim_total;
            before_dim_total *= dimensions[i];
        }
        // 填充初始化列表
        flat_init_list.push_back({element_node, linear_index});
        Value * array_val = module->findVarValue(name);
        array_val->addElement(linear_index, element_node->val->real_int, element_node->val->real_float);
        //对于下一节点的具体维度层级在当前节点就把判断先做掉
        //下一节点首先要存在，同时为=号才可以判断为在同一层级上
        if (now_rank + 1 < large_rank) {
            ast_node * next_node = node->parent->sons[now_rank + 1];
            if ((next_node->node_type == ast_operator_type::AST_OP_SCALAR_CONST_INIT ||
                 next_node->node_type == ast_operator_type::AST_OP_SCALAR_INIT)) {
                int i = index_counters.size() - 1;
                if (index_counters[i] == dimensions[i] - 1) {
                    while (index_counters[i] == dimensions[i] - 1 && i > 0) {
                        index_counters[i] = 0;
                        index_counters[i - 1] += 1;
                        i--;
                    }
                } else {
                    index_counters[i] += 1;
                }
            }
        }
        /*
        if (node->parent->sons[now_rank + 1] &&
            (node->parent->sons[now_rank + 1]->node_type == ast_operator_type::AST_OP_SCALAR_CONST_INIT ||
             node->parent->sons[now_rank + 1]->node_type == ast_operator_type::AST_OP_SCALAR_INIT)) {
            int i = index_counters.size() - 1;
            if (index_counters[i] == dimensions[i] - 1) {
                while (index_counters[i] == dimensions[i] - 1 && i > 0) {
                    index_counters[i] = 0;
                    index_counters[i - 1] += 1;
                    i--;
                }
            } else {
                index_counters[i] += 1;
            }
        }
        */
        return;
    }

    // 中间层：数组初始化结构，递归展开每一层
    if (node->node_type == ast_operator_type::AST_OP_ARRAY_CONST_INIT ||
        node->node_type == ast_operator_type::AST_OP_ARRAY_INIT_VAL) {
        //每一个array-init开始前都要对index_counters在当前维度进行重置
        if (level > -1) {
            // level = -1,说明是最开始的初始化根节点，那就没必要做了
            //初始化的具体做法是当前维度直接进1，后续维度清零
            index_counters[level] += 1;
            for (int i = level + 1; i < index_counters.size(); i++) {
                index_counters[i] = 0;
            }
        }
        //所有子节点的维度也要在父节点的维度上加一
        int tmp_level = level + 1;
        //之后所有子节点在兄弟中的排序也要清零
        int tmp_now_rank = 0;
        int son_large_rank = 0;
        // 遍历当前维度的所有子节点计算出子节点的数量
        for (auto & child: node->sons) {
            son_large_rank++;
        }
        // 遍历当前维度的所有子节点
        for (auto & child: node->sons) {
            flatten_array_init(name,
                               child,
                               flat_init_list,
                               index_counters,
                               dimensions,
                               tmp_now_rank,
                               son_large_rank,
                               tmp_level);
            tmp_now_rank += 1;
            node->blockInsts.addInst(child->blockInsts);
        }
        //当前为array-init节点，下一个兄弟节点如果为“=”则还要对index_count在当前维度进行重置
        if (now_rank + 1 < large_rank) {
            ast_node * next_node = node->parent->sons[now_rank + 1];
            if ((next_node->node_type == ast_operator_type::AST_OP_SCALAR_CONST_INIT ||
                 next_node->node_type == ast_operator_type::AST_OP_SCALAR_INIT)) {
                if (level > -1) {
                    //跟上面同样的做法
                    index_counters[level] += 1;
                    for (int i = level + 1; i < index_counters.size(); i++) {
                        index_counters[i] = 0;
                    }
                }
            }
        }
    }
}

bool IRGenerator::ir_array_var_def_declare(ast_node * node)
{
    if (!node)
        return false;

    // Step 1: 提取维度信息
    std::vector<int32_t> dimensions;
    std::string var_name = node->sons[0]->name; // 获取变量名
    ast_node * dim_length = node->sons[1];      // 获取维度节点

    // 提取所有维度
    for (auto dim_node: dim_length->sons) {
        int temp = ir_const_exp(dim_node);
        dimensions.push_back(static_cast<int32_t>(temp));
    }

    // Step 2: 获取指针类型
    PointerType * pointerType = PointerType::getNonConstPointerType(node->parent->sons[0]->type);
    node->val = module->newArrayValue(pointerType, var_name, dimensions);

    // 计算数组总大小
    int total_size = 1;
    for (auto d: dimensions)
        total_size *= d;

    // 获取数组变量的实际值
    Value * array_val = module->findVarValue(var_name);

    // Step 3: 初始化数组所有元素为0
    // Value * zero_val = module->newConstInt(0);
    // for (int i = 0; i < total_size; ++i) {
    //     ConstInt * offset = module->newConstInt(i);
    //     ConstInt * word_size = module->newConstInt(4); // 假设每个元素占 4 字节
    //     BinaryInstruction * offset_inst = new BinaryInstruction(module->getCurrentFunction(),
    //                                                             IRInstOperator::IRINST_OP_MUL_I,
    //                                                             offset,
    //                                                             word_size,
    //                                                             IntegerType::getTypeInt());

    //     BinaryInstruction * addr_inst = new BinaryInstruction(module->getCurrentFunction(),
    //                                                           IRInstOperator::IRINST_OP_ADD_I,
    //                                                           offset_inst,
    //                                                           array_val,
    //                                                           array_val->getType());

    //     MoveInstruction * move_inst = new MoveInstruction(module->getCurrentFunction(), addr_inst, zero_val);

    //     // 将生成的指令添加到当前的指令块
    //     node->blockInsts.addInst(offset_inst);
    //     node->blockInsts.addInst(addr_inst);
    //     node->blockInsts.addInst(move_inst);
    // }

    // Step 4: 处理显式初始化
    if (node->sons.size() > 2) {
        std::vector<InitElement> flatten_nodes;
        // int linear_index = 0;
        std::vector<int> index_counters(dimensions.size(), 0); // 初始化index_counters
        int now_rank = 0;
        int level = -1;
        int large_rank = 1;
        flatten_array_init(var_name,
                           node->sons[2],
                           flatten_nodes,
                           index_counters,
                           dimensions,
                           now_rank,
                           large_rank,
                           level);
        node->blockInsts.addInst(node->sons[2]->blockInsts);
        // 处理显式初始化列表
        // for (auto & item: flatten_nodes) {
        //     ast_node * init_node = item.node;
        //     int index = item.linear_index;

        //     // 检查初始化节点是否合法
        //     if (!init_node || !init_node->val) {
        //         std::cerr << "Error: initializer is not a valid constant!\n";
        //         return false;
        //     }

        //     // 检查是否超出数组的大小
        //     if (index >= total_size) {
        //         std::cerr << "Error: too many initializers for array '" << var_name << "'" << std::endl;
        //         return false;
        //     }

        //     // 生成 IR 指令，将初始化值赋给数组元素
        //     ConstInt * offset = module->newConstInt(index);
        //     ConstInt * word_size = module->newConstInt(4); // 假设每个元素占 4 字节
        //     BinaryInstruction * offset_inst = new BinaryInstruction(module->getCurrentFunction(),
        //                                                             IRInstOperator::IRINST_OP_MUL_I,
        //                                                             offset,
        //                                                             word_size,
        //                                                             IntegerType::getTypeInt());

        //     BinaryInstruction * addr_inst = new BinaryInstruction(module->getCurrentFunction(),
        //                                                           IRInstOperator::IRINST_OP_ADD_I,
        //                                                           offset_inst,
        //                                                           array_val,
        //                                                           array_val->getType());

        //     MoveInstruction * move_inst = new MoveInstruction(module->getCurrentFunction(), addr_inst,
        //     init_node->val);

        //     // 将生成的指令添加到当前的指令块
        //     node->blockInsts.addInst(offset_inst);
        //     node->blockInsts.addInst(addr_inst);
        //     node->blockInsts.addInst(move_inst);
        // }

        // 最后为数组节点赋值
        node->val = array_val;
    }

    return true;
}

/*
void IRGenerator::flatten_array_init(ast_node * node, std::vector<ast_node *> & flat_init_list)
{
    if (!node) {
        std::cerr << "Visiting no node! " << std::endl;
        return;
    }

    // 数组初始化的叶子：形如 "=(常量)"
    if ((node->node_type == ast_operator_type::AST_OP_SCALAR_CONST_INIT ||
         node->node_type == ast_operator_type::AST_OP_SCALAR_INIT) &&
        !node->sons.empty()) {
        ast_node * exp_node = node->sons[0];

        // 生成该叶子的 IR（可能调用 ir_leaf_node_uint 或其他处理函数）
        // std::cerr << "stage = " << std::endl;

        ast_node * element_node = ir_visit_ast_node(exp_node);

        // irgen->ir_visit_ast_node(element_node);

        Value * val = element_node->val;
        // std::cout << "Visiting node with type: " << (int) node->node_type << std::endl;

        // 确保是常量（ConstInt 或 ConstFloat）
        if (!val || !val->isConst()) {
            std::cerr << "Error: array init element is not a constant!" << std::endl;
            return;
        }

        flat_init_list.push_back(element_node);
    }
    // 如果是数组初始化节点则递归处理
    else if (node->node_type == ast_operator_type::AST_OP_ARRAY_CONST_INIT ||
             node->node_type == ast_operator_type::AST_OP_ARRAY_INIT_VAL) {
        for (auto & child: node->sons) {
            flatten_array_init(child, flat_init_list);
        }
    }
}

// 输入type为AST_OP_ARRAY_VAR_DEF    var-array
bool IRGenerator::ir_array_var_def_declare(ast_node * node)
{
    if (!node) {
        return false;
    }

    std::vector<int32_t> _dimensions;
    // 第一个儿子是变量名称
    std::string var_name = node->sons[0]->name;
    // 第二个儿子是是array-index[10][4]定义
    ast_node * dim_length = node->sons[1]; // node->sons[1]对应array-index[x][y]
    std::vector<ast_node *>::iterator pIter;
    for (pIter = dim_length->sons.begin(); pIter != dim_length->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        int temp = ir_const_exp(*pIter);
        _dimensions.push_back(static_cast<int32_t>(temp));
    }

    // 提取所有维度
    for (auto dim_node: dim_length->sons) {
        int temp = ir_const_exp(dim_node);
        _dimensions.push_back(temp);
    }

    // Function * func = module->getCurrentFunction();
    // const Type * baseType = dim_length->sons[0]->type; // 这是基础类型
    PointerType * pointerType = PointerType::getNonConstPointerType(node->parent->sons[0]->type);
    node->val = module->newArrayValue(pointerType, var_name, _dimensions);


    if (node->sons.size() > 2) {
        // sons[0]: 变量名节点
        // sons[1]: 数组维度信息
        // sons[2]: 初始化值节点（AST_ARRAY_INIT 类型）

        //std::string var_name = node->sons[0]->name;
        Value * array_val = module->findVarValue(var_name);

        // 获取数组维度
        std::vector<int32_t> dims = array_val->arraydimensionVector;
        int total_size = 1;
        for (auto d: dims) {
            total_size *= d;
        }
        printf("total size: %d\n", total_size);

        // 展平初始化节点
        std::vector<ast_node *> flatten_nodes;

        flatten_array_init(node->sons[2], flatten_nodes); // 扁平化结构

        printf("flatten_nodes size: %zu\n", flatten_nodes.size());


        // 检查初始化个数
        int init_count = flatten_nodes.size();
        if (init_count > total_size) {
            std::cerr << "Error: array initializer has too many elements! "
                      << "Expected at most " << total_size << ", but got " << init_count << "." << std::endl;
            return false;
        }


        // 为每个常量生成 IR 并保存为 Value*
        std::vector<Value *> init_val_vector;
        for (auto & init_node: flatten_nodes) {
            if (!ir_visit_ast_node(init_node)) {
                std::cerr << "Error: failed to generate IR for initializer" << std::endl;
                return false;
            }
            init_val_vector.push_back(init_node->val); // ConstInt* 或 ConstFloat*
        }

        // 自动补 0（补成 total_size 个元素）
        Value * zero_val = nullptr;
        if (!init_val_vector.empty()) {
            auto type = init_val_vector[0]->getType();
            if (type->isIntegerType()) {
                zero_val = module->newConstInt(0);
            } else if (type->isFloatType()) {
                zero_val = module->newConstFloat(0.0);
            } else {
                std::cerr << "Error: unsupported array element type for zero init" << std::endl;
                return false;
            }
        } else {
            // 没有元素，默认当 int 型
            zero_val = module->newConstInt(0);
        }
        while ((int) init_val_vector.size() < total_size) {
            init_val_vector.push_back(zero_val);
        }

        // 遍历数组所有初始化值，生成每个元素的偏移地址并进行赋值
        for (int i = 0; i < total_size; ++i) {
            // 计算偏移地址：offset = i * 4 （假设 int/float 都为 4 字节）
            ConstInt * offset_const = module->newConstInt(i);
            ConstInt * word_size = module->newConstInt(4);

            BinaryInstruction * offset_inst = new BinaryInstruction(module->getCurrentFunction(),
                                                                    IRInstOperator::IRINST_OP_MUL_I,
                                                                    offset_const,
                                                                    word_size,
                                                                    IntegerType::getTypeInt());

            BinaryInstruction * addr_inst = new BinaryInstruction(module->getCurrentFunction(),
                                                                  IRInstOperator::IRINST_OP_ADD_I,
                                                                  offset_inst,
                                                                  array_val,
                                                                  array_val->getType());

            // 生成 move 指令：*(array + offset) = init_val
            MoveInstruction * move_inst =
                new MoveInstruction(module->getCurrentFunction(), addr_inst, init_val_vector[i]);

            // 将指令加入当前 block
            node->blockInsts.addInst(offset_inst);
            node->blockInsts.addInst(addr_inst);
            node->blockInsts.addInst(move_inst);
        }

        // 设置当前节点的值为整个数组变量地址
        node->val = array_val;
    }

    return true;
}
*/

//数组访问节点，有点冗余，可删减
bool IRGenerator::ir_array_acess(ast_node * node)
{
    if (!node) {
        return false;
    }
    if (node->node_type == ast_operator_type::AST_OP_EXP) {
        node = node->sons[0];
    }
    //变量名称
    std::vector<int32_t> index;
    std::vector<int32_t> dim;
    // 第一个儿子是变量名称
    std::string var_name = node->sons[0]->name;
    // Value * array_Value = module->findVarValue(var_name);
    Value * array_Value = module->findVar(var_name);

    std::vector<ast_node *>::iterator pIter;
    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {

        // 遍历每一个index
        int temp = ir_const_exp(*pIter);
        index.push_back(static_cast<int32_t>(temp));
    }
    dim = array_Value->arraydimensionVector;
    array_Value->arrayIndexVector = index;
    Value * currentVal = nullptr; // 当前累积的值
    // 根据类型创建对应的常量
    if (index.size() == 1) {
        ConstInt * offset = module->newConstInt((int32_t) index[0]);
        BinaryInstruction * offset_inst = new BinaryInstruction(module->getCurrentFunction(),
                                                                IRInstOperator::IRINST_OP_MUL_I,
                                                                offset,
                                                                module->newConstInt((int32_t) 4),
                                                                IntegerType::getTypeInt());
        node->blockInsts.addInst(offset_inst);
        BinaryInstruction * address_inst = new BinaryInstruction(module->getCurrentFunction(),
                                                                 IRInstOperator::IRINST_OP_ADD_I,
                                                                 offset_inst,
                                                                 array_Value,
                                                                 array_Value->getType());
        node->blockInsts.addInst(address_inst);
        currentVal = address_inst;
    } else {
        ConstInt * mulleftval;
        ConstInt * mulrightval;
        ConstInt * addrightval;
        BinaryInstruction * mul_inst;
        BinaryInstruction * add_inst;
        for (size_t i = 0; i < index.size() - 1; ++i) {
            if (i == 0) {
                // 第一维度的索引值直接作为初始值
                mulleftval = module->newConstInt((int32_t) index[i]);
                mulrightval = module->newConstInt((int32_t) dim[i + 1]);
                addrightval = module->newConstInt((int32_t) index[i + 1]);
                mul_inst = new BinaryInstruction(module->getCurrentFunction(),
                                                 IRInstOperator::IRINST_OP_MUL_I,
                                                 mulleftval,
                                                 mulrightval,
                                                 IntegerType::getTypeInt());
                add_inst = new BinaryInstruction(module->getCurrentFunction(),
                                                 IRInstOperator::IRINST_OP_ADD_I,
                                                 mul_inst,
                                                 addrightval,
                                                 IntegerType::getTypeInt());
                node->blockInsts.addInst(mul_inst);
                node->blockInsts.addInst(add_inst);
            } else {
                mulleftval = module->newConstInt((int32_t) index[i]);
                mulrightval = module->newConstInt((int32_t) dim[i + 1]);
                addrightval = module->newConstInt((int32_t) index[i + 1]);
                mul_inst = new BinaryInstruction(module->getCurrentFunction(),
                                                 IRInstOperator::IRINST_OP_MUL_I,
                                                 add_inst,
                                                 mulrightval,
                                                 IntegerType::getTypeInt());
                add_inst = new BinaryInstruction(module->getCurrentFunction(),
                                                 IRInstOperator::IRINST_OP_ADD_I,
                                                 mul_inst,
                                                 addrightval,
                                                 IntegerType::getTypeInt());
                node->blockInsts.addInst(mul_inst);
                node->blockInsts.addInst(add_inst);
            }
        }
        BinaryInstruction * offset_inst = new BinaryInstruction(module->getCurrentFunction(),
                                                                IRInstOperator::IRINST_OP_MUL_I,
                                                                add_inst,
                                                                module->newConstInt((int32_t) 4),
                                                                IntegerType::getTypeInt());
        node->blockInsts.addInst(offset_inst);
        BinaryInstruction * address_inst = new BinaryInstruction(module->getCurrentFunction(),
                                                                 IRInstOperator::IRINST_OP_ADD_I,
                                                                 offset_inst,
                                                                 array_Value,
                                                                 array_Value->getType());
        node->blockInsts.addInst(address_inst);
        currentVal = address_inst;
    }
    // 最终结果赋值给数组访问的值
    node->val = currentVal;
    // node->type = node->val->getType();
    return true;
}

bool IRGenerator::ir_array_init(ast_node * node)
{
    return true;
}

//获取数组该维度的维度
int IRGenerator::ir_const_exp(ast_node * node)
{
    if (node->sons[0] && node->sons[0]->node_type == ast_operator_type::AST_OP_LVAL) {
        Value * val;

        // 查找ID型Value
        // 变量，则需要在符号表中查找对应的值

        val = module->findVar(node->sons[0]->name);
        return val->real_int;
    }
    return node->integer_val;
}

/// @brief 标识符叶子节点翻译成线性中间IR，变量声明的不走这个语句
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_var_id(ast_node * node)
{
    Value * val;

    // 查找ID型Value
    // 变量，则需要在符号表中查找对应的值

    val = module->findVar(node->name);
    node->val = val;

    return true;
}

// 函数调用AST节点翻译成线性中间IR
bool IRGenerator::ir_func_call(ast_node * node)
{
    // node->sons[0] 是函数名节点，node->sons[1] 可能是参数节点(AST_OP_FUNC_RPARAMS)
    std::string func_name = node->sons[0]->name;
    Function * callee = module->findFunction(func_name);
    if (!callee) {
        std::cerr << "Error: function not found: " << func_name << std::endl;
        return false;
    }

    std::vector<Value *> args;
    // 支持无参数、有参数（AST_OP_FUNC_RPARAMS）、单参数直接表达式等情况
    if (node->sons.size() > 1 && node->sons[1]) {
        ast_node * param_node = node->sons[1];
        if (param_node->node_type == ast_operator_type::AST_OP_FUNC_RPARAMS) {
            // 多参数
            for (auto arg_ast: param_node->sons) {
                ast_node * arg_node = ir_visit_ast_node(arg_ast);
                if (!arg_node)
                    return false;
                node->blockInsts.addInst(arg_node->blockInsts);
                args.push_back(arg_node->val);
            }
        } else {
            // 兼容单参数直接是表达式的情况
            ast_node * arg_node = ir_visit_ast_node(param_node);
            if (!arg_node)
                return false;
            node->blockInsts.addInst(arg_node->blockInsts);
            args.push_back(arg_node->val);
        }
    }
    // else: 无参数

    // --- 新增：为每个参数生成ARG指令 ---
    for (auto * arg_val: args) {
        node->blockInsts.addInst(new ArgInstruction(module->getCurrentFunction(), arg_val));
    }
    // --- 新增结束 ---

    // 只传递参数，不要把call结果变量也作为参数
    FuncCallInstruction * callInst =
        new FuncCallInstruction(module->getCurrentFunction(), callee, args, callee->getReturnType());

    node->blockInsts.addInst(callInst);
    node->val = callInst;
    return true;
}
/*
bool IRGenerator::ir_const_def(ast_node * node)
{
    if (!node) {
        return false;
    }

    // 获取类型：从 const-def 的父节点（const-decl）下的 son[0]
    Type * type = node->parent->sons[0]->type;
    std::string name = node->sons[0]->name;

    // 创建常量值对象
    Value * val = module->newConstValue(type, name);
    if (!val) {
        return false; // 创建失败可能是重名或非法名
    }

    node->val = val;

    // 有初始化表达式：const int a = 5;
    if (node->sons.size() > 1) {
        ast_node * rhs = ir_visit_ast_node(node->sons[1]);
        if (!rhs) {
            return false;
        }

        // 添加初始化语句
        Inst * assign = new Inst(Opcode::Assign, val, rhs->val);
        node->blockInsts.addInst(rhs->blockInsts);
        node->blockInsts.addInst(assign);
    }

    return true;

}
*/

bool IRGenerator::ir_const_def(ast_node * node)
{
    if (!node) {
        return false;
    }
    // if (node->node_type == ast_operator_type::AST_OP_ARRAY_CONST_DEF) {
    //     node->val = module->newconstArrayValue(node->parent->sons[0]->type, node->sons[0]->name);
    // } else {
    node->val = module->newConstValue(node->parent->sons[0]->type, node->sons[0]->name);

    if (node->sons.size() <= 1) {
        printf("A const variable must be assigned an initial value when it is defined.");
        return false;
    } else {
        ast_node * temp = ir_visit_ast_node(node->sons[1]);
        node->blockInsts.addInst(temp->blockInsts);
    }

    return true;
}

ast_node * IRGenerator::ir_global(ast_node * node)
{
    // 空节点
    if (nullptr == node) {
        return nullptr;
    }
    bool result = false;
    if (node->node_type == ast_operator_type::AST_OP_VAR_DECL) {
        result = ir_global_variable_declare(node);
    } else if (node->node_type == ast_operator_type::AST_OP_CONST_DECL) {
        result = ir_global_const_declare(node);
    }
    if (!result) {
        return nullptr;
    }

    return node;
}

bool IRGenerator::ir_global_variable_declare(ast_node * node)
{
    if (!node) {
        return false;
    }

    std::vector<ast_node *>::iterator pIter;
    bool result = false;
    // 第一个儿子是声明i32或f32
    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        if ((*pIter)->node_type == ast_operator_type::AST_OP_ARRAY_VAR_DEF) {
            result = ir_global_array_var_def_declare(*pIter);
        } else {
            result = ir_global_var_def(*pIter);
        }

        if (!result) {
            return false;
        }

        node->blockInsts.addInst((*pIter)->blockInsts);
    }
    return true;
}

bool IRGenerator::ir_global_var_def(ast_node * node)
{
    if (!node) {
        return false;
    }
    bool result = false;
    bool is_bss = !(node->sons.size() > 1);
    node->val = module->newGlobalVariable(node->parent->sons[0]->type, node->sons[0]->name, is_bss);
    if (!is_bss) {
        ast_node * node_son = node->sons[1];
        result = ir_global_scalar_init(node_son);

        node->val->real_int = node_son->val->real_int;
        node->val->real_float = node_son->val->real_float;

        node->blockInsts.addInst(node_son->blockInsts);
    } else {
        node->val->real_int = 0;
        node->val->real_float = 0;
        result = true;
    }

    return result;
}

bool IRGenerator::ir_global_scalar_init(ast_node * node)
{
    ast_node * left_val_node = node->parent;
    ast_node * right_node = node->sons[0];

    // 赋值运算符的右侧操作数
    ast_node * right = ir_visit_ast_node(right_node);
    if (!right) {
        return false;
    }
    node->val = right->val;
    node->blockInsts.addInst(right->blockInsts);
    return true;
}

bool IRGenerator::ir_global_const_declare(ast_node * node)
{
    // 不需要做什么，直接从节点中获取即可。
    // 判断当前节点是否为空
    if (!node) {
        return false;
    }
    bool result = false;
    std::vector<ast_node *>::iterator pIter;
    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        if ((*pIter)->node_type == ast_operator_type::AST_OP_ARRAY_CONST_DEF) {
            result = ir_global_const_array_def(*pIter);
        } else {
            result = ir_global_const_def(*pIter);
        }
        if (!result) {
            return false;
        }

        // node->blockInsts.addInst(temp->blockInsts);
    }
    return true;
}
bool IRGenerator::ir_global_const_def(ast_node * node)
{
    if (!node) {
        return false;
    }
    bool result = false;
    node->val = module->newConstValue(node->parent->sons[0]->type, node->sons[0]->name);
    if (node->sons.size() <= 1) {
        printf("A const variable must be assigned an initial value when it is defined.");
        return false;
    } else {
        result = ir_global_scalar_init(node->sons[1]);
        // node->blockInsts.addInst(temp->blockInsts);
    }
    node->val->real_float = node->sons[1]->val->real_float;
    node->val->real_int = node->sons[1]->val->real_int;

    return result;
}
bool IRGenerator::ir_global_const_array_def(ast_node * node)
{
    if (!node)
        return false;

    // Step 1: 提取维度信息
    std::vector<int32_t> dimensions;
    std::string var_name = node->sons[0]->name; // 获取变量名
    ast_node * dim_length = node->sons[1];      // 获取维度节点

    // 提取所有维度
    for (auto dim_node: dim_length->sons) {
        int temp = ir_const_exp(dim_node);
        dimensions.push_back(static_cast<int32_t>(temp));
    }

    // Step 2: 获取指针类型
    PointerType * pointerType = PointerType::getNonConstPointerType(node->parent->sons[0]->type);
    node->val = module->newconstArray(pointerType, var_name, dimensions);

    // 计算数组总大小
    int total_size = 1;
    for (auto d: dimensions)
        total_size *= d;

    // 获取数组变量的实际值
    Value * array_val = module->findVarValue(var_name);
    // Step 4: 处理显式初始化
    if (node->sons.size() > 2) {
        std::vector<InitElement> flatten_nodes;
        // int linear_index = 0;
        std::vector<int> index_counters(dimensions.size(), 0); // 初始化index_counters
        int now_rank = 0;
        int level = -1;
        int large_rank = 1;
        flatten_array_init(var_name,
                           node->sons[2],
                           flatten_nodes,
                           index_counters,
                           dimensions,
                           now_rank,
                           large_rank,
                           level);
        node->blockInsts.addInst(node->sons[2]->blockInsts);
        node->val = array_val;
    }

    return true;
}
bool IRGenerator::ir_const_array_var_def_declare(ast_node * node)
{
    if (!node)
        return false;

    // Step 1: 提取维度信息
    std::vector<int32_t> dimensions;
    std::string var_name = node->sons[0]->name; // 获取变量名
    ast_node * dim_length = node->sons[1];      // 获取维度节点

    // 提取所有维度
    for (auto dim_node: dim_length->sons) {
        int temp = ir_const_exp(dim_node);
        dimensions.push_back(static_cast<int32_t>(temp));
    }

    // Step 2: 获取指针类型
    PointerType * pointerType = PointerType::getNonConstPointerType(node->parent->sons[0]->type);
    node->val = module->newconstArray(pointerType, var_name, dimensions);

    // 计算数组总大小
    int total_size = 1;
    for (auto d: dimensions)
        total_size *= d;

    // 获取数组变量的实际值
    Value * array_val = module->findVarValue(var_name);
    // Step 4: 处理显式初始化
    if (node->sons.size() > 2) {
        std::vector<InitElement> flatten_nodes;
        // int linear_index = 0;
        std::vector<int> index_counters(dimensions.size(), 0); // 初始化index_counters
        int now_rank = 0;
        int level = -1;
        int large_rank = 1;
        flatten_array_init(var_name,
                           node->sons[2],
                           flatten_nodes,
                           index_counters,
                           dimensions,
                           now_rank,
                           large_rank,
                           level);
        node->blockInsts.addInst(node->sons[2]->blockInsts);
        node->val = array_val;
    }

    return true;
}

bool IRGenerator::ir_global_array_var_def_declare(ast_node * node)
{
    if (!node)
        return false;

    // Step 1: 提取维度信息
    std::vector<int32_t> dimensions;
    std::string var_name = node->sons[0]->name; // 获取变量名
    ast_node * dim_length = node->sons[1];      // 获取维度节点

    // 提取所有维度
    for (auto dim_node: dim_length->sons) {
        int temp = ir_const_exp(dim_node);
        dimensions.push_back(static_cast<int32_t>(temp));
    }

    // Step 2: 获取指针类型
    PointerType * pointerType = PointerType::getNonConstPointerType(node->parent->sons[0]->type);
    node->val = module->newArrayValue(pointerType, var_name, dimensions);

    // 计算数组总大小
    int total_size = 1;
    for (auto d: dimensions)
        total_size *= d;

    // 获取数组变量的实际值
    Value * array_val = module->findVarValue(var_name);

    // Step 4: 处理显式初始化
    if (node->sons.size() > 2) {
        std::vector<InitElement> flatten_nodes;
        // int linear_index = 0;
        std::vector<int> index_counters(dimensions.size(), 0); // 初始化index_counters
        int now_rank = 0;
        int level = -1;
        int large_rank = 1;
        flatten_array_init(var_name,
                           node->sons[2],
                           flatten_nodes,
                           index_counters,
                           dimensions,
                           now_rank,
                           large_rank,
                           level);
        node->blockInsts.addInst(node->sons[2]->blockInsts);

        node->val = array_val;
    }

    return true;
}