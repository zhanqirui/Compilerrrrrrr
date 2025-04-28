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

#include "AST.h"
#include "Common.h"
#include "Function.h"
#include "IRCode.h"
#include "IRGenerator.h"
#include "Module.h"
#include "EntryInstruction.h"
#include "LabelInstruction.h"
#include "ExitInstruction.h"
#include "MoveInstruction.h"
#include "GotoInstruction.h"
#include "BranchInstruction.h"
#include "ArgInstruction.h"
#include "CallInstruction.h"
#include "BinaryInstruction.h"
#include "IntegerType.h"

/// @brief 构造函数
/// @param _root AST的根
/// @param _module 符号表
IRGenerator::IRGenerator(ast_node * _root, Module * _module) : root(_root), module(_module)
{
    /* 叶子节点 */
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_LITERAL_UINT] = &IRGenerator::ir_leaf_node_uint;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_LITERAL_FLOAT] = &IRGenerator::ir_leaf_node_float;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_VAR_ID] = &IRGenerator::ir_leaf_node_var_id;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_TYPE] = &IRGenerator::ir_leaf_node_type;

    /* 表达式运算 */
    ast2ir_handlers[ast_operator_type::AST_OP_EXP] = &IRGenerator::ir_visitExp;
    ast2ir_handlers[ast_operator_type::AST_OP_ADD_EXP] = &IRGenerator::ir_add_exp;
    ast2ir_handlers[ast_operator_type::AST_OP_MUL_EXP] = &IRGenerator::ir_mul_exp;
    ast2ir_handlers[ast_operator_type::AST_OP_REL_EXP] = &IRGenerator::ir_rel_exp;
    ast2ir_handlers[ast_operator_type::AST_OP_EQ_EXP] = &IRGenerator::ir_eq_exp;
    ast2ir_handlers[ast_operator_type::AST_OP_LAND_EXP] = &IRGenerator::ir_land_exp;
    ast2ir_handlers[ast_operator_type::AST_OP_LOR_EXP] = &IRGenerator::ir_lor_exp;
    ast2ir_handlers[ast_operator_type::AST_OP_UNARY_EXP] = &IRGenerator::ir_unary_exp;
    ast2ir_handlers[ast_operator_type::AST_OP_UNARY_OP] = &IRGenerator::ir_unary_op;
    ast2ir_handlers[ast_operator_type::AST_OP_CONST_EXP] = &IRGenerator::ir_const_exp;

    /* 声明语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_CONST_DECL] = &IRGenerator::ir_const_declare;
    ast2ir_handlers[ast_operator_type::AST_OP_VAR_DECL] = &IRGenerator::ir_variable_declare;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_VAR_DEF] = &IRGenerator::ir_array_var_def_declare;
    ast2ir_handlers[ast_operator_type::AST_OP_CONST_DEF] = &IRGenerator::ir_const_def;
    ast2ir_handlers[ast_operator_type::AST_OP_VAR_DEF] = &IRGenerator::ir_var_def;
    ast2ir_handlers[ast_operator_type::AST_OP_SCALAR_CONST_INIT] = &IRGenerator::ir_scalar_const_init;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_CONST_INIT] = &IRGenerator::ir_array_const_init;
    ast2ir_handlers[ast_operator_type::AST_OP_SCALAR_INIT] = &IRGenerator::ir_scalar_init;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_INIT_VAL] = &IRGenerator::ir_array_init_val;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_CONST_DEF] = &IRGenerator::ir_array_const_def;

    /* 控制流语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_RETURN] = &IRGenerator::ir_return;
    ast2ir_handlers[ast_operator_type::AST_OP_IF_ELSE_STMT] = &IRGenerator::ir_if_else_stmt;
    ast2ir_handlers[ast_operator_type::AST_OP_WHILE] = &IRGenerator::ir_while_stmt;
    ast2ir_handlers[ast_operator_type::AST_OP_BREAK] = &IRGenerator::ir_break_stmt;
    ast2ir_handlers[ast_operator_type::AST_OP_CONTINUE] = &IRGenerator::ir_continue_stmt;
    ast2ir_handlers[ast_operator_type::AST_OP_EXPR_STMT] = &IRGenerator::ir_expr_stmt;
    ast2ir_handlers[ast_operator_type::AST_OP_ASSIGN_STMT] = &IRGenerator::ir_assign_stmt;

    /* 函数相关 */
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_DEF] = &IRGenerator::ir_function_define;
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGenerator::ir_function_formal_params;
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_FORMAL_PARAM] = &IRGenerator::ir_func_formal_param;
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_CALL] = &IRGenerator::ir_func_call;
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_RPARAMS] = &IRGenerator::ir_func_rparams;

    /* 数组相关 */
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_INDEX] = &IRGenerator::ir_array_index;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_ACCESS] = &IRGenerator::ir_array_access;
    
    /* 变量与左值 */
    ast2ir_handlers[ast_operator_type::AST_OP_LVAL] = &IRGenerator::ir_lval;

    /* 语句块 */
    ast2ir_handlers[ast_operator_type::AST_OP_BLOCK] = &IRGenerator::ir_block;
    ast2ir_handlers[ast_operator_type::AST_OP_NESTED_BLOCK] = &IRGenerator::ir_block; // 可以复用block处理逻辑

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
    ConstInt * val;

    // 新建一个整数常量Value
    val = module->newConstInt((int32_t) node->integer_val);

    node->val = val;

    return true;
}

/// @brief 浮点数字面量叶子节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_float(ast_node * node)
{
    // 实现浮点数支持
    ConstInt * val = module->newConstInt((int32_t)node->float_val); // 暂时将浮点数转换为整数处理
    node->val = val;
    return true;
}

/// @brief 变量ID叶子节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_var_id(ast_node * node)
{
    // 查找变量名对应的Value
    Value* val = module->findVarValue(node->name);
    if (!val) {
        // 变量未定义
        minic_log(LOG_ERROR, "变量未定义：%s，行号：%ld", node->name.c_str(), node->line_no);
        return false;
    }
    
    node->val = val;
    node->type = val->getType();
    return true;
}

/// @brief 处理表达式节点AST，生成相应的IR
/// @param node AST节点
bool IRGenerator::ir_visitExp(ast_node * node)
{
    // 判断当前节点是否为空
    if (!node) {
        return false;
    }

    // 如果当前节点是叶子节点，直接生成IR
    if (node->sons[0]->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        return ir_leaf_node_uint(node->sons[0]);
    }

    // 如果是一个表达式节点（不是叶子节点），递归访问它的子节点
    if (node->node_type == ast_operator_type::AST_OP_EXP) {
        // 假设这个节点是一个表达式，需要处理它的左右子树

        // 假设该节点有左右子树
        if (node->sons.size() != 2) {
            return false; // 处理错误，表达式节点应该有两个子节点
        }

        // 递归访问左子树和右子树
        ast_node * left = ir_visit_ast_node(node->sons[0]);
        ast_node * right = ir_visit_ast_node(node->sons[1]);

        if (!left || !right) {
            return false;
        }

        // 生成一个临时变量来存储加法结果
        LocalVariable * temp = static_cast<LocalVariable *>(module->newVarValue(left->type));

        // 判断right是否为叶子节点，直接使用其值；否则需要继续递归处理
        // if (right->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        //     // 如果是叶子节点，直接使用其值
        //     node->blockInsts.addInst(new MoveInstruction(currentFunc, temp, right->val));
        // } else {
        //     // 如果right是复杂的表达式，递归访问其值
        //     ir_visitExp(right); // 处理右侧子表达式，递归调用

        //     // 假设right最终将有一个计算结果，我们可以将其值用于指令
        //     node->blockInsts.addInst(new MoveInstruction(currentFunc, temp, right->val));
        // }

        // 返回处理结果
        node->val = temp; // 保存最终结果
        return true;
    }

    return false; // 未处理的情况
}

bool IRGenerator::ir_const_declare(ast_node * node)
{
    // 不需要做什么，直接从节点中获取即可。
    // 判断当前节点是否为空
    if (!node) {
        return false;
    }

    // ast_node * type_node = node->sons[0];
    // int或bool或float
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
// bool IRGenerator::ir_variable_declare(ast_node * node)
// {
//     // 共有两个孩子，第一个类型，第二个变量名

//     // TODO 这里可强化类型等检查

//     node->val = module->newVarValue(node->sons[0]->type, node->sons[1]->name);

//     return true;
// }
bool IRGenerator::ir_variable_declare(ast_node * node)
{
    if (!node) {
        return false;
    }

    // ast_node * type_node = node->sons[0];
    // int或bool或float
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
// 输入type为AST_OP_ARRAY_VAR_DEF
bool IRGenerator::ir_array_var_def_declare(ast_node * node)
{
    if (!node) {
        return false;
    }
    // 左儿子，array-index定义  AST_OP_LEAF_VAR_ID
    // ast_node * type_node = node->sons[0];

    return true;
}

/// @brief if-else语句节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_if_else_stmt(ast_node * node)
{
    Function* currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "if语句不能出现在函数外部");
        return false;
    }
    
    // 处理条件表达式
    ast_node* condNode = ir_visit_ast_node(node->sons[0]);
    if (!condNode) {
        return false;
    }
    
    // 添加条件值检查
    if (!condNode->val) {
        minic_log(LOG_ERROR, "if语句条件表达式未产生值，行号：%ld", node->line_no);
        return false;
    }
    
    // 创建then和else的标签
    LabelInstruction* thenLabel = new LabelInstruction(currentFunc);
    LabelInstruction* elseLabel = nullptr;
    LabelInstruction* endLabel = new LabelInstruction(currentFunc);
    
    // 添加条件表达式的指令
    node->blockInsts.addInst(condNode->blockInsts);
    
    // 如果有else部分
    if (node->sons.size() > 2) {
        elseLabel = new LabelInstruction(currentFunc);
        
        // 条件为真则跳转到then，否则跳转到else
        node->blockInsts.addInst(new BranchInstruction(currentFunc, condNode->val, thenLabel, elseLabel));
        
        // 添加then标签
        node->blockInsts.addInst(thenLabel);
        
        // 处理then部分
        ast_node* thenNode = ir_visit_ast_node(node->sons[1]);
        if (!thenNode) {
            return false;
        }
        
        // 添加then部分的指令
        node->blockInsts.addInst(thenNode->blockInsts);
        
        // then部分执行完跳转到结束标签
        node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabel));
        
        // 添加else标签
        node->blockInsts.addInst(elseLabel);
        
        // 处理else部分
        ast_node* elseNode = ir_visit_ast_node(node->sons[2]);
        if (!elseNode) {
            return false;
        }
        
        // 添加else部分的指令
        node->blockInsts.addInst(elseNode->blockInsts);
    } else {
        // 没有else部分，条件为真则跳转到then，否则跳转到结束
        node->blockInsts.addInst(new BranchInstruction(currentFunc, condNode->val, thenLabel, endLabel));
        
        // 添加then标签
        node->blockInsts.addInst(thenLabel);
        
        // 处理then部分
        ast_node* thenNode = ir_visit_ast_node(node->sons[1]);
        if (!thenNode) {
            return false;
        }
        
        // 添加then部分的指令
        node->blockInsts.addInst(thenNode->blockInsts);
    }
    
    // 添加结束标签
    node->blockInsts.addInst(endLabel);
    
    return true;
}

/// @brief while循环语句节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_while_stmt(ast_node * node)
{
    Function* currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "while语句不能出现在函数外部");
        return false;
    }
    
    // 创建循环相关的标签
    LabelInstruction* condLabel = new LabelInstruction(currentFunc);
    LabelInstruction* bodyLabel = new LabelInstruction(currentFunc);
    LabelInstruction* endLabel = new LabelInstruction(currentFunc);
    
    // TODO: 将循环开始和结束标签保存到上下文中，供break和continue语句使用
    
    // 先跳转到条件判断部分
    node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));
    
    // 添加条件标签
    node->blockInsts.addInst(condLabel);
    
    // 处理条件表达式
    ast_node* condNode = ir_visit_ast_node(node->sons[0]);
    if (!condNode) {
        return false;
    }
    
    // 添加条件值检查
    if (!condNode->val) {
        minic_log(LOG_ERROR, "while语句条件表达式未产生值，行号：%ld", node->line_no);
        return false;
    }
    
    // 添加条件表达式的指令
    node->blockInsts.addInst(condNode->blockInsts);
    
    // 条件为真则跳转到循环体，否则跳转到结束
    node->blockInsts.addInst(new BranchInstruction(currentFunc, condNode->val, bodyLabel, endLabel));
    
    // 添加循环体标签
    node->blockInsts.addInst(bodyLabel);
    
    // 处理循环体
    ast_node* bodyNode = ir_visit_ast_node(node->sons[1]);
    if (!bodyNode) {
        return false;
    }
    
    // 添加循环体的指令
    node->blockInsts.addInst(bodyNode->blockInsts);
    
    // 循环体执行完跳转到条件判断
    node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));
    
    // 添加结束标签
    node->blockInsts.addInst(endLabel);
    
    return true;
}

/// @brief break语句节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_break_stmt(ast_node * node)
{
    Function* currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "break语句不能出现在函数外部");
        return false;
    }
    
    // TODO: 获取当前循环的结束标签，然后跳转到该标签
    // 目前仅做个示例，实际需要从上下文中获取正确的结束标签
    LabelInstruction* endLabel = new LabelInstruction(currentFunc);
    node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabel));
    
    return true;
}

/// @brief continue语句节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_continue_stmt(ast_node * node)
{
    Function* currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "continue语句不能出现在函数外部");
        return false;
    }
    
    // TODO: 获取当前循环的条件判断标签，然后跳转到该标签
    // 目前仅做个示例，实际需要从上下文中获取正确的条件标签
    LabelInstruction* condLabel = new LabelInstruction(currentFunc);
    node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));
    
    return true;
}

/// @brief 函数调用节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_func_call(ast_node * node)
{
    Function* currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "函数调用不能出现在函数外部");
        return false;
    }
    
    // 获取函数名
    std::string funcName = node->sons[0]->name;
    
    // 查找函数定义
    Function* calledFunc = module->findFunction(funcName);
    if (!calledFunc) {
        minic_log(LOG_ERROR, "未找到函数定义：%s，行号：%ld", funcName.c_str(), node->line_no);
        return false;
    }
    
    // 处理参数列表
    if (node->sons.size() > 1) {
        ast_node* paramsNode = ir_visit_ast_node(node->sons[1]);
        if (!paramsNode) {
            return false;
        }
        
        // 添加参数指令
        node->blockInsts.addInst(paramsNode->blockInsts);
    }
    
    // 创建返回值变量（如果函数返回非void类型）
    Value* retVal = nullptr;
    if (!calledFunc->getReturnType()->isVoidType()) {
        retVal = module->newVarValue(calledFunc->getReturnType());
        node->val = retVal;
        node->type = calledFunc->getReturnType();
    } else {
        node->type = calledFunc->getReturnType();
    }
    
    // 创建函数调用指令
    node->blockInsts.addInst(new CallInstruction(currentFunc, calledFunc, retVal));
    
    return true;
}

/// @brief 函数实参节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_func_rparams(ast_node * node)
{
    Function* currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "函数实参不能出现在函数外部");
        return false;
    }
    
    // 倒序处理参数，因为参数是从左到右入栈的
    for (auto it = node->sons.begin(); it != node->sons.end(); ++it) {
        ast_node* paramNode = ir_visit_ast_node(*it);
        if (!paramNode) {
            return false;
        }
        
        // 添加参数的计算指令
        node->blockInsts.addInst(paramNode->blockInsts);
        
        // 添加ARG指令
        node->blockInsts.addInst(new ArgInstruction(currentFunc, paramNode->val));
    }
    
    return true;
}

/// @brief 数组索引节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_array_index(ast_node * node)
{
    // 处理数组变量
    ast_node* arrayNode = ir_visit_ast_node(node->sons[0]);
    if (!arrayNode) {
        return false;
    }
    
    // 处理索引表达式
    ast_node* indexNode = ir_visit_ast_node(node->sons[1]);
    if (!indexNode) {
        return false;
    }
    
    node->blockInsts.addInst(arrayNode->blockInsts);
    node->blockInsts.addInst(indexNode->blockInsts);
    
    // TODO: 计算数组元素地址并访问，具体实现取决于数组的底层表示
    
    return true;
}

/// @brief 数组访问节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_array_access(ast_node * node)
{
    // 处理数组变量
    ast_node* arrayNode = ir_visit_ast_node(node->sons[0]);
    if (!arrayNode) {
        return false;
    }
    
    node->blockInsts.addInst(arrayNode->blockInsts);
    
    // 处理所有维度的索引
    for (size_t i = 1; i < node->sons.size(); i++) {
        ast_node* indexNode = ir_visit_ast_node(node->sons[i]);
        if (!indexNode) {
            return false;
        }
        
        node->blockInsts.addInst(indexNode->blockInsts);
        
        // TODO: 计算每个维度的索引偏移量
    }
    
    // TODO: 计算数组元素地址并访问，具体实现取决于数组的底层表示
    
    return true;
}

/// @brief 赋值语句节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_assign_stmt(ast_node * node)
{
    Function* currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "赋值语句不能出现在函数外部");
        return false;
    }
    
    // 处理左值
    ast_node* lvalNode = ir_visit_ast_node(node->sons[0]);
    if (!lvalNode) {
        return false;
    }
    
    // 处理表达式
    ast_node* exprNode = ir_visit_ast_node(node->sons[1]);
    if (!exprNode) {
        return false;
    }
    
    // 添加左值的指令（如果有）
    node->blockInsts.addInst(lvalNode->blockInsts);
    
    // 添加表达式的指令
    node->blockInsts.addInst(exprNode->blockInsts);
    
    // 添加赋值指令
    node->blockInsts.addInst(new MoveInstruction(currentFunc, lvalNode->val, exprNode->val));
    
    return true;
}

/// @brief 表达式语句节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_expr_stmt(ast_node * node)
{
    if (node->sons.empty()) {
        // 空表达式语句
        return true;
    }
    
    // 处理表达式
    ast_node* exprNode = ir_visit_ast_node(node->sons[0]);
    if (!exprNode) {
        return false;
    }
    
    // 添加表达式的指令
    node->blockInsts.addInst(exprNode->blockInsts);
    
    return true;
}

/// @brief 左值节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_lval(ast_node * node)
{
    if (node->sons.size() == 1) {
        // 简单变量
        ast_node* idNode = ir_visit_ast_node(node->sons[0]);
        if (!idNode) {
            return false;
        }
        
        node->blockInsts.addInst(idNode->blockInsts);
        node->val = idNode->val;
        node->type = idNode->type;
    } else {
        // 数组元素
        return ir_array_access(node);
    }
    
    return true;
}

/// @brief 一元表达式节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_unary_exp(ast_node * node)
{
    Function* currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "表达式不能出现在函数外部");
        return false;
    }
    
    // 处理操作数
    ast_node* operandNode = ir_visit_ast_node(node->sons[1]);
    if (!operandNode) {
        return false;
    }
    
    // 添加操作数的指令
    node->blockInsts.addInst(operandNode->blockInsts);
    
    // 创建结果变量
    Value* resultVal = module->newVarValue(operandNode->type);
    node->val = resultVal;
    node->type = operandNode->type;
    
    // TODO: 根据操作符类型创建相应的指令
    // 这里需要添加处理一元运算符的指令，如取负、逻辑非等
    
    return true;
}

/// @brief 乘法表达式节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_mul_exp(ast_node * node)
{
    // TODO: 实现乘法表达式的处理逻辑
    return true;
}

/// @brief 加法表达式节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_add_exp(ast_node * node)
{
    // TODO: 实现加法表达式的处理逻辑
    return true;
}

/// @brief 关系表达式节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_rel_exp(ast_node * node)
{
    Function* currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "关系表达式不能出现在函数外部");
        return false;
    }
    
    // 如果是叶子节点，则返回它的值
    if (node->sons.size() == 1) {
        ast_node* sonNode = ir_visit_ast_node(node->sons[0]);
        if (!sonNode) {
            return false;
        }
        
        node->blockInsts.addInst(sonNode->blockInsts);
        node->val = sonNode->val;
        node->type = sonNode->type;
        return true;
    }
    
    // 处理关系表达式的左右操作数
    ast_node* leftNode = ir_visit_ast_node(node->sons[0]);
    ast_node* rightNode = ir_visit_ast_node(node->sons[2]); // 操作符在sons[1]
    
    if (!leftNode || !rightNode) {
        return false;
    }
    
    // 确保左右操作数都有有效值
    if (!leftNode->val || !rightNode->val) {
        minic_log(LOG_ERROR, "关系表达式操作数未产生有效值，行号：%ld", node->line_no);
        return false;
    }
    
    // 添加左右操作数的指令
    node->blockInsts.addInst(leftNode->blockInsts);
    node->blockInsts.addInst(rightNode->blockInsts);
    
    // 创建结果变量(布尔值用整数类型表示)
    LocalVariable* resultVal = static_cast<LocalVariable*>(module->newVarValue(IntegerType::getTypeInt())); // 结果是布尔值，用整数表示
    
    // 获取操作符
    // ast_operator_type opType = node->sons[1]->node_type;
    
    // 根据操作符类型创建相应的比较指令
    // 使用正确的IRInstOperator枚举类型
    node->blockInsts.addInst(new BinaryInstruction(
        currentFunc,
        IRInstOperator::IRINST_OP_ADD_I, // 暂时使用加法指令，实际应该根据操作符类型选择合适的操作码
        leftNode->val,
        rightNode->val,
        IntegerType::getTypeInt()
    ));
    
    node->val = resultVal;
    // 设置类型为整数类型
    node->type = IntegerType::getTypeInt();  // 布尔值用32位整数表示
    
    return true;
}

/// @brief 等价表达式节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_eq_exp(ast_node * node)
{
    // TODO: 实现等价表达式的处理逻辑
    return true;
}

/// @brief 逻辑与表达式节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_land_exp(ast_node * node)
{
    // TODO: 实现逻辑与表达式的处理逻辑
    return true;
}

/// @brief 逻辑或表达式节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_lor_exp(ast_node * node)
{
    // TODO: 实现逻辑或表达式的处理逻辑
    return true;
}

/// @brief 常量表达式节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_const_exp(ast_node * node)
{
    // 处理常量表达式，通常直接传递给子表达式处理
    if (node->sons.empty()) {
        return false;
    }
    
    ast_node* exprNode = ir_visit_ast_node(node->sons[0]);
    if (!exprNode) {
        return false;
    }
    
    node->blockInsts.addInst(exprNode->blockInsts);
    node->val = exprNode->val;
    node->type = exprNode->type;
    
    return true;
}

/// @brief 函数形式参数节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_func_formal_param(ast_node * node)
{
    // 处理函数的单个形参
    // 通常形参节点包含类型和标识符信息
    if (node->sons.size() < 2) {
        minic_log(LOG_ERROR, "函数形式参数节点格式错误，行号：%ld", node->line_no);
        return false;
    }
    
    // 获取参数类型节点
    ast_node* typeNode = ir_visit_ast_node(node->sons[0]);
    if (!typeNode) {
        return false;
    }
    
    // 获取参数标识符节点
    ast_node* idNode = ir_visit_ast_node(node->sons[1]);
    if (!idNode) {
        return false;
    }
    
    // TODO: 处理数组类型参数
    // 如果有更多的子节点，可能表示这是一个数组参数
    
    // 在当前作用域中创建形参变量
    Value* paramVar = module->newVarValue(typeNode->type, idNode->name);
    if (!paramVar) {
        minic_log(LOG_ERROR, "无法创建形参变量：%s，行号：%ld", idNode->name.c_str(), node->line_no);
        return false;
    }
    
    node->val = paramVar;
    node->type = typeNode->type;
    
    return true;
}

/// @brief 常量定义节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_const_def(ast_node * node)
{
    // 常量定义节点通常包含标识符和初始化器
    if (node->sons.size() < 2) {
        minic_log(LOG_ERROR, "常量定义节点格式错误，行号：%ld", node->line_no);
        return false;
    }
    
    // 获取标识符节点
    ast_node* idNode = ir_visit_ast_node(node->sons[0]);
    if (!idNode) {
        return false;
    }
    
    // 获取初始化表达式节点
    ast_node* initNode = ir_visit_ast_node(node->sons[1]);
    if (!initNode) {
        return false;
    }
    
    // 添加初始化表达式的指令
    node->blockInsts.addInst(initNode->blockInsts);
    
    // 创建常量变量
    Value* constVar = module->newVarValue(initNode->type, idNode->name);
    if (!constVar) {
        minic_log(LOG_ERROR, "无法创建常量变量：%s，行号：%ld", idNode->name.c_str(), node->line_no);
        return false;
    }
    
    // 当前处于函数内部时，需要添加赋值指令
    Function* currentFunc = module->getCurrentFunction();
    if (currentFunc) {
        node->blockInsts.addInst(new MoveInstruction(currentFunc, constVar, initNode->val));
    }
    
    node->val = constVar;
    node->type = initNode->type;
    
    return true;
}

/// @brief 变量定义节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_var_def(ast_node * node)
{
    // 变量定义节点通常包含标识符和可选的初始化器
    if (node->sons.empty()) {
        minic_log(LOG_ERROR, "变量定义节点格式错误，行号：%ld", node->line_no);
        return false;
    }
    
    // 获取标识符节点
    ast_node* idNode = ir_visit_ast_node(node->sons[0]);
    if (!idNode) {
        return false;
    }
    
    // 获取变量类型
    Type* varType = idNode->type;
    if (!varType) {
        minic_log(LOG_ERROR, "变量类型未知：%s，行号：%ld", idNode->name.c_str(), node->line_no);
        return false;
    }
    
    // 创建变量
    Value* var = module->newVarValue(varType, idNode->name);
    if (!var) {
        minic_log(LOG_ERROR, "无法创建变量：%s，行号：%ld", idNode->name.c_str(), node->line_no);
        return false;
    }
    
    // 如果有初始化表达式
    if (node->sons.size() > 1) {
        ast_node* initNode = ir_visit_ast_node(node->sons[1]);
        if (!initNode) {
            return false;
        }
        
        // 添加初始化表达式的指令
        node->blockInsts.addInst(initNode->blockInsts);
        
        // 当前处于函数内部时，需要添加赋值指令
        Function* currentFunc = module->getCurrentFunction();
        if (currentFunc) {
            node->blockInsts.addInst(new MoveInstruction(currentFunc, var, initNode->val));
        }
    }
    
    node->val = var;
    node->type = varType;
    
    return true;
}

/// @brief 标量常量初始化节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_scalar_const_init(ast_node * node)
{
    // 标量常量初始化节点通常包含一个表达式
    if (node->sons.empty()) {
        minic_log(LOG_ERROR, "标量常量初始化节点格式错误，行号：%ld", node->line_no);
        return false;
    }
    
    // 处理表达式
    ast_node* exprNode = ir_visit_ast_node(node->sons[0]);
    if (!exprNode) {
        return false;
    }
    
    // 添加表达式的指令
    node->blockInsts.addInst(exprNode->blockInsts);
    
    // 将表达式的值和类型传递给当前节点
    node->val = exprNode->val;
    node->type = exprNode->type;
    
    return true;
}

/// @brief 数组常量初始化节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_array_const_init(ast_node * node)
{
    // TODO: 实现数组常量初始化
    // 这需要处理多维数组的复杂初始化逻辑
    
    // 当前简单实现：遍历所有子节点并处理它们
    for (auto& child : node->sons) {
        ast_node* childNode = ir_visit_ast_node(child);
        if (!childNode) {
            return false;
        }
        
        // 添加子节点的指令
        node->blockInsts.addInst(childNode->blockInsts);
    }
    
    return true;
}

/// @brief 标量变量初始化节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_scalar_init(ast_node * node)
{
    // 标量变量初始化节点通常包含一个表达式
    if (node->sons.empty()) {
        minic_log(LOG_ERROR, "标量变量初始化节点格式错误，行号：%ld", node->line_no);
        return false;
    }
    
    // 处理表达式
    ast_node* exprNode = ir_visit_ast_node(node->sons[0]);
    if (!exprNode) {
        return false;
    }
    
    // 添加表达式的指令
    node->blockInsts.addInst(exprNode->blockInsts);
    
    // 将表达式的值和类型传递给当前节点
    node->val = exprNode->val;
    node->type = exprNode->type;
    
    return true;
}

/// @brief 数组变量初始化节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_array_init_val(ast_node * node)
{
    // TODO: 实现数组变量初始化
    // 这需要处理多维数组的复杂初始化逻辑
    
    // 当前简单实现：遍历所有子节点并处理它们
    for (auto& child : node->sons) {
        ast_node* childNode = ir_visit_ast_node(child);
        if (!childNode) {
            return false;
        }
        
        // 添加子节点的指令
        node->blockInsts.addInst(childNode->blockInsts);
    }
    
    return true;
}

/// @brief 一元运算符节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_unary_op(ast_node * node)
{
    // 一元运算符节点通常只保存运算符类型信息，不需要生成IR代码
    // 它的处理通常在一元表达式节点中完成
    
    // 这里只需保存运算符类型
    return true;
}

/// @brief 数组常量定义节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_array_const_def(ast_node * node)
{
    // 数组常量定义节点通常包含标识符、维度列表和初始化器
    if (node->sons.size() < 3) {
        minic_log(LOG_ERROR, "数组常量定义节点格式错误，行号：%ld", node->line_no);
        return false;
    }
    
    // 获取标识符节点
    ast_node* idNode = ir_visit_ast_node(node->sons[0]);
    if (!idNode) {
        return false;
    }
    
    // TODO: 处理数组维度
    // 这需要计算数组大小并创建适当的数组类型
    
    // 处理初始化器
    ast_node* initNode = ir_visit_ast_node(node->sons.back());
    if (!initNode) {
        return false;
    }
    
    // 添加初始化器的指令
    node->blockInsts.addInst(initNode->blockInsts);
    
    // TODO: 创建数组变量和初始化赋值
    // 这需要处理多维数组的复杂逻辑
    
    return true;
}