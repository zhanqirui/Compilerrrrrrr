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
#include "LoadInstruction.h"
#include "BranchifCondition.h"
#include "UnaryInstruction.h"
#include "BitcastInstruction.h"
#include "MemcpyInstruction.h"
#include "MemsetInstruction.h"
#include "GetElementPtrInstruction.h"
#include "ZextInstruction.h"
#include "CastInstruction.h"
#define Instanceof(res, type, var) auto res = dynamic_cast<type>(var)

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
    ast2ir_handlers[ast_operator_type::AST_OP_EXPR_STMT] = &IRGenerator::ir_visitExp;
    // 一元表达式AST_OP_UNARY_EXP
    ast2ir_handlers[ast_operator_type::AST_OP_UNARY_EXP] = &IRGenerator::ir_add;
    ast2ir_handlers[ast_operator_type::AST_OP_UNARY_OP] = &IRGenerator::ir_visitUNARYOP;
    // const 数组
    ast2ir_handlers[ast_operator_type::AST_OP_CONST_DECL] = &IRGenerator::ir_const_declare;
    // 数组访问
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_ACCESS] = &IRGenerator::ir_array_acess;
    /* 语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_ASSIGN_STMT] = &IRGenerator::ir_assign;
    ast2ir_handlers[ast_operator_type::AST_OP_RETURN] = &IRGenerator::ir_return;
    ast2ir_handlers[ast_operator_type::AST_OP_BREAK] = &IRGenerator::ir_break;
    ast2ir_handlers[ast_operator_type::AST_OP_CONTINUE] = &IRGenerator::ir_continue;
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
        printf("Error: function define in function\n");
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
    // LLVM IR没有入口指令，所以直接把入口指令先注释掉，或者我看到有些地方有有些地方没有，可以存疑
    irCode.addInst(new EntryInstruction(newFunc));

    // 创建出口指令并不加入出口指令，等函数内的指令处理完毕后加入出口指令
    LabelInstruction * entryLabelInst = new LabelInstruction(newFunc);
    LabelInstruction * returnLabelInst = new LabelInstruction(newFunc);
    module->getCurrentFunction()->set_fun_return_Lable(returnLabelInst);

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
        if (type_node->type->isIntegerType()) {
            // 保存函数返回值变量到函数信息中，在return语句翻译时需要设置值到这个变量中
            retValue = static_cast<LocalVariable *>(module->newVarValue(type_node->type));
            MoveInstruction * movInst =
                new MoveInstruction(module->getCurrentFunction(), retValue, module->newConstInt((int32_t) 0));
            irCode.addInst(movInst);
        } else {
            // 保存函数返回值变量到函数信息中，在return语句翻译时需要设置值到这个变量中
            retValue = static_cast<LocalVariable *>(module->newVarValue(type_node->type));
            MoveInstruction * movInst =
                new MoveInstruction(module->getCurrentFunction(), retValue, module->newConstFloat((int32_t) 0));
            irCode.addInst(movInst);
        }

    } else {
        retValue = static_cast<LocalVariable *>(module->newVarValue(IntegerType::getTypeInt()));
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

    irCode.addInst(new GotoInstruction(module->getCurrentFunction(), returnLabelInst));
    irCode.addInst(returnLabelInst);
    LoadInstruction * Dereference = new LoadInstruction(module->getCurrentFunction(), newFunc->getReturnValue(), true);
    irCode.addInst(Dereference);
    if (!type_node->type->isVoidType())
        irCode.addInst(new ExitInstruction(newFunc, Dereference));
    else
        irCode.addInst(new ExitInstruction(newFunc, nullptr));

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

            param_type = ptrType;
        } else {
            var = module->newVarValue(param_type, param_name);
        }
        var->is_come_from_formalparm = true;
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

/// @brief 判断 return 语句是否位于 if-else 块中
/// @param node 当前的 return 语句节点
/// @return 如果位于 if-else 块中返回 true，否则返回 false
bool IRGenerator::isReturnInIfElse(ast_node * node)
{

    // 不断访问 parent 节点
    while (node) {
        // 如果遇到 if-else 块，返回 true
        if (node->node_type == ast_operator_type::AST_OP_IF_ELSE_STMT) {
            return true;
        }

        // 如果遇到函数定义块，停止搜索
        if (node->node_type == ast_operator_type::AST_OP_FUNC_DEF) {
            break;
        }

        // 继续访问 parent 节点
        node = node->parent;
    }

    // 如果未找到 if-else 块，返回 false
    return false;
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
        if ((*pIter)->node_type == ast_operator_type::AST_OP_WHILE) {
            node->blockInsts.addInst(
                new GotoInstruction(module->getCurrentFunction(), static_cast<Instruction *>(temp->val)));
        }
        if ((*pIter)->node_type == ast_operator_type::AST_OP_IF_ELSE_STMT) {
            node->blockInsts.addInst(
                new GotoInstruction(module->getCurrentFunction(), static_cast<Instruction *>(temp->val)));
        }
        node->blockInsts.addInst(temp->blockInsts);
        if (module->getCurrentFunction()->is_real_return == true) {
            break;
        }
        if ((*pIter)->node_type == ast_operator_type::AST_OP_BREAK ||
            (*pIter)->node_type == ast_operator_type::AST_OP_CONTINUE) {
            break;
        }
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
    LabelInstruction * entryLabelInst;
    Function * currentFunc = module->getCurrentFunction();
    if (!(node->parent->node_type == ast_operator_type::AST_OP_BLOCK)) {
        entryLabelInst = new LabelInstruction(currentFunc);
        node->blockInsts.addInst(entryLabelInst);
    }

    std::vector<ast_node *>::iterator pIter;
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        ast_node * temp = ir_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }

        node->blockInsts.addInst(temp->blockInsts);
        if (module->getCurrentFunction()->is_real_return == true) {
            break;
        }
        // if ((*pIter)->node_type == ast_operator_type::AST_OP_BLOCK) {
        //     break;
        // }
    }
    if (!(node->parent->node_type == ast_operator_type::AST_OP_BLOCK)) {
        node->val = entryLabelInst;
    }

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

    LabelInstruction * exitLabelInst = new LabelInstruction(currentFunc);
    LabelInstruction * entryLabelInst = nullptr;
    entryLabelInst = new LabelInstruction(currentFunc);
    node->blockInsts.addInst(entryLabelInst);
    ast_node *cond, *branch1, *branch2;
    BinaryInstruction * NEQ_ZERO_Inst;
    BranchifCondition * branch_Inst;
    LabelInstruction *parent_ifelse_Lable1, *parent_ifelse_Lable2;
    parent_ifelse_Lable1 = module->getCurrentFunction()->get_ifelse_Lable1();
    parent_ifelse_Lable2 = module->getCurrentFunction()->get_ifelse_Lable2();
    ConstInt * ZERO = module->newConstInt(0);
    // 可能不存在else分支，只有单if
    if (node->sons.size() >= 3) {
        branch1 = ir_visit_ast_node(node->sons[1]);
        branch2 = ir_visit_ast_node(node->sons[2]);
        module->getCurrentFunction()->set_ifelse_Lable1(static_cast<LabelInstruction *>(branch1->val));
        module->getCurrentFunction()->set_ifelse_Lable2(static_cast<LabelInstruction *>(branch2->val));
        //条件后判断，现有branch1的label，才能短路求值
        cond = ir_visit_ast_node(node->sons[0]);
        NEQ_ZERO_Inst = new BinaryInstruction(module->getCurrentFunction(),
                                              IRInstOperator::IRINST_OP_NE_I,
                                              cond->val,
                                              ZERO,
                                              IntegerType::getTypeBool());
        branch_Inst = new BranchifCondition(module->getCurrentFunction(),
                                            NEQ_ZERO_Inst,
                                            static_cast<Value *>(branch1->val),
                                            static_cast<Value *>(branch2->val));
        node->blockInsts.addInst(cond->blockInsts);
        node->blockInsts.addInst(NEQ_ZERO_Inst);
        node->blockInsts.addInst(branch_Inst);
        node->blockInsts.addInst(branch1->blockInsts);
        node->blockInsts.addInst(new GotoInstruction(currentFunc, exitLabelInst));
        node->blockInsts.addInst(branch2->blockInsts);
        node->blockInsts.addInst(new GotoInstruction(currentFunc, exitLabelInst));
    } else if (node->sons.size() == 1) {
        module->getCurrentFunction()->set_ifelse_Lable1(static_cast<LabelInstruction *>(branch1->val));
        module->getCurrentFunction()->set_ifelse_Lable2(exitLabelInst);
        cond = ir_visit_ast_node(node->sons[0]);
        node->blockInsts.addInst(cond->blockInsts);
        if (!(node->blockInsts.code.back()->getOp() == IRInstOperator::IRINST_OP_GOTO)) {
            node->blockInsts.addInst(new GotoInstruction(currentFunc, exitLabelInst));
        }
    } else {
        branch1 = ir_visit_ast_node(node->sons[1]);
        module->getCurrentFunction()->set_ifelse_Lable1(static_cast<LabelInstruction *>(branch1->val));
        module->getCurrentFunction()->set_ifelse_Lable2(exitLabelInst);
        cond = ir_visit_ast_node(node->sons[0]);

        NEQ_ZERO_Inst = new BinaryInstruction(module->getCurrentFunction(),
                                              IRInstOperator::IRINST_OP_NE_I,
                                              cond->val,
                                              ZERO,
                                              IntegerType::getTypeBool());
        branch_Inst = new BranchifCondition(module->getCurrentFunction(),
                                            NEQ_ZERO_Inst,
                                            static_cast<Value *>(branch1->val),
                                            static_cast<Value *>(exitLabelInst));

        node->blockInsts.addInst(cond->blockInsts);
        node->blockInsts.addInst(NEQ_ZERO_Inst);
        node->blockInsts.addInst(branch_Inst);
        node->blockInsts.addInst(branch1->blockInsts);
        if (!(node->blockInsts.code.back()->getOp() == IRInstOperator::IRINST_OP_GOTO)) {
            node->blockInsts.addInst(new GotoInstruction(currentFunc, exitLabelInst));
        }
    }
    node->blockInsts.addInst(exitLabelInst);
    node->val = entryLabelInst;
    // 离开作用域
    if (node->needScope) {
        module->leaveScope();
    }
    module->getCurrentFunction()->set_ifelse_Lable1(parent_ifelse_Lable1);
    module->getCurrentFunction()->set_ifelse_Lable2(parent_ifelse_Lable2);
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
    LabelInstruction *parent_block_entry_Lable, *parent_block_exit_Lable;
    //保存当前的出入口，if和while都要相应保留
    parent_block_entry_Lable = currentFunc->getblock_entry_Lable();
    parent_block_exit_Lable = currentFunc->getblock_exit_Lable();
    currentFunc->set_block_entry_Lable(entryLabelInst);
    currentFunc->set_block_exit_Lable(exitLabelInst);
    node->blockInsts.addInst(entryLabelInst);
    ConstInt * ZERO = module->newConstInt(0);
    ast_node * cond = ir_visit_ast_node(node->sons[0]);
    BinaryInstruction * NEQ_ZERO_Inst = new BinaryInstruction(module->getCurrentFunction(),
                                                              IRInstOperator::IRINST_OP_NE_I,
                                                              cond->val,
                                                              ZERO,
                                                              IntegerType::getTypeBool());
    // cond->blocks是放的最后计算的变量，%t2= icmp gt %l1,100中的t2.
    node->blockInsts.addInst(cond->blockInsts);
    node->blockInsts.addInst(NEQ_ZERO_Inst);
    // nested_block->val是语块的的一个label，也就是开头
    ast_node * nested_block = ir_visit_ast_node(node->sons[1]);
    BranchifCondition * branch_Inst;
    LabelInstruction * breakLabelInst = nullptr;
    LabelInstruction * continueLabelInst = nullptr;
    if (node->sons[1]->node_type == ast_operator_type::AST_OP_BREAK) {
        //主要是为了解决while(1)break的问题，continue不再block内
        breakLabelInst = new LabelInstruction(currentFunc);
        branch_Inst = new BranchifCondition(module->getCurrentFunction(), NEQ_ZERO_Inst, breakLabelInst, exitLabelInst);
    } else if (node->sons[1]->node_type == ast_operator_type::AST_OP_CONTINUE) {
        /// continue为验证
        continueLabelInst = new LabelInstruction(currentFunc);
        branch_Inst =
            new BranchifCondition(module->getCurrentFunction(), NEQ_ZERO_Inst, continueLabelInst, entryLabelInst);
    } else {
        branch_Inst =
            new BranchifCondition(module->getCurrentFunction(), NEQ_ZERO_Inst, nested_block->val, exitLabelInst);
    }
    node->blockInsts.addInst(branch_Inst);
    if (breakLabelInst != nullptr) {
        node->blockInsts.addInst(breakLabelInst);
    }
    node->blockInsts.addInst(nested_block->blockInsts);

    node->blockInsts.addInst(new GotoInstruction(currentFunc, entryLabelInst));

    node->val = entryLabelInst;

    node->blockInsts.addInst(exitLabelInst);
    // 离开作用域
    if (node->needScope) {
        module->leaveScope();
    }
    currentFunc->set_block_entry_Lable(parent_block_entry_Lable);
    currentFunc->set_block_exit_Lable(parent_block_exit_Lable);
    return true;
}
/// @brief return节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_return(ast_node * node)
{
    ast_node * right = nullptr;
    ast_node * son_node;
    LabelInstruction * labelInst;
    if (node->parent->node_type == ast_operator_type::AST_OP_IF_ELSE_STMT) {
        labelInst = new LabelInstruction(module->getCurrentFunction());
        node->blockInsts.addInst(labelInst);
    }
    // return语句可能没有没有表达式，也可能有，因此这里必须进行区分判断
    if (!node->sons.empty()) {

        son_node = node->sons[0];

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
        node->blockInsts.addInst(right->blockInsts);
        if (right->val->type->isFloatType() && currentFunc->getReturnValue()->type->isIntegerType()) {
            CastInstruction * castInst =
                new CastInstruction(currentFunc, CastInstruction::FPTOSI, right->val, IntegerType::getTypeInt());
            node->blockInsts.addInst(castInst);
            node->blockInsts.addInst(new MoveInstruction(currentFunc, currentFunc->getReturnValue(), castInst));
        } else if (right->val->type->isIntegerType() && currentFunc->getReturnValue()->type->isFloatType()) {
            CastInstruction * castInst =
                new CastInstruction(currentFunc, CastInstruction::SITOFP, right->val, FloatType::getTypeFloat());
            node->blockInsts.addInst(castInst);
            node->blockInsts.addInst(new MoveInstruction(currentFunc, currentFunc->getReturnValue(), castInst));
        } else {
            node->blockInsts.addInst(new MoveInstruction(currentFunc, currentFunc->getReturnValue(), right->val));
        }

    } else {
        // 没有返回值
        node->val = nullptr;
    }

    // 跳转到函数的尾部出口指令上
    // node->blockInsts.addInst(new GotoInstruction(currentFunc, currentFunc->getExitLabel()));
    if (node->parent->node_type == ast_operator_type::AST_OP_IF_ELSE_STMT) {
        node->val = labelInst;
    } else {
        node->val = right->val;
    }
    module->getCurrentFunction()->is_real_return = !(isReturnInIfElse(node));
    if (!(module->getCurrentFunction()->is_real_return)) {
        node->blockInsts.addInst(
            new GotoInstruction(module->getCurrentFunction(), module->getCurrentFunction()->get_fun_return_Lable()));
    }

    return true;
}
bool IRGenerator::ir_break(ast_node * node)
{

    Function * currentFunc = module->getCurrentFunction();
    GotoInstruction * inst = new GotoInstruction(currentFunc, currentFunc->getblock_exit_Lable());
    LabelInstruction * label_inst;
    if (node->parent->node_type == ast_operator_type::AST_OP_IF_ELSE_STMT) {
        label_inst = new LabelInstruction(module->getCurrentFunction());
        node->blockInsts.addInst(label_inst);
        node->blockInsts.addInst(inst);
        node->val = label_inst;
    } else {
        node->blockInsts.addInst(inst);
        node->val = inst;
    }

    return true;
}
bool IRGenerator::ir_continue(ast_node * node)
{

    Function * currentFunc = module->getCurrentFunction();
    GotoInstruction * inst = new GotoInstruction(currentFunc, currentFunc->getblock_entry_Lable());
    node->blockInsts.addInst(inst);
    node->val = inst;
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
    ConstInt * ZERO = module->newConstInt(0);
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];
    //针对not情况
    if (node->node_type == ast_operator_type::AST_OP_UNARY_EXP && src1_node->op_type == Op::NOT) {
        Value * resultPtr = module->getCurrentFunction()->getReturnValue();
        ast_node * right = ir_visit_ast_node(src2_node);
        BranchifCondition * branch_Inst = nullptr;
        LabelInstruction * label_true = new LabelInstruction(module->getCurrentFunction());
        LabelInstruction * label_false = new LabelInstruction(module->getCurrentFunction());
        LabelInstruction * label_exit = new LabelInstruction(module->getCurrentFunction());
        BinaryInstruction * BinInst = new BinaryInstruction(module->getCurrentFunction(),
                                                            IRInstOperator::IRINST_OP_NE_I,
                                                            ZERO,
                                                            right->val,
                                                            IntegerType::getTypeInt());
        branch_Inst = new BranchifCondition(module->getCurrentFunction(), BinInst, label_true, label_false);
        node->blockInsts.addInst(right->blockInsts);
        node->blockInsts.addInst(BinInst);
        node->blockInsts.addInst(branch_Inst);
        // 7. true分支：store 1
        node->blockInsts.addInst(label_true);
        node->blockInsts.addInst(new MoveInstruction(module->getCurrentFunction(), resultPtr, module->newConstInt(0)));
        node->blockInsts.addInst(new GotoInstruction(module->getCurrentFunction(), label_exit));

        // 8. false分支：store 0
        node->blockInsts.addInst(label_false);
        node->blockInsts.addInst(new MoveInstruction(module->getCurrentFunction(), resultPtr, module->newConstInt(1)));
        node->blockInsts.addInst(new GotoInstruction(module->getCurrentFunction(), label_exit));
        // 9. exit分支：load结果
        node->blockInsts.addInst(label_exit);
        LoadInstruction * resultVal = new LoadInstruction(module->getCurrentFunction(), resultPtr, true);
        node->blockInsts.addInst(resultVal);
        node->val = resultVal;
        return true;
    }
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    if (left->val && left->val->isConst() && right->val && right->val->isConst()) {
        if (left->val->type->isFloatType() || left->val->type->isFloatType()) {
            node->val = module->newConstFloat((op == Op::ADD) ? (left->val->real_int + right->val->real_int)
                                                              : (left->val->real_int - right->val->real_int));
            node->val->real_float = (op == Op::ADD) ? (left->val->real_float + right->val->real_float)
                                                    : (left->val->real_float - right->val->real_float);
            node->val->setConst(true);
            return true;
        }
        node->val = module->newConstInt((op == Op::ADD) ? (left->val->real_int + right->val->real_int)
                                                        : (left->val->real_int - right->val->real_int));
        node->val->real_float = (op == Op::ADD) ? (left->val->real_float + right->val->real_float)
                                                : (left->val->real_float - right->val->real_float);
        node->val->setConst(true);
        return true;
    }

    BinaryInstruction * addInst;
    StoreInstruction * LstoInst = nullptr;
    StoreInstruction * RstoInst = nullptr;
    ZextInstruction * zertinst = nullptr;
    ZextInstruction * Lzertinst = nullptr;
    ZextInstruction * Rzertinst = nullptr;
    IRInstOperator irOp = (op == Op::ADD) ? IRInstOperator::IRINST_OP_ADD_I : IRInstOperator::IRINST_OP_SUB_I;
    if (node->node_type == ast_operator_type::AST_OP_UNARY_EXP) {
        Value * val = RstoInst ? RstoInst : right->val;
        if (val->type->toString() == "i1") {
            zertinst = new ZextInstruction(module->getCurrentFunction(), val, IntegerType::getTypeInt());
        }
        if (src1_node->op_type == Op::NEG) {
            addInst = new BinaryInstruction(module->getCurrentFunction(),
                                            IRInstOperator::IRINST_OP_SUB_I,
                                            ZERO,
                                            zertinst ? zertinst : val,
                                            IntegerType::getTypeInt());
            // 针对const int N=-1优化
            addInst->real_float = -right->val->real_float;
            addInst->real_int = -right->val->real_int;
        } else {
            addInst = new BinaryInstruction(module->getCurrentFunction(),
                                            IRInstOperator::IRINST_OP_ADD_I,
                                            ZERO,
                                            zertinst ? zertinst : val,
                                            IntegerType::getTypeInt());
            // 针对const int N=1优化
            addInst->real_float = right->val->real_float;
            addInst->real_int = right->val->real_int;
        }
    } else {

        Value * L = LstoInst ? LstoInst : left->val;
        Value * R = RstoInst ? RstoInst : right->val;

        if (L->type->toString() == "i1") {
            Lzertinst = new ZextInstruction(module->getCurrentFunction(), L, IntegerType::getTypeInt());
            // node->blockInsts.addInst(Lzertinst);
        }
        if (R->type->toString() == "i1") {
            Rzertinst = new ZextInstruction(module->getCurrentFunction(), R, IntegerType::getTypeInt());
            // node->blockInsts.addInst(Rzertinst);
        }
        addInst = new BinaryInstruction(module->getCurrentFunction(),
                                        irOp,
                                        Lzertinst ? Lzertinst : L,
                                        Rzertinst ? Rzertinst : R,
                                        IntegerType::getTypeInt());
        addInst->real_int = (op == Op::ADD) ? L->real_int + R->real_int : L->real_int - R->real_int;
        addInst->real_float = (op == Op::ADD) ? L->real_float + R->real_float : L->real_float - R->real_float;
    }

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
    // if (RLoadInst) {
    //     node->blockInsts.addInst(RLoadInst);
    // }
    if (Lzertinst)
        node->blockInsts.addInst(Lzertinst);
    if (Rzertinst)
        node->blockInsts.addInst(Rzertinst);
    if (zertinst)
        node->blockInsts.addInst(zertinst);
    node->blockInsts.addInst(addInst);

    node->val = addInst;

    return true;
}

/// @brief 整数乘 除法AST节点翻译成线性中间IR,要根据op来判断乘除
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败

bool IRGenerator::ir_visitUNARYOP(ast_node * node)
{
    return true;
}
bool IRGenerator::ir_mul(ast_node * node)
{
    Op op = node->op_type;
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];
    // 加法的左边操作数

    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    if (left->val && left->val->isConst() && right->val && right->val->isConst()) {
        if (left->val->type->isFloatType() || left->val->type->isFloatType()) {
            node->val = module->newConstFloat((op == Op::MUL)   ? (left->val->real_int * right->val->real_int)
                                              : (op == Op::DIV) ? (left->val->real_int / right->val->real_int)
                                                                : (left->val->real_int % right->val->real_int));
            node->val->real_float = (op == Op::MUL)   ? (left->val->real_float * right->val->real_float)
                                    : (op == Op::DIV) ? (left->val->real_int / right->val->real_int)
                                                      : (left->val->real_float / right->val->real_float);
            node->val->setConst(true);
            return true;
        }
        node->val = module->newConstInt((op == Op::MUL)   ? (left->val->real_int * right->val->real_int)
                                        : (op == Op::DIV) ? (left->val->real_int / right->val->real_int)
                                                          : (left->val->real_int % right->val->real_int));
        node->val->real_float = (op == Op::MUL)   ? (left->val->real_float * right->val->real_float)
                                : (op == Op::DIV) ? (left->val->real_int / right->val->real_int)
                                                  : (left->val->real_float / right->val->real_float);
        node->val->setConst(true);
        return true;
    }

    BinaryInstruction * mulInst;
    StoreInstruction * LstoInst = nullptr;
    StoreInstruction * RstoInst = nullptr;
    MoveInstruction * LMoveInst = nullptr;
    MoveInstruction * RMoveInst = nullptr;

    // if (left->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
    //     LMoveInst = new MoveInstruction(module->getCurrentFunction(), left->val, true);
    // }
    // if (right->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
    //     RstoInst = new StoreInstruction(module->getCurrentFunction(), right->val, true);
    // }
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
    LabelInstruction * label_inst;
    // 如果当前节点是叶子节点，直接生成IR

    //对于if ((25 - 7) != (36 - 6 * 3)) putch(66);情况的特殊情况
    if (node->node_type == ast_operator_type::AST_OP_EXPR_STMT &&
        node->parent->node_type == ast_operator_type::AST_OP_IF_ELSE_STMT) {
        label_inst = new LabelInstruction(module->getCurrentFunction());
        node->val = label_inst;
        node->blockInsts.addInst(label_inst);
        node->blockInsts.addInst(temp->blockInsts);
    } else if (node->node_type == ast_operator_type::AST_OP_EXPR_STMT &&
               node->parent->node_type == ast_operator_type::AST_OP_WHILE) {
        label_inst = new LabelInstruction(module->getCurrentFunction());
        node->val = label_inst;
        node->blockInsts.addInst(label_inst);
        node->blockInsts.addInst(temp->blockInsts);
    } else {
        node->val = temp->val;
        node->blockInsts.addInst(temp->blockInsts);
    }
    return true;
}
bool IRGenerator::ir_visitLogitExp(ast_node * node)
{
    // 判断当前节点是否为空
    if (!node) {
        return false;
    }
    ast_operator_type Node_Type = node->node_type;
    IRInstOperator irOp = (node->node_type == ast_operator_type::AST_OP_LAND_EXP) ? IRInstOperator::IRINST_OP_AND_I
                                                                                  : IRInstOperator::IRINST_OP_OR_I;
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点
    Value * resultPtr = module->getCurrentFunction()->getReturnValue();
    // Value * resultPtr = new AllocaInstruction(module->getCurrentFunction(), IntegerType::getTypeBool());
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left)
        return false;
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right)
        return false;

    // 3. 生成判断左、右是否为真
    ConstInt * ZERO = module->newConstInt(0);
    BinaryInstruction * LEQ_ZERO_Inst = new BinaryInstruction(module->getCurrentFunction(),
                                                              IRInstOperator::IRINST_OP_NE_I,
                                                              left->val,
                                                              ZERO,
                                                              IntegerType::getTypeBool());
    BinaryInstruction * REQ_ZERO_Inst = new BinaryInstruction(module->getCurrentFunction(),
                                                              IRInstOperator::IRINST_OP_NE_I,
                                                              right->val,
                                                              ZERO,
                                                              IntegerType::getTypeBool());

    // 4. 创建各个label
    LabelInstruction * label_true = new LabelInstruction(module->getCurrentFunction());
    LabelInstruction * label_false = new LabelInstruction(module->getCurrentFunction());
    LabelInstruction * label_exit = new LabelInstruction(module->getCurrentFunction());
    LabelInstruction * label_right = new LabelInstruction(module->getCurrentFunction());
    LabelInstruction * label_ifelse_true = module->getCurrentFunction()->get_ifelse_Lable1();  // ifelse真分支
    LabelInstruction * label_ifelse_false = module->getCurrentFunction()->get_ifelse_Lable2(); // ifelse 假分支
    LabelInstruction * label_ifelse_exit = module->getCurrentFunction()->get_ifelse_exit();    // ifelse的出口指令

    // 5. 生成短路分支
    BranchifCondition * branch_Inst1;
    if (node->node_type == ast_operator_type::AST_OP_LAND_EXP) {
        // && 短路：左假直接跳false，否则判断右
        branch_Inst1 = new BranchifCondition(module->getCurrentFunction(), LEQ_ZERO_Inst, label_right, label_false);
    } else {
        // || 短路：左真直接跳true，否则判断右
        branch_Inst1 = new BranchifCondition(module->getCurrentFunction(), LEQ_ZERO_Inst, label_true, label_right);
    }
    BranchifCondition * branch_Inst2 =
        new BranchifCondition(module->getCurrentFunction(), REQ_ZERO_Inst, label_true, label_false);

    // 6. 拼接IR
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(LEQ_ZERO_Inst);
    node->blockInsts.addInst(branch_Inst1);

    node->blockInsts.addInst(label_right);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(REQ_ZERO_Inst);
    node->blockInsts.addInst(branch_Inst2);

    // 7. true分支：store 1
    node->blockInsts.addInst(label_true);
    node->blockInsts.addInst(new MoveInstruction(module->getCurrentFunction(), resultPtr, module->newConstInt(1)));
    node->blockInsts.addInst(new GotoInstruction(module->getCurrentFunction(), label_exit));

    // 8. false分支：store 0
    node->blockInsts.addInst(label_false);
    node->blockInsts.addInst(new MoveInstruction(module->getCurrentFunction(), resultPtr, module->newConstInt(0)));
    node->blockInsts.addInst(new GotoInstruction(module->getCurrentFunction(), label_exit));

    // 9. exit分支：load结果
    node->blockInsts.addInst(label_exit);
    LoadInstruction * resultVal = new LoadInstruction(module->getCurrentFunction(), resultPtr, true);
    node->blockInsts.addInst(resultVal);
    node->val = resultVal;

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

    // 加法节点，左结合，先计算左节点，后计算右节点
    IRInstOperator irOp = (op == Op::GT)    ? IRInstOperator::IRINST_OP_GT_I
                          : (op == Op::EQ)  ? IRInstOperator::IRINST_OP_EQ_I
                          : (op == Op::LT)  ? IRInstOperator::IRINST_OP_LT_I
                          : (op == Op::LE)  ? IRInstOperator::IRINST_OP_LE_I
                          : (op == Op::GE)  ? IRInstOperator::IRINST_OP_GE_I
                          : (op == Op::NE)  ? IRInstOperator::IRINST_OP_NE_I
                          : (op == Op::AND) ? IRInstOperator::IRINST_OP_AND_I
                          : (op == Op::OR)  ? IRInstOperator::IRINST_OP_OR_I
                                            : IRInstOperator::IRINST_OP_DIV_I;
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
    LoadInstruction * LstoInst = nullptr;
    LoadInstruction * RstoInst = nullptr;

    // if (left->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
    //     LstoInst = new LoadInstruction(module->getCurrentFunction(), left->val, true);
    // }
    // if (right->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
    //     RstoInst = new LoadInstruction(module->getCurrentFunction(), right->val, true);
    // }

    Value * LVal = LstoInst ? LstoInst : left->val;
    Value * RVal = RstoInst ? RstoInst : right->val;
    ZextInstruction * Lzertinst = nullptr;
    ZextInstruction * Rzertinst = nullptr;
    if (LVal->type->toString() == "i1") {
        Lzertinst = new ZextInstruction(module->getCurrentFunction(), LVal, IntegerType::getTypeInt());
    }
    if (RVal->type->toString() == "i1") {
        Rzertinst = new ZextInstruction(module->getCurrentFunction(), RVal, IntegerType::getTypeInt());
    }
    mulInst = new BinaryInstruction(module->getCurrentFunction(),
                                    irOp,
                                    Lzertinst ? Lzertinst : LVal,
                                    Rzertinst ? Rzertinst : RVal,
                                    IntegerType::getTypeBool());
    BranchifCondition * branch_Inst = nullptr;
    // if (node->parent->node_type == ast_operator_type::AST_OP_IF_ELSE_STMT) {
    //     LabelInstruction *Lable1, *Lable2;
    //     Lable1 = module->getCurrentFunction()->get_ifelse_Lable1();
    //     Lable2 = module->getCurrentFunction()->get_ifelse_Lable2();
    //     branch_Inst = new BranchifCondition(module->getCurrentFunction(), mulInst, Lable1, Lable2);
    // }
    node->blockInsts.addInst(left->blockInsts);
    if (LstoInst) {
        node->blockInsts.addInst(LstoInst);
    }
    node->blockInsts.addInst(right->blockInsts);
    if (RstoInst) {
        node->blockInsts.addInst(RstoInst);
    }
    if (Lzertinst) {
        node->blockInsts.addInst(Lzertinst);
    }
    if (Rzertinst) {
        node->blockInsts.addInst(Rzertinst);
    }
    node->blockInsts.addInst(mulInst);
    if (branch_Inst != nullptr) {
        node->blockInsts.addInst(branch_Inst);
    }
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
    LabelInstruction * labelInst = nullptr;
    if (node->parent->node_type == ast_operator_type::AST_OP_IF_ELSE_STMT) {
        labelInst = new LabelInstruction(module->getCurrentFunction());
        node->blockInsts.addInst(labelInst);
    }
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
    // if (right->val->isConst()) {
    //     printf("const variable can not be assigned.");
    //     return false;
    // }
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(left->blockInsts);
    MoveInstruction * movInst = nullptr;
    if (right->val->type->isFloatType() && left->val->type->isIntegerType()) {
        CastInstruction * castInst = new CastInstruction(module->getCurrentFunction(),
                                                         CastInstruction::FPTOSI,
                                                         right->val,
                                                         IntegerType::getTypeInt());
        node->blockInsts.addInst(castInst);
        node->blockInsts.addInst(new MoveInstruction(module->getCurrentFunction(), left->val, castInst));
    } else if (right->val->type->isIntegerType() && left->val->type->isFloatType()) {
        CastInstruction * castInst = new CastInstruction(module->getCurrentFunction(),
                                                         CastInstruction::SITOFP,
                                                         right->val,
                                                         FloatType::getTypeFloat());
        node->blockInsts.addInst(castInst);
        node->blockInsts.addInst(new MoveInstruction(module->getCurrentFunction(), left->val, castInst));
    } else {
        node->blockInsts.addInst(new MoveInstruction(module->getCurrentFunction(), left->val, right->val));
    }
    // movInst = new MoveInstruction(module->getCurrentFunction(), left->val, right->val);

    // 这里假定赋值的类型是一致的
    if (node->parent->node_type == ast_operator_type::AST_OP_IF_ELSE_STMT) {
        node->val = labelInst;
    } else {
        node->val = movInst;
    }

    return true;
}

// AST_OP_SCALAR_INIT
bool IRGenerator::ir_scalar_init(ast_node * node)
{
    ast_node * left_val_node = node->parent;
    ast_node * right_node = node->sons[0];
    ast_node * type_node = node->parent->parent->sons[0];

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
    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left_val_node->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    MoveInstruction * movInst;
    if (right->val->isConst()) {
        if (type_node->type->isFloatType()) {
            Value * fVal = module->newConstFloat(right->val->real_float);
            movInst = new MoveInstruction(module->getCurrentFunction(), left_val_node->val, fVal);
        } else {
            Value * i32Val = module->newConstInt((int) right->val->real_float);
            movInst = new MoveInstruction(module->getCurrentFunction(), left_val_node->val, i32Val);
        }
        node->blockInsts.addInst(movInst);
    } else {
        if (right->val->type->isFloatType() && type_node->type->isIntegerType()) {
            CastInstruction * castInst = new CastInstruction(module->getCurrentFunction(),
                                                             CastInstruction::FPTOSI,
                                                             right->val,
                                                             IntegerType::getTypeInt());
            node->blockInsts.addInst(castInst);
            node->blockInsts.addInst(new MoveInstruction(module->getCurrentFunction(), left_val_node->val, castInst));
        } else if (right->val->type->isIntegerType() && type_node->type->isFloatType()) {
            CastInstruction * castInst = new CastInstruction(module->getCurrentFunction(),
                                                             CastInstruction::SITOFP,
                                                             right->val,
                                                             FloatType::getTypeFloat());
            node->blockInsts.addInst(castInst);
            node->blockInsts.addInst(new MoveInstruction(module->getCurrentFunction(), left_val_node->val, castInst));
        } else {
            node->blockInsts.addInst(new MoveInstruction(module->getCurrentFunction(), left_val_node->val, right->val));
        }
    }

    // 这里假定赋值的类型是一致的
    // node->val = movInst;
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
        if (exp_node->sons[0]->node_type != ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
            module->getCurrentFunction()->is_const_func_var = false;
        }
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
        array_val->addElement(linear_index,
                              element_node->val->real_int,
                              element_node->val->real_float,
                              element_node->val,
                              (exp_node->sons[0]->node_type != ast_operator_type::AST_OP_LEAF_LITERAL_UINT) ? true
                                                                                                            : false);
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
                        if (index_counters[i - 1] < dimensions[i - 1]) {
                            break;
                        }
                        i--;
                    }
                } else {
                    index_counters[i] += 1;
                }
            }
        }

        return;
    }

    // 中间层：数组初始化结构，递归展开每一层
    if (node->node_type == ast_operator_type::AST_OP_ARRAY_CONST_INIT ||
        node->node_type == ast_operator_type::AST_OP_ARRAY_INIT_VAL) {
        //每一个array-init开始前都要对index_counters在当前维度进行重置
        if (level > -1) {
            // level = -1,说明是最开始的初始化根节点，那就没必要做了
            //初始化的具体做法是当前维度直接进1，后续维度清零
            //如果是后续的第一个根节点那也不需要进位
            if (now_rank > 0) {
                index_counters[level] += 1;
            }
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
    module->getCurrentFunction()->is_const_func_var = true;
    // 计算数组总大小
    int total_size = 1;
    for (auto d: dimensions)
        total_size *= d;

    total_size = total_size * 4; // 每个元素4字节
    // 获取数组变量的实际值
    Value * array_val = module->findVarValue(var_name);
    BitcastInstruction * bitcatinst;

    // Step 4: 处理显式初始化
    if (node->sons.size() > 2 && node->sons[2]->sons.size() > 0) {
        bitcatinst = new BitcastInstruction(module->getCurrentFunction(), array_val, 8);
        node->blockInsts.addInst(bitcatinst);
        MemsetInstruction * memsetInst =
            new MemsetInstruction(module->getCurrentFunction(), bitcatinst, 0, total_size, 16);
        node->blockInsts.addInst(memsetInst);
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
        bitcatinst = new BitcastInstruction(module->getCurrentFunction(), array_val, 32);
        node->blockInsts.addInst(bitcatinst);
        for (FlattenedArrayElement & elem: array_val->flattenedArray) {
            GetElementPtrInstruction * gepInst;
            MoveInstruction * movInst;
            std::vector<int> indices = {elem.flatIndex};
            Value * flatvalue = module->newConstInt(elem.flatIndex);
            if (elem.is_use_val) {
                gepInst = new GetElementPtrInstruction(module->getCurrentFunction(), bitcatinst, flatvalue);
                node->blockInsts.addInst(gepInst);
                movInst = new MoveInstruction(module->getCurrentFunction(), gepInst, elem.val);
                node->blockInsts.addInst(movInst);
            } else {
                //得到要初始化的坐标的位置
                gepInst = new GetElementPtrInstruction(module->getCurrentFunction(), bitcatinst, flatvalue);
                node->blockInsts.addInst(gepInst);
                movInst = new MoveInstruction(module->getCurrentFunction(),
                                              gepInst,
                                              module->newConstInt((int32_t) elem.intValue));
                node->blockInsts.addInst(movInst);
            }
        }
        // }
    } else if (node->sons.size() > 2 && node->sons[2]->sons.size() == 0) {
        bitcatinst = new BitcastInstruction(module->getCurrentFunction(), array_val, 8);
        node->blockInsts.addInst(bitcatinst);
        MemsetInstruction * memsetInst =
            new MemsetInstruction(module->getCurrentFunction(), bitcatinst, 0, total_size, 16);
        node->blockInsts.addInst(memsetInst);
    }

    return true;
}

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
    // std::vector<int32_t> index;
    // arrayIndexVector存的是数组下标的结构体，其中idx为-1表示是变量，idx为-2表示是表达式
    // Value 存的是具体的下标值
    std::vector<ArrayIndex> arrayIndexVector;
    std::vector<int32_t> dim;
    // 第一个儿子是变量名称
    std::string var_name = node->sons[0]->name;
    // Value * array_Value = module->findVarValue(var_name);
    Value * array_Value = module->findVar(var_name);

    std::vector<ast_node *>::iterator pIter;
    //遍历每一个下标
    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {

        // 遍历每一个index
        if ((*pIter)->sons[0]->node_type == ast_operator_type::AST_OP_LVAL) {
            bool temp = ir_array_exp_lval(*pIter);
            arrayIndexVector.push_back({-1, (*pIter)->val});
        } else if ((*pIter)->sons[0]->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
            int temp = ir_const_exp(*pIter);
            arrayIndexVector.push_back({temp, nullptr});
            //新增数组下标还为数组元素的情况
        } else if ((*pIter)->sons[0]->node_type == ast_operator_type::AST_OP_ADD_EXP ||
                   (*pIter)->sons[0]->node_type == ast_operator_type::AST_OP_MUL_EXP ||
                   (*pIter)->sons[0]->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
            bool temp = ir_visit_ast_node(*pIter);
            node->blockInsts.addInst((*pIter)->blockInsts);
            arrayIndexVector.push_back({-2, (*pIter)->val});
        }
    }
    dim = array_Value->arraydimensionVector;

    // array_Value->arrayIndexVector = index;
    Value * currentVal = nullptr; // 当前累积的值
    int nowdim = 1;
    GetElementPtrInstruction * gepInst = nullptr;
    int flatindex = 0;
    int mul = 1;
    BinaryInstruction * mulinst;
    BinaryInstruction * addinst = nullptr;
    LoadInstruction * LoadInst;
    Value * lastInst = nullptr; //下边循环之后的结果

    //这里需要新增对数组维度的判断，如果是空数组size为0原本会报错报空指针
    if (arrayIndexVector.size() >= 2) {
        for (int i = 0; i < arrayIndexVector.size() - 1; i++) {
            if (arrayIndexVector[i].idx != -1) {
                mulinst = new BinaryInstruction(
                    module->getCurrentFunction(),
                    IRInstOperator::IRINST_OP_MUL_I,
                    lastInst ? lastInst : static_cast<Value *>(module->newConstInt((int32_t) arrayIndexVector[i].idx)),
                    module->newConstInt((int32_t) dim[i + 1]),
                    IntegerType::getTypeInt());
                node->blockInsts.addInst(mulinst);

                if (arrayIndexVector[i + 1].idx != -1) {
                    addinst = new BinaryInstruction(module->getCurrentFunction(),
                                                    IRInstOperator::IRINST_OP_ADD_I,
                                                    mulinst,
                                                    module->newConstInt((int32_t) arrayIndexVector[i + 1].idx),
                                                    IntegerType::getTypeInt());
                } else {
                    LoadInst = new LoadInstruction(module->getCurrentFunction(), arrayIndexVector[i + 1].value, true);
                    node->blockInsts.addInst(LoadInst);
                    addinst = new BinaryInstruction(module->getCurrentFunction(),
                                                    IRInstOperator::IRINST_OP_ADD_I,
                                                    mulinst,
                                                    LoadInst,
                                                    IntegerType::getTypeInt());
                }
                node->blockInsts.addInst(addinst);
            } else if (arrayIndexVector[i].value) {
                LoadInst = new LoadInstruction(module->getCurrentFunction(), arrayIndexVector[i].value, true);
                node->blockInsts.addInst(LoadInst);
                mulinst = new BinaryInstruction(module->getCurrentFunction(),
                                                IRInstOperator::IRINST_OP_MUL_I,
                                                LoadInst,
                                                module->newConstInt((int32_t) dim[i + 1]),
                                                IntegerType::getTypeInt());
                node->blockInsts.addInst(mulinst);
                if (arrayIndexVector[i + 1].idx != -1) {
                    addinst = new BinaryInstruction(module->getCurrentFunction(),
                                                    IRInstOperator::IRINST_OP_ADD_I,
                                                    mulinst,
                                                    module->newConstInt((int32_t) arrayIndexVector[i + 1].idx),
                                                    IntegerType::getTypeInt());
                } else {
                    LoadInst = new LoadInstruction(module->getCurrentFunction(), arrayIndexVector[i + 1].value, true);
                    node->blockInsts.addInst(LoadInst);
                    addinst = new BinaryInstruction(module->getCurrentFunction(),
                                                    IRInstOperator::IRINST_OP_ADD_I,
                                                    mulinst,
                                                    LoadInst,
                                                    IntegerType::getTypeInt());
                }
                node->blockInsts.addInst(addinst);
            }
            lastInst = static_cast<Value *>(addinst);
        }
    }
    BinaryInstruction * latestaddinst = addinst;
    if (arrayIndexVector.size() == 1) {
        if (arrayIndexVector[arrayIndexVector.size() - 1].idx == -1) {
            LoadInst = new LoadInstruction(module->getCurrentFunction(),
                                           arrayIndexVector[arrayIndexVector.size() - 1].value,
                                           true);
            node->blockInsts.addInst(LoadInst);
        }
        /*
        idx == -1：说明这个下标是变量（左值），它的值通过 LoadInstruction 加载。
        idx == -2：说明这是一个表达式（如 a[i+1]），已经在前面通过 ir_visit_ast_node 转换成了 Value*。
        否则，说明是一个常量数字（如 a[3]），直接创建常量值。
        */
        latestaddinst = new BinaryInstruction(
            module->getCurrentFunction(),
            IRInstOperator::IRINST_OP_ADD_I,
            addinst ? addinst : static_cast<Value *>(module->newConstInt((int32_t) 0)),
            (arrayIndexVector[arrayIndexVector.size() - 1].idx == -1) ? static_cast<Value *>(LoadInst)
            : (arrayIndexVector[arrayIndexVector.size() - 1].idx == -2)
                ? static_cast<Value *>(arrayIndexVector[arrayIndexVector.size() - 1].value)
                : static_cast<Value *>(
                      module->newConstInt((int32_t) arrayIndexVector[arrayIndexVector.size() - 1].idx)),
            IntegerType::getTypeInt());
        //处理最后一维度
        node->blockInsts.addInst(latestaddinst);
    } else {
        //这里addinst会空,报段错误
        LoadInst = new LoadInstruction(module->getCurrentFunction(), addinst, true);
        // node->blockInsts.addInst(LoadInst);
    }

    //展平成为一维度
    //形参需要再取里边的地址
    LoadInstruction * FormalParmLoadInst = nullptr;
    if (array_Value->is_come_from_formalparm) {
        FormalParmLoadInst = new LoadInstruction(module->getCurrentFunction(), array_Value, true);
        node->blockInsts.addInst(FormalParmLoadInst);
    }
    BitcastInstruction * bitcatinst =
        new BitcastInstruction(module->getCurrentFunction(), FormalParmLoadInst ? FormalParmLoadInst : array_Value, 32);
    node->blockInsts.addInst(bitcatinst);
    // gep指令遍历一维数组
    // std::vector<int> indices = {flatindex};
    gepInst = new GetElementPtrInstruction(module->getCurrentFunction(), bitcatinst, latestaddinst);
    node->blockInsts.addInst(gepInst);
    if (node->parent->node_type == ast_operator_type::AST_OP_ASSIGN_STMT) {
        currentVal = gepInst;
    } else {
        LoadInstruction * LoadInst = new LoadInstruction(module->getCurrentFunction(), gepInst, true);
        node->blockInsts.addInst(LoadInst);
        currentVal = LoadInst;
    }

    node->val = currentVal;
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
    ast_node * temp = ir_visit_ast_node(node->sons[0]);
    // 如果当前节点是叶子节点，直接生成IR
    node->val = temp->val;
    node->blockInsts.addInst(temp->blockInsts);
    // return node->integer_val;
    return node->val->real_int;
}
//用于数组a[i]的情况
bool IRGenerator::ir_array_exp_lval(ast_node * node)
{
    ast_node * son = node->sons[0];
    node->val = module->findVar(son->name);
    return true;
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
    ConstInt * ZERO = module->newConstInt(0);
    if (node->parent->node_type == ast_operator_type::AST_OP_ASSIGN_STMT) {
        node->val = val;
    } else if (node->parent->node_type == ast_operator_type::AST_OP_IF_ELSE_STMT) {
        ///这个是为了解决if (m)的问题
        LoadInstruction * LoadInst = new LoadInstruction(module->getCurrentFunction(), val, true);

        BinaryInstruction * EQ_ZERO_Inst = new BinaryInstruction(module->getCurrentFunction(),
                                                                 IRInstOperator::IRINST_OP_NE_I,
                                                                 LoadInst,
                                                                 ZERO,
                                                                 IntegerType::getTypeBool());
        // BranchifCondition * branch_Inst = new BranchifCondition(module->getCurrentFunction(),
        //                                                         EQ_ZERO_Inst,
        //                                                         module->getCurrentFunction()->get_ifelse_Lable1(),
        //                                                         module->getCurrentFunction()->get_ifelse_Lable2());
        node->val = EQ_ZERO_Inst;
        node->blockInsts.addInst(LoadInst);
        node->blockInsts.addInst(EQ_ZERO_Inst);
        // node->blockInsts.addInst(branch_Inst);

    } else if (val->isConst()) {
        node->val = val;
    } else if (node->parent->parent->node_type == ast_operator_type::AST_OP_FUNC_RPARAMS &&
               val->type->isPointerType()) {
        BitcastInstruction * bitcatinst;
        GetElementPtrInstruction * gepInst;
        LoadInstruction * LoadInst = nullptr;
        if (module->getCurrentFunction()->name != "main" && val->is_come_from_formalparm) {
            //如果是数组类型指针则不能直接load，会将数组大指针load出来，实际应该load第一个元素的地址
            LoadInst = new LoadInstruction(module->getCurrentFunction(), val, true);
            bitcatinst = new BitcastInstruction(module->getCurrentFunction(), LoadInst, 32);
            gepInst = new GetElementPtrInstruction(module->getCurrentFunction(), bitcatinst, ZERO);
        } else {
            bitcatinst = new BitcastInstruction(module->getCurrentFunction(), val, 32);
            gepInst = new GetElementPtrInstruction(module->getCurrentFunction(), bitcatinst, ZERO);
        }
        if (LoadInst)
            node->blockInsts.addInst(LoadInst);
        node->blockInsts.addInst(bitcatinst);
        node->blockInsts.addInst(gepInst);
        node->val = gepInst;

    } else {
        LoadInstruction * LoadInst =
            new LoadInstruction(module->getCurrentFunction(), val, val->getType()->isFloatType() ? false : true);
        node->blockInsts.addInst(LoadInst);
        node->val = LoadInst;
    }

    return true;
}

// 函数调用AST节点翻译成线性中间IR
bool IRGenerator::ir_func_call(ast_node * node)
{
    // node->sons[0] 是函数名节点，node->sons[1] 可能是参数节点(AST_OP_FUNC_RPARAMS)
    std::string func_name = node->sons[0]->name;
    Function * callee = module->findFunction(func_name);
    Function * curren_function = module->getCurrentFunction();
    if (!curren_function->getExistFuncCall()) {
        curren_function->setExistFuncCall(true);
    }

    if (!callee) {
        std::cerr << "Error: function not found: " << func_name << std::endl;
        return false;
    }
    //对于被调用函数进行判断，如果是内置函数则需要将函数名加入到module的InFunctionList，然后模块运行时将用到的内置函数优先new出来
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
    auto it = irMap.find(callee->getIRName());
    if (it != irMap.end()) {
        module->InFunctionList[it->second] = true;
        // InFunction为true则后面需要打印对应的内置函数
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

    // 只传递参数，不要把call结果变量也作为参数
    FuncCallInstruction * callInst =
        new FuncCallInstruction(module->getCurrentFunction(), callee, args, callee->getReturnType());

    node->blockInsts.addInst(callInst);
    node->val = callInst;
    return true;
}

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
    total_size = total_size * 4; // 每个元素4字节

    // 获取数组变量的实际值
    Value * array_val = module->findVarValue(var_name);
    Instanceof(array_global_val, GlobalVariable *, array_val);
    array_global_val->setSize(total_size);

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
    } else {
        array_global_val->setInBSSSection(true);
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
    total_size = total_size * 4;

    total_size = total_size * 4; // 每个元素4字节
    // 获取数组变量的实际值
    Value * array_val = module->findVarValue(var_name);
    BitcastInstruction * bitcatinst;

    // Step 4: 处理显式初始化
    if (node->sons.size() > 2 && node->sons[2]->sons.size() > 0) {
        bitcatinst = new BitcastInstruction(module->getCurrentFunction(), array_val, 8);
        node->blockInsts.addInst(bitcatinst);
        MemsetInstruction * memsetInst =
            new MemsetInstruction(module->getCurrentFunction(), bitcatinst, 0, total_size, 16);
        node->blockInsts.addInst(memsetInst);
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
        bitcatinst = new BitcastInstruction(module->getCurrentFunction(), array_val, 32);
        node->blockInsts.addInst(bitcatinst);
        for (FlattenedArrayElement & elem: array_val->flattenedArray) {
            GetElementPtrInstruction * gepInst;
            MoveInstruction * movInst;
            std::vector<int> indices = {elem.flatIndex};
            Value * flatvalue = module->newConstInt(elem.flatIndex);
            if (elem.is_use_val) {
                gepInst = new GetElementPtrInstruction(module->getCurrentFunction(), bitcatinst, flatvalue);
                node->blockInsts.addInst(gepInst);
                movInst = new MoveInstruction(module->getCurrentFunction(), gepInst, elem.val);
                node->blockInsts.addInst(movInst);
            } else {
                //得到要初始化的坐标的位置
                gepInst = new GetElementPtrInstruction(module->getCurrentFunction(), bitcatinst, flatvalue);
                node->blockInsts.addInst(gepInst);
                movInst = new MoveInstruction(module->getCurrentFunction(),
                                              gepInst,
                                              module->newConstInt((int32_t) elem.intValue));
                node->blockInsts.addInst(movInst);
            }
        }
        // }
    } else if (node->sons.size() > 2 && node->sons[2]->sons.size() == 0) {
        bitcatinst = new BitcastInstruction(module->getCurrentFunction(), array_val, 8);
        node->blockInsts.addInst(bitcatinst);
        MemsetInstruction * memsetInst =
            new MemsetInstruction(module->getCurrentFunction(), bitcatinst, 0, total_size, 16);
        node->blockInsts.addInst(memsetInst);
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

    // 计算数组总大小
    int total_size = 1;
    for (auto d: dimensions)
        total_size *= d;
    total_size = total_size * 4; // 每个元素4字节

    // Step 2: 获取指针类型
    PointerType * pointerType = PointerType::getNonConstPointerType(node->parent->sons[0]->type);
    node->val = module->newArrayValue(pointerType, var_name, dimensions);

    // 获取数组变量的实际值
    Value * array_val = module->findVarValue(var_name);
    Instanceof(array_global_val, GlobalVariable *, array_val);
    array_global_val->setSize(total_size);

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
    } else {
        array_global_val->setInBSSSection(true);
    }

    return true;
}