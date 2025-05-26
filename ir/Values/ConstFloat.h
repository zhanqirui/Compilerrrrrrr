///
/// @file ConstFloat.h
/// @brief float类型的常量
///
/// @author fsy
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

#include <sstream>
#include "Constant.h"
#include "IRConstant.h"
#include "FloatType.h"

///
/// @brief 浮点常量类
///
class ConstFloat : public Constant {

public:
    ///
    /// @brief 指定值的常量
    /// \param val 浮点值
    explicit ConstFloat(float val) : Constant(FloatType::getTypeFloat())
    {
        name = std::to_string(val);
        floatVal = val;
        setConst(true);
    }

    /// @brief 获取名字
    /// @return 变量名
    [[nodiscard]] std::string getIRName() const override
    {
        return name;
    }

    ///
    /// @brief 获取值
    /// @return float
    ///
    float getVal() const
    {
        return floatVal;
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
    /// @param regId 寄存器编号
    ///
    void setLoadRegId(int32_t regId) override
    {
        this->loadRegNo = regId;
    }
    ///
    /// @brief 将浮点数格式转换成LLVM格式
    /// @details 该函数将浮点数转换为十六进制字符串格式，适用于LLVM IR的表示
    /// @param num
    /// @return std::string
    ///
    static std::string float2str_llvm(float num)
    {
        union {
            uint64_t x;
            double y;
        } u;

        std::stringstream ss;
        // printf("%f\n",num);
        u.y = num;
        ss << std::hex << u.x;
        // printf("%s\n",ss.str().c_str());
        return "0x" + ss.str();
    }

private:
    ///
    /// @brief 浮点值
    ///
    float floatVal;

    ///
    /// @brief 变量加载到寄存器中时对应的寄存器编号
    ///
    int32_t loadRegNo = -1;
};