///
/// @file FloatType.cpp
/// @brief 浮点类型类，可描述32位的float类型或64位的double类型
///
/// @author fsyj
/// @version 1.0
/// @date 2025-04-23
///
/// @copyright Copyright (c) 2025
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2025-04-23 <td>1.0     <td>zenglj  <td>新建
/// </table>
///

#include "FloatType.h"

///
/// @brief 唯一的float和double类型实例
///
FloatType * FloatType::oneInstanceFloat = new FloatType(32);
FloatType * FloatType::oneInstanceDouble = new FloatType(64);

///
/// @brief 获取float类型（32位）
/// @return FloatType*
///
FloatType * FloatType::getTypeFloat()
{
    return oneInstanceFloat;
}

///
/// @brief 获取double类型（64位）
/// @return FloatType*
///
FloatType * FloatType::getTypeDouble()
{
    return oneInstanceDouble;
}
