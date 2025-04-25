///
/// @file AST.h
/// @brief 抽象语法树AST管理的头文件
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
#pragma once

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "AttrType.h"
#include "IRCode.h"
#include "Value.h"
#include "VoidType.h"

///
/// @brief AST节点的类型。C++专门因为枚举类来区分C语言的结构体
///
enum class ast_operator_type : int {

    /* 以下为AST的叶子节点 */

    /// @brief 无符号整数字面量叶子节点
    AST_OP_LEAF_LITERAL_UINT,

    /// @brief  无符号整数字面量叶子节点
    AST_OP_LEAF_LITERAL_FLOAT,

    /// @brief 变量ID叶子节点
    AST_OP_LEAF_VAR_ID,

    /// @brief 复杂类型的节点
    AST_OP_LEAF_TYPE,

    /* 以下为AST的内部节点，含根节点 */

    /// @brief 文件编译单元运算符，可包含函数定义、语句块等孩子
    AST_OP_COMPILE_UNIT,

    /// @brief 函数定义运算符，函数名和返回值类型作为节点的属性，自左到右孩子：AST_OP_FUNC_FORMAL_PARAMS、AST_OP_BLOCK
    AST_OP_FUNC_DEF,

    /// @brief 形式参数列表运算符，可包含多个孩子：AST_OP_FUNC_FORMAL_PARAM
    AST_OP_FUNC_FORMAL_PARAMS,

    /// @brief 多个语句组成的块运算符，也称为复合语句
    AST_OP_BLOCK,

    /// @brief 符合语句，也就是语句块，两个名字一个运算符
    AST_OP_COMPOUNDSTMT = AST_OP_BLOCK,

    /// @brief return语句运算符
    AST_OP_RETURN,

    // 新增节点类型

    /// @brief 常量声明
    AST_OP_CONST_DECL,

    /// @brief 变量声明
    AST_OP_VAR_DECL,

    /// @brief while循环语句
    AST_OP_WHILE,

    /// @brief break语句
    AST_OP_BREAK,

    /// @brief continue语句
    AST_OP_CONTINUE,

    /// @brief 函数调用
    AST_OP_FUNC_CALL,

    /// @brief 数组索引
    AST_OP_ARRAY_INDEX,

    /// @brief 表达式定义
    AST_OP_EXP,

    // ! not sure
    /// @brief int类型
    AST_OP_INT_TYPE,

    // ! not sure
    /// @brief float类型
    AST_OP_FLOAT_TYPE,

    /// @brief 函数参数类型
    AST_OP_FUNC_FORMAL_PARAM,

    /// @brief 数组变量定义
    AST_OP_ARRAY_VAR_DEF,

    /// @brief 常量定义
    AST_OP_CONST_DEF,

    /// @brief 变量定义
    AST_OP_VAR_DEF,

    /// @brief 标量常量初始化
    AST_OP_SCALAR_CONST_INIT,

    /// @brief 数组常量初始化
    AST_OP_ARRAY_CONST_INIT,

    /// @brief 标量变量初始化
    AST_OP_SCALAR_INIT,

    /// @brief 数组变量初始化
    AST_OP_ARRAY_INIT_VAL,

    /// @brief 赋值语句
    AST_OP_ASSIGN_STMT,

    /// @brief 表达式语句
    AST_OP_EXPR_STMT,

    /// @brief 嵌套块语句
    AST_OP_NESTED_BLOCK,

    /// @brief if-else语句
    AST_OP_IF_ELSE_STMT,

    /// @brief 左值
    AST_OP_LVAL,

    /// @brief 一元表达式
    AST_OP_UNARY_EXP,

    /// @brief 一元运算符
    AST_OP_UNARY_OP,

    /// @brief 函数实参
    AST_OP_FUNC_RPARAMS,

    /// @brief 乘法表达式
    AST_OP_MUL_EXP,

    /// @brief 加法表达式
    AST_OP_ADD_EXP,

    /// @brief 关系表达式
    AST_OP_REL_EXP,

    /// @brief 等价表达式
    AST_OP_EQ_EXP,

    /// @brief 逻辑与表达式
    AST_OP_LAND_EXP,

    /// @brief 逻辑或表达式
    AST_OP_LOR_EXP,

    /// @brief 常量表达式
    AST_OP_CONST_EXP,

    /// @brief 数组constant定义
    AST_OP_ARRAY_CONST_DEF,

    /// @brief 数组访问操作
    AST_OP_ARRAY_ACCESS,

    /// @brief 最大标识符，表示非法运算符
    AST_OP_MAX,
};

///
/// @brief 抽象语法树AST的节点描述类
///
class ast_node {
public:
    /// @brief 节点类型
    ast_operator_type node_type;

    /// @brief 行号信息，主要针对叶子节点有用
    int64_t line_no;

    /// @brief 节点值的类型，可用于函数返回值类型
    Type * type;

    /// @brief 无符号整数字面量值
    uint32_t integer_val;

    /// @brief float类型字面量值
    float float_val;

    /// @brief 操作符类型
    Op op_type;

    /// @brief 变量名，或者函数名
    std::string name;

    /// @brief 是否为数组
    bool is_array = false;

    /// @brief 数组维度信息 (存储每个维度的大小)
    std::vector<int> array_dimensions;

    /// @brief 数组基础类型
    Type * array_element_type = nullptr;

    /// @brief 父节点
    ast_node * parent = nullptr;

    /// @brief 孩子节点
    std::vector<ast_node *> sons;

    /// @brief 线性IR指令块，可包含多条IR指令，用于线性IR指令产生用
    InterCode blockInsts;

    /// @brief 线性IR指令或者运行产生的Value，用于线性IR指令产生用
    Value * val = nullptr;

    ///
    /// @brief 在进入block等节点时是否要进行作用域管理。默认要做。
    ///
    bool needScope = true;

    /// @brief 创建指定节点类型的节点
    /// @param _node_type 节点类型
    ast_node(ast_operator_type _node_type, Type * _type = VoidType::getType(), int64_t _line_no = -1);

    /// @brief 构造函数
    /// @param _type 节点值的类型
    ast_node(Type * _type);

    /// @brief 针对无符号整数字面量的构造函数
    /// @param attr 无符号整数字面量
    ast_node(digit_int_attr attr);

    /// @brief 针对无符号整数字面量的构造函数
    /// @param attr 无符号整数字面量
    ast_node(digit_real_attr attr);

    /// @brief 针对标识符ID的叶子构造函数
    /// @param attr 字符型标识符
    ast_node(var_id_attr attr);

    /// @brief 针对标识符ID的叶子构造函数
    /// @param _id 标识符ID
    /// @param _line_no 行号
    ast_node(std::string id, int64_t _line_no);

    /// @brief 判断是否是叶子节点
    /// @param type 节点类型
    /// @return true：是叶子节点 false：内部节点
    bool isLeafNode();

    /// @brief 向父节点插入一个节点
    /// @param parent 父节点
    /// @param node 节点
    ast_node * insert_son_node(ast_node * node);

    /// @brief 创建指定节点类型的节点，最后一个孩子节点必须指定为nullptr。
    /// @param type 节点类型
    /// @param  可变参数，最后一个孩子节点必须指定为nullptr。如果没有孩子，则指定为nullptr
    /// @return 创建的节点
    static ast_node * New(ast_operator_type type, ...);

    /// @brief 创建无符号整数的叶子节点
    /// @param val 词法值
    /// @param line_no 行号
    static ast_node * New(digit_int_attr attr);

    /// @brief 创建浮点数的叶子节点
    /// @param attr 行号
    static ast_node * New(digit_real_attr attr);

    /// @brief 创建标识符的叶子节点
    /// @param val 词法值
    /// @param line_no 行号
    static ast_node * New(var_id_attr attr);

    /// @brief 创建标识符的叶子节点
    /// @param id 词法值
    /// @param line_no 行号
    static ast_node * New(std::string id, int64_t lineno);

    /// @brief 创建具备指定类型的节点
    /// @param type 节点值类型
    /// @param line_no 行号
    /// @return 创建的节点
    static ast_node * New(Type * type);

    ///
    /// @brief 释放节点
    /// @param node
    ///
    static void Delete(ast_node * node);
};

/// @brief AST资源清理
void free_ast(ast_node * root);

/// @brief抽象语法树的根节点指针
extern ast_node * ast_root;

/// @brief 创建AST的内部节点，请注意可追加孩子节点，请按次序依次加入，最多3个
/// @param node_type 节点类型
/// @param first_child 第一个孩子节点
/// @param second_child 第一个孩子节点
/// @param third_child 第一个孩子节点
/// @return 创建的节点
ast_node * create_contain_node(ast_operator_type node_type,
                               ast_node * first_child = nullptr,
                               ast_node * second_child = nullptr,
                               ast_node * third_child = nullptr);

/// @brief 创建函数定义类型的内部AST节点
/// @param type_node 函数返回值类型
/// @param name_node 函数名节点
/// @param block 函数体语句块
/// @param params 函数形参，可以没有参数
/// @return 创建的节点
ast_node *
create_func_def(ast_node * type_node, ast_node * name_node, ast_node * block = nullptr, ast_node * params = nullptr);

/// @brief 创建函数定义类型的内部AST节点
/// @param type 返回值类型
/// @param id 函数名字
/// @param block_node 函数体语句块节点
/// @param params_node 函数形参，可以没有参数
/// @return 创建的节点
ast_node * create_func_def(type_attr & type, var_id_attr & id, ast_node * block_node, ast_node * params_node);

/// @brief 创建函数形式参数的节点
/// @param line_no 行号
/// @param param_name 形式参数名
/// @return 创建的节点
ast_node * create_func_formal_param(uint32_t line_no, const char * param_name);

/// @brief 创建函数调用的节点
/// @param funcname_node 函数名节点
/// @param params_node 实参节点
/// @return 创建的节点
ast_node * create_func_call(ast_node * funcname_node, ast_node * params_node = nullptr);

/// @brief 创建类型节点
/// @param type 类型信息
/// @return 创建的节点
ast_node * create_type_node(type_attr & type);

///
/// @brief 类型属性转换成Type
/// @param attr 词法属性
/// @return Type* 类型
///
Type * typeAttr2Type(type_attr & attr);

///
/// @brief 根据第一个变量定义创建变量声明语句节点
/// @param first_child 第一个变量定义节点
/// @return ast_node* 变量声明语句节点
///
ast_node * create_var_decl_stmt_node(ast_node * first_child);

///
/// @brief 根据变量的类型和属性创建变量声明语句节点
/// @param type 变量的类型
/// @param id 变量的名字
/// @return ast_node* 变量声明语句节点
///
ast_node * create_var_decl_stmt_node(type_attr & type, var_id_attr & id);

///
/// @brief 向变量声明语句中追加变量声明
/// @param stmt_node 变量声明语句
/// @param id 变量的名字
/// @return ast_node* 变量声明语句节点
///
ast_node * add_var_decl_node(ast_node * stmt_node, var_id_attr & id);

///
/// @brief 创建常量声明节点
/// @param type 常量类型
/// @param id 常量名
/// @param init_val 初始值
/// @return ast_node* 常量声明节点
///
ast_node * create_const_decl_node(type_attr & type, var_id_attr & id, ast_node * init_val);

///
/// @brief 创建if语句节点
/// @param condition 条件表达式
/// @param then_stmt then语句
/// @return ast_node* if语句节点
///
ast_node * create_if_stmt_node(ast_node * condition, ast_node * then_stmt);

///
/// @brief 创建if-else语句节点
/// @param condition 条件表达式
/// @param then_stmt then语句
/// @param else_stmt else语句
/// @return ast_node* if-else语句节点
///
ast_node * create_if_else_stmt_node(ast_node * condition, ast_node * then_stmt, ast_node * else_stmt);

///
/// @brief 创建while循环语句节点
/// @param condition 条件表达式
/// @param body 循环体
/// @return ast_node* while循环语句节点
///
ast_node * create_while_stmt_node(ast_node * condition, ast_node * body);

///
/// @brief 创建break语句节点
/// @param line_no 行号
/// @return ast_node* break语句节点
///
ast_node * create_break_stmt_node(int64_t line_no);

///
/// @brief 创建普通参数节点
/// @param type_node 节点类型
/// @param id_node 标识符节点类型
ast_node * create_func_btype_node(ast_node * type_node, ast_node * id_node);

///
/// @brief 创建continue语句节点
/// @param line_no 行号
/// @return ast_node* continue语句节点
///
ast_node * create_continue_stmt_node(int64_t line_no);

///
/// @brief 创建赋值语句节点
/// @param lval 左值
/// @param expr 表达式
/// @return ast_node* 赋值语句节点
///
ast_node * create_assign_stmt_node(ast_node * lval, ast_node * expr);

/// @brief 创建return语句节点
/// @param expr 表达式
/// @param line_no 行号
/// @return ast_node* return语句节点
/// @details 如果expr为nullptr，则表示return语句没有返回值
ast_node * create_return_stmt_node(ast_node * expr, int64_t line_no);

///
/// @brief 创建浮点数字面量节点
/// @param attr 浮点数属性
/// @return ast_node* 浮点数字面量节点
///
ast_node * create_float_literal_node(digit_real_attr & attr);

///
/// @brief 创建实际参数列表节点
/// @return ast_node* 实际参数列表节点
///
ast_node * create_func_real_params_node();

///
/// @brief 向实际参数列表添加参数
/// @param params_node 实际参数列表节点
/// @param param 参数
/// @return ast_node* 更新后的实际参数列表节点
///
ast_node * add_real_param_node(ast_node * params_node, ast_node * param);

///
/// @brief 创建数组索引表达式节点
/// @param array 数组标识符
/// @param index 索引表达式
/// @return ast_node* 数组索引表达式节点
///
ast_node * create_array_index_node(ast_node * array, ast_node * index);

///
/// @brief 创建数组初始化节点
/// @return ast_node* 数组初始化节点
///
ast_node * create_array_init_node();

///
/// @brief 向数组初始化节点添加元素
/// @param init_node 数组初始化节点
/// @param element 元素
/// @return ast_node* 更新后的数组初始化节点
///
ast_node * add_array_init_element(ast_node * init_node, ast_node * element);

/// @brief 创建常量声明节点
/// @param type_node 类型节点
/// @param def_list 定义列表
/// @return ast_node* 常量声明节点
ast_node * create_const_decl_node(ast_node * type_node, ast_node * def_list);

/// @brief 创建变量声明节点
/// @param type_node 类型节点
/// @param def_list 定义列表
/// @return ast_node* 变量声明节点
ast_node * create_var_decl_node(ast_node * type_node, ast_node * def_list);

/// @brief 创建常量定义节点
/// @param id_node 标识符节点
/// @param init_node 初始化节点
/// @return ast_node* 常量定义节点
ast_node * create_const_def_node(ast_node * id_node, ast_node * init_node);

/// @brief 创建变量定义节点
/// @param id_node 标识符节点
/// @param init_node 初始化节点
/// @return ast_node* 变量定义节点
ast_node * create_var_def_node(ast_node * id_node, ast_node * init_node);

/// @brief 创建标量常量初始化节点
/// @param expr_node 表达式节点
/// @return ast_node* 标量常量初始化节点
ast_node * create_scalar_const_init_node(ast_node * expr_node);

/// @brief 创建数组常量初始化节点
/// @param elements 元素列表
/// @return ast_node* 数组常量初始化节点
ast_node * create_array_const_init_node(std::vector<ast_node *> & elements);

/// @brief 创建标量变量初始化节点
/// @param expr_node 表达式节点
/// @return ast_node* 标量变量初始化节点
ast_node * create_scalar_init_node(ast_node * expr_node);

/// @brief 创建数组变量初始化节点
/// @param elements 元素列表
/// @return ast_node* 数组变量初始化节点
ast_node * create_array_init_val_node(std::vector<ast_node *> & elements);

/// @brief 创建赋值语句节点
/// @param lval 左值节点
/// @param expr 表达式节点
/// @return ast_node* 赋值语句节点
ast_node * create_assign_stmt_node(ast_node * lval, ast_node * expr);

/// @brief 创建表达式语句节点
/// @param expr 表达式节点
/// @return ast_node* 表达式语句节点
ast_node * create_expr_stmt_node(ast_node * expr);

/// @brief 创建嵌套块语句节点
/// @param block 块节点
/// @return ast_node* 嵌套块语句节点
ast_node * create_nested_block_node(ast_node * block);

/// @brief 创建if-else语句节点
/// @param cond 条件节点
/// @param then_stmt then语句节点
/// @param else_stmt else语句节点
/// @return ast_node* if-else语句节点
ast_node * create_if_else_stmt_node(ast_node * cond, ast_node * then_stmt, ast_node * else_stmt);

/// @brief 创建while循环语句节点
/// @param cond 条件节点
/// @param body 循环体节点
/// @return ast_node* while循环语句节点
ast_node * create_while_loop_node(ast_node * cond, ast_node * body);

/// @brief 创建break语句节点
/// @param line_no 行号
/// @return ast_node* break语句节点
ast_node * create_break_stmt_node(int64_t line_no);

/// @brief 创建continue语句节点
/// @param line_no 行号
/// @return ast_node* continue语句节点
ast_node * create_continue_stmt_node(int64_t line_no);

///
/// @brief 创建条件表达式节点
/// @param expr 表达式节点
/// @return ast_node* 条件表达式节点
ast_node * create_cond_node(ast_node * expr);

/// @brief 创建左值节点
/// @param id_node 标识符节点
/// @param indices 索引列表
/// @return ast_node* 左值节点
ast_node * create_lval_node(ast_node * id_node, std::vector<ast_node *> & indices);

/// @brief 创建数组访问节点
/// @param id_node 数组标识符节点
/// @param indices 索引列表
/// @return ast_node* 数组访问节点
ast_node * create_array_access_node(ast_node * id_node, std::vector<ast_node *> & indices);

/// @brief 创建主表达式节点
/// @param value 值节点
/// @return ast_node* 主表达式节点
ast_node * create_primary_node(ast_node * value);

/// @brief 创建整数节点
/// @param value 数字值
/// @return ast_node* 数字节点
ast_node * create_number_node(int value);

/// @brief 创建浮点数节点
/// @param value 数字值
/// @return ast_node* 数字节点
ast_node * create_float_node(float value);

/// @brief 创建一元表达式节点
/// @param op 运算符节点
/// @param operand 操作数节点
/// @return ast_node* 一元表达式节点
ast_node * create_unary_exp_node(ast_node * op, ast_node * operand);

/// @brief 创建一元运算符节点
/// @param op_type 运算符类型
/// @return ast_node* 一元运算符节点
ast_node * create_unary_op_node(Op op_type);

/// @brief 创建函数实参节点
/// @param params 参数列表
/// @return ast_node* 函数实参节点
ast_node * create_func_rparams_node(std::vector<ast_node *> & params);

/// @brief 创建乘法表达式节点
/// @param left 左操作数节点
/// @param right 右操作数节点
/// @param op_type 运算符类型
/// @return ast_node* 乘法表达式节点
ast_node * create_mul_exp_node(ast_node * left, ast_node * right, Op op_type);

/// @brief 创建加法表达式节点
/// @param left 左操作数节点
/// @param right 右操作数节点
/// @param op_type 运算符类型
/// @return ast_node* 加法表达式节点
ast_node * create_add_exp_node(ast_node * left, ast_node * right, Op op_type);

/// @brief 创建关系表达式节点
/// @param left 左操作数节点
/// @param right 右操作数节点
/// @param op_type 运算符类型
/// @return ast_node* 关系表达式节点
ast_node * create_rel_exp_node(ast_node * left, ast_node * right, Op op_type);

/// @brief 创建等价表达式节点
/// @param left 左操作数节点
/// @param right 右操作数节点
/// @param op_type 运算符类型
/// @return ast_node* 等价表达式节点
ast_node * create_eq_exp_node(ast_node * left, ast_node * right, Op op_type);

/// @brief 创建逻辑与表达式节点
/// @param left 左操作数节点
/// @param right 右操作数节点
/// @return ast_node* 逻辑与表达式节点
ast_node * create_land_exp_node(ast_node * left, ast_node * right);

/// @brief 创建逻辑或表达式节点
/// @param left 左操作数节点
/// @param right 右操作数节点
/// @return ast_node* 逻辑或表达式节点
ast_node * create_lor_exp_node(ast_node * left, ast_node * right);

ast_node * create_const_exp_node(
    ast_node * expr); /// @return ast_node* 常量表达式节点/// @param expr 表达式节点/// @brief
                      /// 创建常量表达式节点ast_node * create_lor_exp_node(ast_node * left, ast_node * right);

/// @brief 创建数组常量定义节点
/// @param id_node 标识符节点
/// @param dimensions 数组维度列表
/// @param init_node 初始化节点
/// @return ast_node* 数组常量定义节点
ast_node * create_array_const_def_node(ast_node * id_node, std::vector<ast_node *> & dimensions, ast_node * init_node);

/// @brief 创建数组变量定义节点
/// @param id_node 标识符节点
/// @param dimensions 数组维度列表
/// @param init_node 初始化节点
/// @return ast_node* 数组变量定义节点
ast_node * create_array_var_def_node(ast_node * id_node, std::vector<ast_node *> & dimensions, ast_node * init_node);

/// @brief 创建函数形式参数节点
/// @param type_node 类型节点
/// @param id_node 标识符节点
/// @param is_array 是否为数组类型
/// @param dimensions 数组维度列表
/// @return ast_node* 函数形式参数节点
ast_node * create_func_fparam_node(ast_node * type_node,
                                   ast_node * id_node,
                                   bool is_array = false,
                                   std::vector<ast_node *> dimensions = {});

ast_node * create_exp_node(ast_node * expr);
