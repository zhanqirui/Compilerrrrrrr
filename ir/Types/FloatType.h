///
/// @file FloatType.h
/// @brief 浮点类型类，可描述32位的float类型或64位的double类型
///
/// @author fsy
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

#pragma once

#include <cstdint>

#include "Type.h"

class FloatType final : public Type {
public:
    ///
    /// @brief 获取float类型实例（32位）
    /// @return FloatType*
    ///
    static FloatType * getTypeFloat();

    ///
    /// @brief 获取double类型实例（64位）
    /// @return FloatType*
    ///
    static FloatType * getTypeDouble();

    ///
    /// @brief 获取类型的IR标识符
    /// @return std::string
    ///
    [[nodiscard]] std::string toString() const override
    {
        // return bitWidth == 32 ? "f32" : "f64";
        return "float";
    }

    ///
    /// @brief 获取浮点数位宽
    /// @return int32_t
    ///
    [[nodiscard]] int32_t getBitWidth() const
    {
        return this->bitWidth;
    }

    ///
    /// @brief 是否是float类型（32位）
    /// @return bool
    ///
    [[nodiscard]] bool isFloat32() const
    {
        return bitWidth == 32;
    }

    ///
    /// @brief 是否是double类型（64位）
    /// @return bool
    ///
    [[nodiscard]] bool isFloat64() const
    {
        return bitWidth == 64;
    }

    ///
    /// @brief 获取类型所占内存空间
    /// @return int32_t
    ///
    [[nodiscard]] int32_t getSize() const override
    {
        return bitWidth / 8;
    }

private:
    ///
    /// @brief 构造函数
    /// @param _bitWidth 位宽
    ///
    explicit FloatType(int32_t _bitWidth) : Type(Type::FloatTyID), bitWidth(_bitWidth)
    {}

    static FloatType * oneInstanceFloat;
    static FloatType * oneInstanceDouble;

    int32_t bitWidth;
};
