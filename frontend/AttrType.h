///
/// @file AttrType.h
/// @brief 文法符号的属性类型
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

///
/// @brief 基本类型枚举类
///
enum class BasicType : std::int8_t {
    TYPE_NONE,  // 节点不存在类型
    TYPE_VOID,  // void型，仅用于函数返回值
    TYPE_INT,   // 整型
    TYPE_FLOAT, // Float类型
    TYPE_MAX,   // 其它类型，未知类型
};

///
/// @brief 词法与语法通信的无符号整数字面量属性
///
typedef struct digit_int_attr {
    uint32_t val;   // 整数值
    int64_t lineno; // 行号
} digit_int_attr;

///
/// @brief 词法与语法通信的单精度浮点数字面量属性
///
typedef struct digit_real_attr {
    double val;     // C语言默认实数为double类型
    int64_t lineno; // 行号
} digit_real_attr;

///
/// @brief 词法与语法通信的标识符（变量名、函数名等）
///
typedef struct var_id_attr {
    char * id;      // 标识符名称
    int64_t lineno; // 行号
} var_id_attr;

///
/// @brief 类型属性
///
typedef struct type_attr {
    BasicType type; // 类型
    int64_t lineno; // 行号
} type_attr;

///
/// @brief 操作符属性
///
typedef struct op_attr {
    char op;        // 操作符
    int64_t lineno; // 行号
} op_attr;

///
/// @brief 表示运算符的枚举
///
enum class Op : std::int8_t {
    LT,  // <
    LE,  // <=
    GT,  // >
    GE,  // >=REL
    EQ,  // ==
    NE,  // !=EQ
    ADD, // +
    SUB, // -
    MUL, // *
    DIV, // /EXP
    MOD, // %
    AND, // &&
    OR,  // ||
    NOT, // !
    POS, // +
    NEG, // -
    NONE
};
///
/// @brief 判断是否是加法运算符
/// @param op 运算符枚举值
/// @return true 如果是加法运算符
/// @return false 如果不是
///
inline bool isAddOp(Op op)
{
    return op == Op::ADD;
}

///
/// @brief 判断是否是减法运算符
/// @param op 运算符枚举值
/// @return true 如果是减法运算符
/// @return false 如果不是
///
inline bool isSubOp(Op op)
{
    return op == Op::SUB;
}

///
/// @brief 判断是否是乘法运算符
/// @param op 运算符枚举值
/// @return true 如果是乘法运算符
/// @return false 如果不是
///
inline bool isMulOp(Op op)
{
    return op == Op::MUL;
}

///
/// @brief 判断是否是除法运算符
/// @param op 运算符枚举值
/// @return true 如果是除法运算符
/// @return false 如果不是
///
inline bool isDivOp(Op op)
{
    return op == Op::DIV;
}