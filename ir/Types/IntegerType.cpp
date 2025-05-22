///
/// @file IntegerType.cpp
/// @brief 整型类型类，可描述1位的bool类型或32位的int类型
///
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

#include "IntegerType.h"

///
/// @brief 获取类型bool
/// @return VoidType*
///
IntegerType* IntegerType::getTypeBool() {
    static IntegerType instance(1);
    return &instance;
}

///
/// @brief 获取类型int
/// @return VoidType*
///
IntegerType* IntegerType::getTypeInt() {
    static IntegerType instance(32);  // ⚠️局部静态变量初始化顺序保证
    return &instance;
}