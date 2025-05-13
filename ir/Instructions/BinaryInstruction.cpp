///
/// @file BinaryInstruction.cpp
/// @brief 二元操作指令
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
#include "BinaryInstruction.h"

/// @brief 构造函数
/// @param _op 操作符
/// @param _result 结果操作数
/// @param _srcVal1 源操作数1
/// @param _srcVal2 源操作数2
BinaryInstruction::BinaryInstruction(Function * _func,
                                     IRInstOperator _op,
                                     Value * _srcVal1,
                                     Value * _srcVal2,
                                     Type * _type)
    : Instruction(_func, _op, _type)
{
    addOperand(_srcVal1);
    addOperand(_srcVal2);
}

/// @brief 转换成字符串
/// @param str 转换后的字符串
void BinaryInstruction::toString(std::string & str)
{

    Value *src1 = getOperand(0), *src2 = getOperand(1);
    std::string type_str = this->getType()->toString() + " ";
    // {
    //     if (src1->type->isFloatType() || src2->type->isFloatType())
    //         type_str = "float ";
    //     else
    //         type_str = src1->type->toString() + ' ';
    //     ;
    // }
    switch (op) {
        case IRInstOperator::IRINST_OP_ADD_I:

            // 加法指令，二元运算

            str = getIRName() + " = add nsw " + type_str + src1->getIRName() + ", " + src2->getIRName();

            break;
        case IRInstOperator::IRINST_OP_SUB_I:

            // 减法指令，二元运算
            str = getIRName() + " = sub nsw " + type_str + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_MUL_I:

            // 减法指令，二元运算
            str = getIRName() + " = mul nsw " + type_str + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_DIV_I:
            if (src1->getType()->toString() == "i32") {
                str = getIRName() + " = sdiv " + type_str + src1->getIRName() + ", " + src2->getIRName();
            } else {
                str = getIRName() + " = fdiv " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_GT_I:
            str = getIRName() + " = icmp sgt " + type_str + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_GE_I:

            // 减法指令，二元运算
            str = getIRName() + " = icmp sge " + type_str + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_LT_I:

            // 减法指令，二元运算
            str = getIRName() + " = icmp slt " + type_str + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_LE_I:

            // 减法指令，二元运算
            str = getIRName() + " = icmp sle " + type_str + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_EQ_I:

            // 减法指令，二元运算
            str = getIRName() + " = icmp eq " + type_str + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_NE_I:

            // 减法指令，二元运算
            str = getIRName() + " = icmp ne " + type_str + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_AND_I:

            // 减法指令，二元运算
            str = getIRName() + " = and i1 " + src1->getIRName() + "," + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_OR_I:

            // 减法指令，二元运算
            str = getIRName() + " = or i1 " + src1->getIRName() + "," + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_MOD_I:

            // 减法指令，二元运算
            str = getIRName() + " = srem " + type_str + src1->getIRName() + ", " + src2->getIRName();
            break;
        default:
            // 未知指令
            Instruction::toString(str);
            break;
    }
}
