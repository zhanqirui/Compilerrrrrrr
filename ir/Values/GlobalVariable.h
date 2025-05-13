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
    void renameIR()
    {
        if (this->const_func_name != "null") {
            IRName = "@__const." + this->const_func_name + "." + name;
        }
    }

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
        str = getIRName();
        if (this->type->isIntegerType()) {
            str += " = dso_local global " + getType()->toString() + " " + std::to_string(this->real_int) + ", align 4";
        } else if (this->type->isFloatType()) {
            str +=
                " = dso_local global " + getType()->toString() + " " + std::to_string(this->real_float) + ", align 4";
        } else {
            const std::vector<int32_t> & dims = this->arraydimensionVector;

            if (!dims.empty()) {
                std::string arrayType = "";
                for (auto it = dims.begin(); it != dims.end(); ++it) {
                    arrayType += "[" + std::to_string(*it) + " x ";
                }
                Type * baseType = getType(); // 获取类型
                PointerType * pointerType = dynamic_cast<PointerType *>(baseType);
                arrayType += pointerType->getreferencetype()->toString();
                for (size_t i = 0; i < dims.size(); ++i) {
                    arrayType += "]";
                }
                arrayType += " ";
                if (this->const_func_name == "null") {
                    str += " = dso_local global " + arrayType;

                    // 添加数组声明
                    str += " zeroinitializer, align 16";
                } else {

                    str += " = private unnamed_addr constant " + arrayType;
                    const std::vector<int32_t> dims = this->arraydimensionVector;
                    if (!dims.empty()) {

                        // 获取数组的维度信息和展平数组
                        const std::vector<int32_t> & dims = this->arraydimensionVector;
                        const std::vector<FlattenedArrayElement> & flattenedArray = this->flattenedArray;

                        // 处理多维数组
                        if (!dims.empty()) {
                            str += processMultiDimArray(this, dims, flattenedArray, 0, 0);
                            str += ", align 16";
                        }
                    }
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
    std::string processMultiDimArray(Value * Var,
                                     const std::vector<int32_t> & dims,
                                     const std::vector<FlattenedArrayElement> & flattenedArray,
                                     size_t currentIndex,
                                     int32_t flatOffset)
    {
        std::string result;
        int dim = dims[currentIndex];

        // 递归到最后一维
        if (currentIndex == dims.size() - 1) {
            result += "[" + std::to_string(dim) + " x i32] [";
            for (int i = 0; i < dim; ++i) {
                int flatIndex = flatOffset + i;
                bool found = false;
                for (const auto & element: flattenedArray) {
                    if (element.flatIndex == flatIndex) {
                        result += "i32 " + std::to_string(element.intValue);
                        found = true;
                        break;
                    }
                }
                if (!found)
                    result += "i32 0";
                if (i < dim - 1)
                    result += ", ";
            }
            result += "]";
            return result;
        }

        // 递归处理高维
        result += "[" + std::to_string(dim) + " x ";
        // 类型说明
        result += processMultiDimArray(Var, dims, flattenedArray, currentIndex + 1, flatOffset);
        result += "] [";
        int nextDimSize = 1;
        for (size_t i = currentIndex + 1; i < dims.size(); ++i)
            nextDimSize *= dims[i];
        for (int i = 0; i < dim; ++i) {
            // 每个元素前加类型
            result += "[" + std::to_string(dims[currentIndex + 1]);
            for (size_t j = currentIndex + 2; j < dims.size(); ++j)
                result += " x " + std::to_string(dims[j]);
            result += " x i32] ";
            result += processMultiDimArray(Var, dims, flattenedArray, currentIndex + 1, flatOffset + i * nextDimSize);
            if (i < dim - 1)
                result += ", ";
        }
        result += "]";
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
