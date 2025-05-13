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
#include <sstream>

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
    /// @param varName
    ///
	void toDeclareString(std::string &varName)
	{
		varName = getIRName();
		if (this->type->isIntegerType()) {
			varName += " = dso_local global " + getType()->toString() + " " + std::to_string(this->real_int) + ", align 4";
		} else if (this->type->isFloatType()) {
			varName += " = dso_local global " + getType()->toString() + " " + std::to_string(this->real_float) + ", align 4";
		} else {
			std::vector<std::pair<int, int>> flatArr;
			for (const auto &elem : this->flattenedArray) {
				flatArr.push_back({elem.flatIndex, elem.intValue});
			}

			const std::vector<int32_t> &dims = this->arraydimensionVector;
			if (!dims.empty()) {
				std::string arrayType;
				for (auto it = dims.begin(); it != dims.end(); ++it) {
					arrayType += "[" + std::to_string(*it) + " x ";
				}

				Type *baseType = getType();
				PointerType *pointerType = dynamic_cast<PointerType *>(baseType);
				std::string elemType = pointerType->getreferencetype()->toString();

				arrayType += elemType;
				for (size_t i = 0; i < dims.size(); ++i) {
					arrayType += "]";
				}
				arrayType += " ";

				// Generate the content string
				if (this->flattenedArray.empty()) {
					varName += " = dso_local global " + arrayType + "zeroinitializer, align 16";
				} else {
					std::string typeStr = getArrayTypeStr(dims, 0, elemType);
					std::string content = emitContent(dims, elemType, flatArr, 0, 0);
					varName += " = dso_local constant " + typeStr + " " + content + ", align 16";
				}
			}
		}
	}

	// 构造 LLVM IR 类型字符串，比如 [5 x [5 x i32]]
	std::string getArrayTypeStr(const std::vector<int> &dims, int dimIdx, const std::string &elemType) {
		std::string res = elemType;
		for (int i = dims.size() - 1; i >= dimIdx; --i) {
			res = "[" + std::to_string(dims[i]) + " x " + res + "]";
		}
		return res;
	}

	std::string emitContent(const std::vector<int> &dims,
							const std::string &elemType,
							const std::vector<std::pair<int, int>> &flatArr,
							size_t dimIdx, int flatOffset) {
		int dim = dims[dimIdx];
		int nextDimSize = 1;
		for (size_t i = dimIdx + 1; i < dims.size(); ++i)
			nextDimSize *= dims[i];

		// 检查当前维度及所有子维度是否全为零
		bool isAllZero = true;
		int totalSize = nextDimSize * dim;
		for (const auto &[idx, val] : flatArr) {
			if (idx >= flatOffset && idx < flatOffset + totalSize && val != 0) {
				isAllZero = false;
				break;
			}
		}

		std::string typeStr = getArrayTypeStr(dims, dimIdx, elemType);

		// 如果整个区域全为零，直接返回zeroinitializer
		if (isAllZero && dimIdx != 0) {
			return typeStr + " zeroinitializer";
		}

		if (dimIdx == dims.size() - 1) {
			// 最后一维
			bool isDimZero = true;
			std::vector<int> values(dim, 0);
			for (const auto &[idx, val] : flatArr) {
				if (idx >= flatOffset && idx < flatOffset + dim) {
					values[idx - flatOffset] = val;
					if (val != 0) isDimZero = false;
				}
			}

			if (isDimZero)
				return "[" + std::to_string(dim) + " x " + elemType + "] zeroinitializer";

			std::string res = "[";
			for (int i = 0; i < dim; ++i) {
				res += elemType + " " + std::to_string(values[i]);
				if (i < dim - 1)
					res += ", ";
			}
			res += "]";
			return "[" + std::to_string(dim) + " x " + elemType + "] " + res;
		}

		// 非最后一维
		std::string res = "[";
		for (int i = 0; i < dim; ++i) {
			// 检查这个子数组是否全为零
			bool isSubZero = true;
			for (const auto &[idx, val] : flatArr) {
				if (idx >= flatOffset + i * nextDimSize && 
					idx < flatOffset + (i + 1) * nextDimSize && 
					val != 0) {
					isSubZero = false;
					break;
				}
			}
			
			std::string subTypeStr = getArrayTypeStr(dims, dimIdx + 1, elemType);
			
			if (isSubZero) {
				res += subTypeStr + " zeroinitializer";
			} else {
				res += emitContent(dims, elemType, flatArr, dimIdx + 1, flatOffset + i * nextDimSize);
			}
			
			if (i < dim - 1)
				res += ", ";
		}
		res += "]";
		
		if (dimIdx == 0) {
			return res;
		} else {
			return "[" + std::to_string(dim) + " x " + getArrayTypeStr(dims, dimIdx + 1, elemType) + "] " + res;
		}
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
