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

    /* 函数定义 */
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_DEF] = &IRGenerator::ir_function_define;
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGenerator::ir_function_formal_params;

    /* 语句块 */
    ast2ir_handlers[ast_operator_type::AST_OP_BLOCK] = &IRGenerator::ir_block;
    ast2ir_handlers[ast_operator_type::AST_OP_IF_ELSE_STMT] = &IRGenerator::ir_if_else;
    ast2ir_handlers[ast_operator_type::AST_OP_NESTED_BLOCK] = &IRGenerator::ir_nested_block;

    /* 编译单元 */
    ast2ir_handlers[ast_operator_type::AST_OP_COMPILE_UNIT] = &IRGenerator::ir_compile_unit;
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

    for (auto son: node->sons) {

        // 遍历编译单元，要么是函数定义，要么是语句
        ast_node * son_node = ir_visit_ast_node(son);
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
    LabelInstruction * exitLabelInst = new LabelInstruction(newFunc);

    // 函数出口指令保存到函数信息中，因为在语义分析函数体时return语句需要跳转到函数尾部，需要这个label指令
    newFunc->setExitLabel(exitLabelInst);

    // 遍历形参，没有IR指令，不需要追加
    result = ir_function_formal_params(param_node);
    if (!result) {
        // 形参解析失败
        // TODO 自行追加语义错误处理
        return false;
    }
    node->blockInsts.addInst(param_node->blockInsts);

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
    irCode.addInst(exitLabelInst);

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
    // TODO 目前形参还不支持，直接返回true

    // 每个形参变量都创建对应的临时变量，用于表达实参转递的值
    // 而真实的形参则创建函数内的局部变量。
    // 然后产生赋值指令，用于把表达实参值的临时变量拷贝到形参局部变量上。
    // 请注意这些指令要放在Entry指令后面，因此处理的先后上要注意。

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
    LabelInstruction * exitLabelInst = new LabelInstruction(currentFunc);
    node->blockInsts.addInst(exitLabelInst);

    std::vector<ast_node *>::iterator pIter;
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        ast_node * temp = ir_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }

        node->blockInsts.addInst(temp->blockInsts);
    }
    node->val = exitLabelInst;
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
    node->blockInsts.addInst(exitLabelInst);
    ast_node * cond = ir_visit_ast_node(node->sons[0]);
    // cond->blocks是放的最后计算的变量，%t2= icmp gt %l1,100中的t2.
    node->blockInsts.addInst(cond->blockInsts);

    ast_node * branch1 = ir_visit_ast_node(node->sons[1]);
    ast_node * branch2 = ir_visit_ast_node(node->sons[2]);
    // branch1->val是一个label指令
    BranchifCondition * branch_Inst;
    branch_Inst = new BranchifCondition(module->getCurrentFunction(), cond->val, branch1->val, branch2->val);
    node->blockInsts.addInst(branch_Inst);
    node->blockInsts.addInst(branch1->blockInsts);
    node->blockInsts.addInst(branch2->blockInsts);
    node->val = exitLabelInst;
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
        ConstFloat * val = module->newConstFloat((float) node->sons[0]->float_val);
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

    val = module->findVarValue(node->sons[0]->name);

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
/// @brief 整数乘 除法AST节点翻译成线性中间IR，要根据op来判断乘除
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
    ast_node * dim_length = node->sons[1];
    std::vector<ast_node *>::iterator pIter;
    for (pIter = dim_length->sons.begin(); pIter != dim_length->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        int temp = ir_const_exp(*pIter);
        _dimensions.push_back(static_cast<int32_t>(temp));
    }

    // Function * func = module->getCurrentFunction();
    // const Type * baseType = dim_length->sons[0]->type; // 这是基础类型
    PointerType * pointerType = PointerType::getNonConstPointerType(node->parent->sons[0]->type);
    node->val = module->newArrayValue(pointerType, var_name, _dimensions);
    return true;
    //数组初始化不会写，先空了
    // func->newLocalVarValue(dim_length->sons[0]->type, var_name, func->getScopeLevel(), _dimensions);
    //如果有第三个儿子，说明变量再声明的时候同时初始化。AST_OP_ARRAY_INIT_VAL
    // if (node->sons.size() > 2) {
    //     ast_node * initi = node->sons[2]; //转到初始化

    //     for (auto * init_node: initi->sons) {
    // 计算当前初始化值
    // Value * initVal = module->newConstInt(ir_const_exp(init_node));
    // 生成乘法指令
    // Value * mulResult = module->newTempVar(IntegerType::getTypeInt());
    // node->blockInsts.addInst(new BinaryInstruction(BinaryOp::Mul, mulResult, currentVal, initVal));

    // // 生成加法指令
    // Value * addResult = module->newTempVar(IntegerType::getTypeInt());
    // node->blockInsts.addInst(new BinaryInstruction(BinaryOp::Add, addResult, mulResult, initVal));

    // // 更新当前值
    // currentVal = addResult;
}

// 最终结果赋值给数组变量
// node->blockInsts.addInst(new MoveInstruction(func, node->val, currentVal));
// }

// if (node->sons.size() > 2) {
//     ast_node * initi = node->sons[2];
//     int idx = 0;
//     if (initi->node_type == ast_operator_type::AST_OP_ARRAY_INIT_VAL) {
//         //依次遍历每一个赋值语句
//         for (pIter = initi->sons.begin(); pIter != initi->sons.end(); ++pIter) {
//             ast_node * assign_op = (*pIter)->sons[0];
//             // 遍历Block的每个语句，进行显示或者运算
//             ast_node * right = ir_visit_ast_node(assign_op);
//             // Value * element = module->newArrayElement(array_value, index);
//             std::string indexed_name = var_name + "[" + std::to_string(idx) + "]";
//             Value * val = module->newVarValue(right->type, indexed_name);
//             idx++;
//             node->blockInsts.addInst(new MoveInstruction(func, val, right->val));
//         }
//     }
// }
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
    Value * array_Value = module->findVarValue(var_name);

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

    val = module->findVarValue(node->name);

    node->val = val;

    return true;
}