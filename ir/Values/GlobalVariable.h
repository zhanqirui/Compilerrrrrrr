///
/// @file GlobalVariable.h
/// @brief 全局变量描述类
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

#include "GlobalValue.h"
#include "IRConstant.h"
#include "PointerType.h"
///
/// @brief 全局变量，寻址时通过符号名或变量名来寻址
///
class GlobalVariable : public GlobalValue {

public:
    ///
    /// @brief 构建全局变量，默认对齐为4字节
    /// @param _type 类型
    /// @param _name 名字
    ///
    explicit GlobalVariable(Type * _type, std::string _name) : GlobalValue(_type, _name)
    {
        // 设置对齐大小
        setAlignment(4);
    }

    ///
    /// @brief  检查是否是函数
    /// @return true 是函数
    /// @return false 不是函数
    ///
    [[nodiscard]] bool isGlobalVarible() const override
    {
        return true;
    }

    ///
    /// @brief 是否属于BSS段的变量，即未初始化过的变量，或者初值都为0的变量
    /// @return true
    /// @return false
    ///
    [[nodiscard]] bool isInBSSSection() const
    {
        return this->inBSSSection;
    }

    void setInBSSSection(bool inBSS)
    {
        this->inBSSSection = inBSS;
    }

    ///
    /// @brief 取得变量所在的作用域层级
    /// @return int32_t 层级
    ///
    int32_t getScopeLevel() override
    {
        return 0;
    }

    ///
    /// @brief 对该Value进行Load用的寄存器编号
    /// @return int32_t 寄存器编号
    ///
    int32_t getLoadRegId() override
    {
        return this->loadRegNo;
    }

    ///
    /// @brief 对该Value进行Load用的寄存器编号
    /// @return int32_t 寄存器编号
    ///
    void setLoadRegId(int32_t regId) override
    {
        this->loadRegNo = regId;
    }

    ///
    /// @brief Declare指令IR显示
    /// @param str
    ///
    void toDeclareString(std::string & str)
    {
        str = "declare " + getType()->toString() + " " + getIRName();
        if (this->type->isIntegerType()) {
            str += "=" + std::to_string(this->real_int); // 转换为字符串
        } else if (this->type->isFloatType()) {
            str += "=" + std::to_string(this->real_float); // 同理
        } else {
            const std::vector<int32_t> dims = this->arraydimensionVector;
            if (!dims.empty()) {
                for (auto dim: dims) {
                    str += "[" + std::to_string(dim) + "]";
                }

                // 获取数组的维度信息和展平数组
                const std::vector<int32_t> & dims = this->arraydimensionVector;
                const std::vector<FlattenedArrayElement> & flattenedArray = this->flattenedArray;

                // 处理多维数组
                if (!dims.empty()) {
                    str += " = ";
                    str += processMultiDimArray(dims, flattenedArray, 0, 0);
                }
            }
        }
    }
    /// @brief 递归处理多维数组
    /// @param dims 当前维度信息
    /// @param flattenedArray 展平后的数组
    /// @param currentIndex 当前处理的维度索引
    /// @param flatOffset 当前展平数组的偏移量
    /// @return 返回多维数组的字符串表示
    std::string processMultiDimArray(const std::vector<int32_t> & dims,
                                     const std::vector<FlattenedArrayElement> & flattenedArray,
                                     size_t currentIndex,
                                     int32_t flatOffset)
    {
        std::string result = "{";

        // 如果已经处理到最后一维
        if (currentIndex == dims.size() - 1) {
            for (int32_t i = 0; i < dims[currentIndex]; ++i) {
                int32_t flatIndex = flatOffset + i;
                bool found = false;

                // 查找展平数组中的值
                for (const auto & element: flattenedArray) {
                    if (element.flatIndex == flatIndex) {
                        result += std::to_string(
                            static_cast<const PointerType *>(this->getType())->getRootType()->isIntegerType()
                                ? element.intValue
                                : element.floatValue); // 找到值
                        found = true;
                        break;
                    }
                }

                // 如果找不到值，使用默认值 0
                if (!found) {
                    result += "0";
                }

                // 添加逗号分隔符，最后一个元素不加逗号
                if (i < dims[currentIndex] - 1) {
                    result += ", ";
                }
            }
        } else {
            // 递归处理下一维
            for (int32_t i = 0; i < dims[currentIndex]; ++i) {
                result += processMultiDimArray(dims,
                                               flattenedArray,
                                               currentIndex + 1,
                                               flatOffset + i * dims[currentIndex + 1]);

                // 添加逗号分隔符，最后一个元素不加逗号
                if (i < dims[currentIndex] - 1) {
                    result += ", ";
                }
            }
        }

        result += "}";
        return result;
    }

private:
    ///
    /// @brief 变量加载到寄存器中时对应的寄存器编号
    ///
    int32_t loadRegNo = -1;

    ///
    /// @brief 默认全局变量在BSS段，没有初始化，或者即使初始化过，但都值都为0
    ///
    bool inBSSSection = true;
};
