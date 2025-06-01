/// @file AST.cpp
/// @brief 抽象语法树AST管理的实现
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
#include <cstdarg>
#include <cstdint>
#include <string>
#include <vector>
#include <cstring>

#include "AST.h"
#include "AttrType.h"
#include "Types/IntegerType.h"
#include "Types/VoidType.h"
#include "Types/FloatType.h"

/* 整个AST的根节点 */
ast_node * ast_root = nullptr;

/// @brief 创建指定节点类型的节点
/// @param _node_type 节点类型
/// @param _line_no 行号
ast_node::ast_node(ast_operator_type _node_type, Type * _type, int64_t _line_no)
    : node_type(_node_type), line_no(_line_no), type(_type)
{}

/// @brief 构造函数
/// @param _type 节点值的类型
/// @param line_no 行号
ast_node::ast_node(Type * _type) : ast_node(ast_operator_type::AST_OP_LEAF_TYPE, _type, -1)
{}

/// @brief 针对无符号整数字面量的构造函数
/// @param attr 无符号整数字面量
ast_node::ast_node(digit_int_attr attr)
    : ast_node(ast_operator_type::AST_OP_LEAF_LITERAL_UINT, IntegerType::getTypeInt(), attr.lineno)
{
    integer_val = attr.val;
}

// TODO 加入浮点数支持

/// @brief 针对浮点数字面量的构造函数
/// @param attr 浮点数字面量
ast_node::ast_node(digit_real_attr attr)
    : ast_node(ast_operator_type::AST_OP_LEAF_LITERAL_UINT, FloatType::getTypeFloat(), attr.lineno)
{
    float_val = attr.val;
    // line_no = attr.lineno;
}

/// @brief 针对标识符ID的叶子构造函数
/// @param attr 字符型字面量
ast_node::ast_node(var_id_attr attr) : ast_node(ast_operator_type::AST_OP_LEAF_VAR_ID, VoidType::getType(), attr.lineno)
{
    name = attr.id;
}

/// @brief 针对标识符ID的叶子构造函数
/// @param _id 标识符ID
/// @param _line_no 行号
ast_node::ast_node(std::string _id, int64_t _line_no)
    : ast_node(ast_operator_type::AST_OP_LEAF_VAR_ID, VoidType::getType(), _line_no)
{
    name = _id;
}

/// @brief 判断是否是叶子节点
/// @return true：是叶子节点 false：内部节点
bool ast_node::isLeafNode()
{
    bool is_leaf;

    switch (this->node_type) {
        case ast_operator_type::AST_OP_LEAF_LITERAL_UINT:
        case ast_operator_type::AST_OP_LEAF_LITERAL_FLOAT:
        case ast_operator_type::AST_OP_LEAF_VAR_ID:
        case ast_operator_type::AST_OP_LEAF_TYPE:
            is_leaf = true;
            break;
        default:
            is_leaf = false;
            break;
    }

    return is_leaf;
}

/// @brief 创建指定节点类型的节点，请注意在指定有效的孩子后必须追加一个空指针nullptr，表明可变参数结束
/// @param type 节点类型
/// @param son_num 孩子节点的个数
/// @param ...
/// 可变参数，可支持插入若干个孩子节点，自左往右的次序，最后一个孩子节点必须指定为nullptr。如果没有孩子，则指定为nullptr
/// @return 创建的节点
ast_node * ast_node::New(ast_operator_type type, ...)
{
    ast_node * parent_node = new ast_node(type);

    va_list valist;

    /* valist指向传入的第一个可选参数 */
    va_start(valist, type);

    for (;;) {

        // 获取节点对象。如果最后一个对象为空指针，则说明结束
        ast_node * node = va_arg(valist, ast_node *);
        if (nullptr == node) {
            break;
        }

        // 插入到父节点中
        parent_node->insert_son_node(node);
    }

    /* 清理为 valist 保留的内存 */
    va_end(valist);

    return parent_node;
}

/// @brief 向父节点插入一个节点
/// @param parent 父节点
/// @param node 节点
ast_node * ast_node::insert_son_node(ast_node * node)
{
    if (node) {

        // 孩子节点有效时加入，主要为了避免空语句等时会返回空指针
        node->parent = this;
        this->sons.push_back(node);
    }

    return this;
}

/// @brief 创建无符号整数的叶子节点
/// @param attr 无符号整数字面量
ast_node * ast_node::New(digit_int_attr attr)
{
    ast_node * node = new ast_node(attr);

    return node;
}

/// @brief 创建浮点数的叶子节点
/// @param attr 无符号浮点数字面量
ast_node * ast_node::New(digit_real_attr attr)
{
    ast_node * node = new ast_node(attr);

    return node;
}

/// @brief 创建标识符的叶子节点
/// @param attr 字符型字面量
ast_node * ast_node::New(var_id_attr attr)
{
    ast_node * node = new ast_node(attr);

    return node;
}

/// @brief 创建标识符的叶子节点
/// @param id 词法值
/// @param line_no 行号
ast_node * ast_node::New(std::string id, int64_t lineno)
{
    ast_node * node = new ast_node(id, lineno);

    return node;
}

/// @brief 创建具备指定类型的节点
/// @param type 节点值类型
/// @param line_no 行号
/// @return 创建的节点
ast_node * ast_node::New(Type * type)
{
    ast_node * node = new ast_node(type);

    return node;
}

/// @brief 递归清理抽象语法树
/// @param node AST的节点
void ast_node::Delete(ast_node * node)
{
    if (node) {

        for (auto child: node->sons) {
            ast_node::Delete(child);
        }

        // 这里没有必要清理孩子，由于下面就要删除该节点
        // node->sons.clear();
    }

    // 清理node资源
    delete node;
}

///
/// @brief AST资源清理
///
void free_ast(ast_node * root)
{
    ast_node::Delete(root);
}

/// @brief 创建函数定义类型的内部AST节点
/// @param type_node 类型节点
/// @param name_node 函数名字节点
/// @param block_node 函数体语句块节点
/// @param params_node 函数形参，可以没有参数
/// @return 创建的节点
ast_node * create_func_def(ast_node * type_node, ast_node * name_node, ast_node * block_node, ast_node * params_node)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_FUNC_DEF, type_node->type, name_node->line_no);

    // 设置函数名
    node->name = name_node->name;

    // 如果没有参数，则创建参数节点
    if (!params_node) {
        params_node = new ast_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS);
    }

    // 如果没有函数体，则创建函数体，也就是语句块
    if (!block_node) {
        block_node = new ast_node(ast_operator_type::AST_OP_BLOCK);
    }

    (void) node->insert_son_node(type_node);
    (void) node->insert_son_node(name_node);
    (void) node->insert_son_node(params_node);
    (void) node->insert_son_node(block_node);

    return node;
}

/// @brief 创建函数定义类型的内部AST节点
/// @param type 返回值类型
/// @param id 函数名字
/// @param block_node 函数体语句块节点
/// @param params_node 函数形参，可以没有参数
/// @return 创建的节点
ast_node * create_func_def(type_attr & type, var_id_attr & id, ast_node * block_node, ast_node * params_node)
{
    // 创建整型类型节点的终结符节点
    ast_node * type_node = create_type_node(type);

    // 创建标识符终结符节点
    ast_node * id_node = ast_node::New(id.id, id.lineno);

    // 对于字符型字面量的字符串空间需要释放，因词法用到了strdup进行了字符串复制
    free(id.id);
    id.id = nullptr;

    return create_func_def(type_node, id_node, block_node, params_node);
}

/// @brief 创建AST的内部节点
/// @param node_type 节点类型
/// @param first_child 第一个孩子节点
/// @param second_child 第一个孩子节点
/// @param third_child 第一个孩子节点
/// @return 创建的节点
ast_node * create_contain_node(ast_operator_type node_type,
                               ast_node * first_child,
                               ast_node * second_child,
                               ast_node * third_child)
{
    ast_node * node = new ast_node(node_type);

    if (first_child) {
        (void) node->insert_son_node(first_child);
    }

    if (second_child) {
        (void) node->insert_son_node(second_child);
    }

    if (third_child) {
        (void) node->insert_son_node(third_child);
    }

    return node;
}

Type * typeAttr2Type(type_attr & attr)
{
    if (attr.type == BasicType::TYPE_INT) {
        return IntegerType::getTypeInt();
    } else if (attr.type == BasicType::TYPE_FLOAT) {
        return FloatType::getTypeFloat(); 
    } else {
        return VoidType::getType();
    }
}

/// @brief 创建类型节点
/// @param type 类型信息
/// @return 创建的节点
ast_node * create_type_node(type_attr & attr)
{
    Type * type = typeAttr2Type(attr);

    ast_node * type_node = ast_node::New(type);

    return type_node;
}

ast_node * create_func_call(ast_node * funcname_node, ast_node * params_node)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_FUNC_CALL);
    node->insert_son_node(funcname_node);
    if (params_node)
        node->insert_son_node(params_node);
    return node;
}

ast_node * create_if_else_stmt_node(ast_node * condition, ast_node * then_stmt, ast_node * else_stmt)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_IF_ELSE_STMT);
    node->insert_son_node(condition);
    node->insert_son_node(then_stmt);
    if (else_stmt)
        node->insert_son_node(else_stmt);
    return node;
}

ast_node * create_break_stmt_node(int64_t line_no)
{
    return new ast_node(ast_operator_type::AST_OP_BREAK, nullptr, line_no);
}

ast_node * create_continue_stmt_node(int64_t line_no)
{
    return new ast_node(ast_operator_type::AST_OP_CONTINUE, nullptr, line_no);
}

ast_node * create_assign_stmt_node(ast_node * lval, ast_node * expr)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_ASSIGN_STMT);
    node->insert_son_node(lval);
    node->insert_son_node(expr);
    return node;
}

ast_node * create_return_stmt_node(ast_node * expr, int64_t line_no)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_RETURN, nullptr, line_no);
    if (expr)
        node->insert_son_node(expr);
    return node;
}

ast_node * create_float_literal_node(digit_real_attr & attr)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_LEAF_LITERAL_FLOAT, nullptr, attr.lineno);
    node->float_val = attr.val;
    return node;
}

ast_node * create_const_def_node(ast_node * id_node, ast_node * init_node)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_CONST_DEF);
    node->insert_son_node(id_node);
    node->insert_son_node(init_node);
    return node;
}

ast_node * create_var_def_node(ast_node * id_node, ast_node * init_node)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_VAR_DEF);
    node->insert_son_node(id_node);
    node->insert_son_node(init_node);
    return node;
}

ast_node * create_scalar_const_init_node(ast_node * expr_node)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_SCALAR_CONST_INIT);
    node->insert_son_node(expr_node);
    return node;
}

ast_node * create_array_const_init_node(std::vector<ast_node *> & elements)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_ARRAY_CONST_INIT);
    for (auto elem: elements)
        node->insert_son_node(elem);
    return node;
}

ast_node * create_scalar_init_node(ast_node * expr_node)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_SCALAR_INIT);
    node->insert_son_node(expr_node);
    return node;
}

ast_node * create_array_init_val_node(std::vector<ast_node *> & elements)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_ARRAY_INIT_VAL);
    for (auto elem: elements)
        node->insert_son_node(elem);
    return node;
}

ast_node * create_array_const_def_node(ast_node * id_node, std::vector<ast_node *> & dimensions, ast_node * init_node)
{
    // 创建一个数组常量定义节点
    ast_node * node = new ast_node(ast_operator_type::AST_OP_ARRAY_CONST_DEF);

    // 添加标识符节点作为第一个子节点
    node->insert_son_node(id_node);

    // 设置节点自身的数组属性
    node->is_array = true;
    node->array_element_type = id_node->type; // 使用标识符节点的类型作为元素类型

    // 创建一个数组类型节点来存储维度信息
    ast_node * dims_node = new ast_node(ast_operator_type::AST_OP_ARRAY_INDEX);

    // 混合方法：既在节点属性中存储，也在子节点中保留原始表达式
    for (auto dim: dimensions) {
        // 将维度表达式添加到维度节点
        dims_node->insert_son_node(dim);

        // 如果维度是常量表达式，则直接存储其值
        if (dim && dim->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
            node->array_dimensions.push_back(dim->integer_val);
        } else {
            // 对于非常量表达式，存储-1表示需要运行时计算
            node->array_dimensions.push_back(-1);
        }
    }

    // 将维度节点作为第二个子节点
    node->insert_son_node(dims_node);

    // 如果有初始化节点，则作为第三个子节点
    if (init_node) {
        node->insert_son_node(init_node);
    }

    return node;
}

ast_node * create_array_var_def_node(ast_node * id_node, std::vector<ast_node *> & dimensions, ast_node * init_node)
{
    // 创建一个数组变量定义节点
    ast_node * node = new ast_node(ast_operator_type::AST_OP_ARRAY_VAR_DEF);

    // 添加标识符节点作为第一个子节点
    node->insert_son_node(id_node);

    // 设置节点自身的数组属性
    node->is_array = true;
    node->array_element_type = id_node->type; // 使用标识符节点的类型作为元素类型

    // 创建一个数组类型节点来存储维度信息
    ast_node * dims_node = new ast_node(ast_operator_type::AST_OP_ARRAY_INDEX);

    // 混合方法：既在节点属性中存储，也在子节点中保留原始表达式
    for (auto dim: dimensions) {
        // 将维度表达式添加到维度节点
        dims_node->insert_son_node(dim);

        // 如果维度是常量表达式，则直接存储其值
        if (dim && (dim->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT || dim->node_type == ast_operator_type::AST_OP_CONST_EXP)) {
            node->array_dimensions.push_back(dim->integer_val);
        } else {
            // 对于非常量表达式，存储-1表示需要运行时计算
            node->array_dimensions.push_back(-1);
        }
    }

    // 将维度节点作为第二个子节点
    node->insert_son_node(dims_node);

    // 如果有初始化节点，则作为第三个子节点
    if (init_node) {
        node->insert_son_node(init_node);
    }

    return node;
}

ast_node * create_expr_stmt_node(ast_node * expr)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_EXPR_STMT);
    node->insert_son_node(expr);
    return node;
}

ast_node * create_nested_block_node(ast_node * block)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_NESTED_BLOCK);
    node->insert_son_node(block);
    return node;
}

ast_node * create_while_loop_node(ast_node * cond, ast_node * body)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_WHILE);
    node->insert_son_node(cond);
    node->insert_son_node(body);
    return node;
}

// 为了保持一致性，修改lval节点，支持数组访问
ast_node * create_lval_node(ast_node * id_node, std::vector<ast_node *> & indices)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_LVAL);

    // 添加标识符节点
    node->insert_son_node(id_node);

    // 如果有索引，说明是数组访问
    if (!indices.empty()) {
        node->is_array = true;
        node->name = id_node->name;
        node->array_element_type = id_node->type;

        // 处理索引
        for (auto idx: indices) {
            node->insert_son_node(idx);

            // 如果索引是常量，存储其值以便优化
            if (idx && idx->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
                node->array_dimensions.push_back(idx->integer_val);
            } else {
                // 非常量索引，标记为运行时计算
                node->array_dimensions.push_back(-1);
            }
        }
    } else {
        // 不是数组访问，只是普通变量
        node->name = id_node->name;
    }

    return node;
}

ast_node * create_number_node(int value)
{
    digit_int_attr attr;
    attr.val = value;
    attr.lineno = -1;
    return ast_node::New(attr);
}

ast_node * create_float_node(float value)
{
    digit_real_attr attr;
    attr.val = value;
    attr.lineno = -1;
    return ast_node::New(attr);
}

ast_node * create_unary_exp_node(ast_node * op, ast_node * operand)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_UNARY_EXP);
    node->insert_son_node(op);
    node->insert_son_node(operand);
    return node;
}

ast_node * create_unary_op_node(Op op_type)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_UNARY_OP);
    node->op_type = op_type;
    return node;
}

ast_node * create_func_rparams_node(std::vector<ast_node *> & params)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_FUNC_RPARAMS);
    for (auto p: params)
        node->insert_son_node(p);
    return node;
}

ast_node * create_mul_exp_node(ast_node * left, ast_node * right, Op op_type)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_MUL_EXP);
    node->insert_son_node(left);
    node->insert_son_node(right);
    node->op_type = op_type;
    return node;
}

ast_node * create_add_exp_node(ast_node * left, ast_node * right, Op op_type)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_ADD_EXP);
    node->insert_son_node(left);
    node->insert_son_node(right);
    node->op_type = op_type;
    return node;
}

ast_node * create_rel_exp_node(ast_node * left, ast_node * right, Op op_type)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_REL_EXP);
    node->insert_son_node(left);
    node->insert_son_node(right);
    node->op_type = op_type;
    return node;
}

ast_node * create_eq_exp_node(ast_node * left, ast_node * right, Op op_type)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_EQ_EXP);
    node->insert_son_node(left);
    node->insert_son_node(right);
    node->op_type = op_type;
    return node;
}

ast_node * create_land_exp_node(ast_node * left, ast_node * right)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_LAND_EXP);
    node->insert_son_node(left);
    node->insert_son_node(right);
    return node;
}

ast_node * create_lor_exp_node(ast_node * left, ast_node * right)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_LOR_EXP);
    node->insert_son_node(left);
    node->insert_son_node(right);
    return node;
}

ast_node * create_exp_node(ast_node * expr)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_EXP);

    // 继承表达式的类型和行号
    node->type = expr->type;
    node->line_no = expr->line_no;

    // 如果表达式是字面量，可以直接保存它的值
    if (expr->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        node->integer_val = expr->integer_val;
    } else if (expr->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_FLOAT) {
        node->float_val = expr->float_val;
    }

    // 一定要添加原始表达式作为子节点！这步可能在当前实现中缺失了
    node->insert_son_node(expr);

    return node;
}

ast_node * create_const_exp_node(ast_node * expr)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_CONST_EXP);

    // 继承表达式的类型和行号
    node->type = expr->type;
    node->line_no = expr->line_no;

    // 如果表达式是字面量，可以直接保存它的值
    if (expr->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        node->integer_val = expr->integer_val;
    } else if (expr->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_FLOAT) {
        node->float_val = expr->float_val;
    }

    // 一定要添加原始表达式作为子节点！这步可能在当前实现中缺失了
    node->insert_son_node(expr);

    return node;
}

// 数组访问节点也应该使用混合方法
ast_node * create_array_access_node(ast_node * id_node, std::vector<ast_node *> & indices)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_ARRAY_ACCESS);

    // 设置数组访问的基本信息
    node->is_array = true;
    node->name = id_node->name;
    node->type = id_node->type; // 这里会在语义分析阶段更新为元素类型

    // 添加标识符节点
    node->insert_son_node(id_node);

    // 处理索引表达式
    for (auto idx: indices) {
        node->insert_son_node(idx);

        // 如果索引是常量，存储其值以便优化
        if (idx && idx->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
            node->array_dimensions.push_back(idx->integer_val);
        } else {
            // 非常量索引，标记为运行时计算
            node->array_dimensions.push_back(-1);
        }
    }

    return node;
}

ast_node *
create_func_fparam_node(ast_node * type_node, ast_node * id_node, bool is_array, std::vector<ast_node *> dimensions)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAM);

    node->type = type_node->type;
    node->name = id_node->name;
    node->line_no = id_node->line_no;

    // 添加类型和标识符作为子节点
    node->insert_son_node(type_node);
    node->insert_son_node(id_node);

    // 设置数组相关属性
    if (is_array) {
        node->is_array = true;
        node->array_element_type = node->type;

        // 创建一个专门的数组维度节点
        ast_node * dims_node = new ast_node(ast_operator_type::AST_OP_ARRAY_INDEX);

        // 如果是函数参数的数组形式，必须在 AST 中明确标记第一维为空
        // 函数参数的第一维总是空的 int a[]
        if (dimensions.empty() || dimensions[0] == nullptr) {
            // 创建一个表示空维度的节点（使用特殊值如 -1 表示）
            ast_node * empty_dim = new ast_node(ast_operator_type::AST_OP_LEAF_LITERAL_UINT);
            empty_dim->integer_val = -1; // -1 表示空维度
            dims_node->insert_son_node(empty_dim);
            node->array_dimensions.push_back(-1);
        }

        // 处理剩余维度
        for (auto dim: dimensions) {
            if (dim) {
                dims_node->insert_son_node(dim);

                // 如果维度是常量，存储其值
                if (dim->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
                    node->array_dimensions.push_back(dim->integer_val);
                } else {
                    node->array_dimensions.push_back(-1);
                }
            }
        }

        // 将维度节点添加为子节点
        node->insert_son_node(dims_node);
    }

    return node;
}

ast_node * ast_node::clone() const
{
    // 1. 拷贝当前节点的基本属性（不拷贝parent）
    ast_node *copy = new ast_node(this->node_type, this->type, this->line_no);
    copy->integer_val = this->integer_val;
    copy->float_val = this->float_val;
    copy->op_type = this->op_type;
    copy->name = this->name;
    copy->is_array = this->is_array;
    copy->array_dimensions = this->array_dimensions;
    copy->array_element_type = this->array_element_type;
    copy->needScope = this->needScope;
    // IR/Value等不拷贝

    // 2. 递归拷贝所有子节点
    for (auto son : this->sons) {
        if (son) {
            ast_node *son_copy = son->clone();
            copy->insert_son_node(son_copy);
        }
    }
    return copy;
}