///
/// @file Value.h
/// @brief 值操作类型，所有的变量、函数、常量都是Value
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
#pragma once

#include <cstdint>
#include <string>

#include "Use.h"
#include "Type.h"
struct FlattenedArrayElement {
    int32_t flatIndex; // 展平后的索引
    int32_t intValue;  // 整数值
    float floatValue;  // 浮点值
};
///
/// @brief 值类，每个值都要有一个类型，全局变量和局部变量可以有名字，
/// 但通过运算得到的指令类值没有名字，只有在需要输出时给定名字即可
///
/// Value表示所有可计算的值的基类，例如常量、指令、参数等。
/// 每个Value都有一个类型(Type)和一个名字(Name)。Value是IR中所有可计算实体的抽象。
///
class Value {

protected:
    /// @brief 变量名，函数名等原始的名字，可能为空串
    std::string name;

    ///
    /// @brief IR名字，用于文本IR的输出
    ///
    std::string IRName;

    /// @brief 类型

    ///
    /// @brief define-use链，这个定值被使用的所有边，即所有的User
    ///
    std::vector<Use *> uses;

    int liveStart; // 活跃起始位置（如指令编号）
    int liveEnd;   // 活跃结束位置

    ///
    /// @brief 判断是否是const型变量
    ///
    bool is_constant = false;

public:
    std::string const_func_name = "null";
    /// @brief 构造函数
    /// @param _type
    explicit Value(Type * _type);

    /// @brief 析构函数
    virtual ~Value();

    /// @brief 获取名字
    /// @return 变量名
    [[nodiscard]] virtual std::string getName() const;

    ///
    /// @brief 设置名字
    /// @param _name 名字
    ///
    void setName(std::string _name);

    /// @brief 获取名字
    /// @return 变量名
    [[nodiscard]] virtual std::string getIRName() const;

    ///
    /// @brief 设置名字
    /// @param _name 名字
    ///
    void setIRName(std::string _name);

    /// @brief 获取类型
    /// @return 变量名
    virtual Type * getType();

    ///
    /// @brief 增加一条边，增加Value被使用次数
    /// @param use
    ///
    void addUse(Use * use);

    ///
    /// @brief 消除一条边，减少Value被使用次数
    /// @param use
    ///
    void removeUse(Use * use);

    ///
    /// @brief 取得变量所在的作用域层级
    /// @return int32_t 层级
    ///
    virtual int32_t getScopeLevel();

    ///
    /// @brief 获得分配的寄存器编号或ID
    /// @return int32_t 寄存器编号
    ///
    virtual int32_t getRegId();

    ///
    /// @brief @brief 如是内存变量型Value，则获取基址寄存器和偏移
    /// @param regId 寄存器编号
    /// @param offset 相对偏移
    /// @return true 是内存型变量
    /// @return false 不是内存型变量
    ///
    virtual bool getMemoryAddr(int32_t * regId = nullptr, int64_t * offset = nullptr);

    ///
    /// @brief 对该Value进行Load用的寄存器编号
    /// @return int32_t 寄存器编号
    ///
    virtual int32_t getLoadRegId();

    ///
    /// @brief 对该Value进行Load用的寄存器编号
    /// @return int32_t 寄存器编号
    ///
    virtual void setLoadRegId(int32_t regId);

    ///
    /// @brief 获取活跃结束位置
    /// @return int32_t 结束位置指令编号
    ///
    virtual int32_t getLiveEnd();

    /// @brief 作为数组的下标集合
    std::vector<int32_t> arrayIndexVector;
    std::vector<int32_t> arraydimensionVector;
    std::vector<FlattenedArrayElement> flattenedArray;

    void addElement(int32_t flatIndex, int32_t intValue, float floatValue)
    {
        flattenedArray.push_back({flatIndex, intValue, floatValue});
    }
    std::vector<FlattenedArrayElement> getElement()
    {
        return flattenedArray;
    }
    void ReplaceElement(const std::vector<FlattenedArrayElement> & b)
    {
        flattenedArray = b;
    }

    /// @brief 设置是否为常量
    /// @param value
    void setConst(bool value)
    {
        is_constant = value;
    }
    bool isArray() const
    {
        return !arraydimensionVector.empty();
    }
    /// @brief 判断该值是否为常量
    /// @return 是否是const，默认返回false
    bool isConst()
    {
        return is_constant;
    }
    int real_int;
    float real_float;

    Type * type;
};
