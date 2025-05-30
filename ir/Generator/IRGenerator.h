﻿///
/// @file IRGenerator.h
/// @brief AST遍历产生线性IR的头文件
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
#pragma once

#include <unordered_map>

#include "AST.h"
#include "Module.h"

/// @brief AST遍历产生线性IR类
class IRGenerator {

public:
    /// @brief 构造函数
    /// @param root
    /// @param _module
    IRGenerator(ast_node * root, Module * _module);

    /// @brief 析构函数
    ~IRGenerator() = default;

    /// @brief 运行产生IR
    bool run();

protected:
    /// @brief 编译单元AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_compile_unit(ast_node * node);

    /// @brief 函数定义AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_function_define(ast_node * node);

    /// @brief 形式参数AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_function_formal_params(ast_node * node);

    /// @brief 语句块（含函数体）AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_block(ast_node * node);
    // @brief 语句块（含函数体）AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_nested_block(ast_node * node);
    /// @brief 语句块（含函数体）AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_if_else(ast_node * node);
    /// @brief 语句块（含函数体）AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_while(ast_node * node);
    /// @brief return节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_return(ast_node * node);

    /// @brief 类型叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_leaf_node_type(ast_node * node);

    /// @brief 无符号整数字面量叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_leaf_node_uint(ast_node * node);
    /// @brief 未知节点类型的节点处理
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_default(ast_node * node);

    /// @brief 根据AST的节点运算符查找对应的翻译函数并执行翻译动作
    /// @param node AST节点
    /// @return 成功返回node节点，否则返回nullptr
    ast_node * ir_visit_ast_node(ast_node * node);

    /// @brief AST的节点操作函数
    typedef bool (IRGenerator::*ast2ir_handler_t)(ast_node *);
    bool ir_array_exp_lval(ast_node * node);
    bool ir_visitExp(ast_node * node);
    bool ir_visitUNARYExp(ast_node * node);
    bool ir_visitUNARYOP(ast_node * node);

    bool ir_visitConfExp(ast_node * node);
    bool ir_visitLogitExp(ast_node * node);
    bool ir_const_declare(ast_node * node);
    bool ir_declare_statment(ast_node * node);
    bool ir_variable_declare(ast_node * node);
    bool ir_array_var_def_declare(ast_node * node);
    bool ir_var_def(ast_node * node);
    int ir_const_exp(ast_node * node);
    bool ir_leaf_value_uint(ast_node * node);
    bool ir_scalar_init(ast_node * node);
    bool ir_assign(ast_node * node);
    bool ir_leaf_node_var_id(ast_node * node);
    bool ir_add(ast_node * node);
    bool ir_sub(ast_node * node);
    bool ir_mul(ast_node * node);
    bool ir_div(ast_node * node);
    bool ir_array_init(ast_node * node);
    bool ir_array_acess(ast_node * node);
    ast_node * ir_array_aslval_assign(ast_node * node);
    // 新增：函数调用
    bool ir_func_call(ast_node * node);

    // const常量的定义
    bool ir_const_def(ast_node * node);

    ast_node * ir_global(ast_node * node);
    bool ir_global_variable_declare(ast_node * node);
    bool ir_global_var_def(ast_node * node);
    bool ir_global_scalar_init(ast_node * node);
    bool ir_global_array_var_def_declare(ast_node * node);
    bool ir_global_const_declare(ast_node * node);
    bool ir_global_const_def(ast_node * node);
    bool ir_break(ast_node * node);
    bool ir_continue(ast_node * node);
    struct InitElement {
        ast_node * node;
        int linear_index;
    };
    bool ir_const_array_var_def_declare(ast_node * node);
    // 新增数组初始化展平操作
    //  void flatten_array_init(ast_node * node, std::vector<ast_node *> & flat_init_list);
    //  void flatten_array_init(ast_node * node, std::vector<ast_node *> & flat_list, int & curr_index, int
    //  total_size);
    void flatten_array_init(std::string name,
                            ast_node * node,
                            std::vector<InitElement> & flat_init_list,
                            std::vector<int> & index_counters,
                            std::vector<int> & dimensions,
                            int & now_rank,
                            int & large_rank,
                            int & level);
    bool isReturnInIfElse(ast_node * node);
    /// @brief AST节点运算符与动作函数关联的映射表
    std::unordered_map<ast_operator_type, ast2ir_handler_t> ast2ir_handlers;
    bool ir_global_const_array_def(ast_node * node);

private:
    /// @brief 抽象语法树的根
    ast_node * root;

    /// @brief 符号表:模块
    Module * module;
};
