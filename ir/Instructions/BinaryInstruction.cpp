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
#include "ConstFloat.h"

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
    std::string type_str;
    {
        if (src1->type->isFloatType() || src2->type->isFloatType())
            type_str = "float ";
        else
            type_str = src1->type->toString() + ' ';
        ;
    }
    //对于所有的常量计算直接把其具体的值打印到IR中
    switch (op) {
        case IRInstOperator::IRINST_OP_ADD_F:

            // 加法指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st1 = std::to_string(src1->real_float);
                        st1 = ConstFloat::float2str_llvm(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st2 = std::to_string(src2->real_float);
                        st2 = ConstFloat::float2str_llvm(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = fadd " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = fadd " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;
        case IRInstOperator::IRINST_OP_ADD_I:

            // 加法指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        st1 = std::to_string(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        st2 = std::to_string(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = add nsw " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = add nsw " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_SUB_F:

            // 减法指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st1 = std::to_string(src1->real_float);
                        st1 = ConstFloat::float2str_llvm(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st2 = std::to_string(src2->real_float);
                        st2 = ConstFloat::float2str_llvm(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = fsub " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = fsub " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_SUB_I:

            // 减法指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        st1 = std::to_string(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        st2 = std::to_string(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = sub nsw " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = sub nsw " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_MUL_F:

            // 乘法指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st1 = std::to_string(src1->real_float);
                        st1 = ConstFloat::float2str_llvm(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st2 = std::to_string(src2->real_float);
                        st2 = ConstFloat::float2str_llvm(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = fmul " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = fmul " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_MUL_I:

            // 乘法指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        st1 = std::to_string(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        st2 = std::to_string(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = mul nsw " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = mul nsw " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_DIV_F:

            // 除法指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st1 = std::to_string(src1->real_float);
                        st1 = ConstFloat::float2str_llvm(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st2 = std::to_string(src2->real_float);
                        st2 = ConstFloat::float2str_llvm(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = fdiv " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = fdiv " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_DIV_I:

            // 除法指令，二元运算
            if (src1->getType()->toString() == "i32") {
                if (src1->isConst() || src2->isConst()) {
                    std::string st1, st2;
                    if (src1->isConst()) {
                        st1 = std::to_string(src1->real_int);
                    } else {
                        st1 = src1->getIRName();
                    }
                    if (src2->isConst()) {
                        st2 = std::to_string(src2->real_int);
                    } else {
                        st2 = src2->getIRName();
                    }
                    str = getIRName() + " = sdiv " + type_str + st1 + ", " + st2;
                } else {
                    str = getIRName() + " = sdiv " + type_str + src1->getIRName() + ", " + src2->getIRName();
                }
            } else {
                if (src1->isConst() || src2->isConst()) {
                    std::string st1, st2;
                    if (src1->isConst()) {
                        st1 = std::to_string(src1->real_float);
                    } else {
                        st1 = src1->getIRName();
                    }
                    if (src2->isConst()) {
                        st2 = std::to_string(src2->real_float);
                    } else {
                        st2 = src2->getIRName();
                    }
                    str = getIRName() + " = fdiv " + type_str + st1 + ", " + st2;
                } else {
                    str = getIRName() + " = fdiv " + type_str + src1->getIRName() + ", " + src2->getIRName();
                }
            }
            break;

        case IRInstOperator::IRINST_OP_GT_F:

            //浮点大于指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st1 = std::to_string(src1->real_float);
                        st1 = ConstFloat::float2str_llvm(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st2 = std::to_string(src2->real_float);
                        st2 = ConstFloat::float2str_llvm(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = fcmp ogt " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = fcmp ogt " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_GT_I:

            //有符号大于指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        st1 = std::to_string(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        st2 = std::to_string(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = icmp sgt " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = icmp sgt " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_GE_F:

            //浮点大于等于指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st1 = std::to_string(src1->real_float);
                        st1 = ConstFloat::float2str_llvm(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st2 = std::to_string(src2->real_float);
                        st2 = ConstFloat::float2str_llvm(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = fcmp oge " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = fcmp oge " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_GE_I:

            // 有符号大于等于指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        st1 = std::to_string(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        st2 = std::to_string(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = icmp sge " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = icmp sge " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_LT_F:

            // 浮点小于指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st1 = std::to_string(src1->real_float);
                        st1 = ConstFloat::float2str_llvm(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st2 = std::to_string(src2->real_float);
                        st2 = ConstFloat::float2str_llvm(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = fcmp olt " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = fcmp olt " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_LT_I:

            // 有符号小于指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        st1 = std::to_string(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        st2 = std::to_string(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = icmp slt " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = icmp slt " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_LE_F:

            // 浮点小于等于指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st1 = std::to_string(src1->real_float);
                        st1 = ConstFloat::float2str_llvm(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st2 = std::to_string(src2->real_float);
                        st2 = ConstFloat::float2str_llvm(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = fcmp ole " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = fcmp ole " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_LE_I:

            // 有符号小于等于指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        st1 = std::to_string(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        st2 = std::to_string(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = icmp sle " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = icmp sle " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_EQ_F:

            // 浮点相等判断指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st1 = std::to_string(src1->real_float);
                        st1 = ConstFloat::float2str_llvm(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st2 = std::to_string(src2->real_float);
                        st2 = ConstFloat::float2str_llvm(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = fcmp oeq " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = fcmp oeq " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_EQ_I:

            // 相等判断指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        st1 = std::to_string(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        st2 = std::to_string(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = icmp eq " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = icmp eq " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_NE_F:

            // 浮点不相等判断指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st1 = std::to_string(src1->real_float);
                        st1 = ConstFloat::float2str_llvm(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        // st2 = std::to_string(src2->real_float);
                        st2 = ConstFloat::float2str_llvm(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = fcmp one " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = fcmp one " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_NE_I:

            // 不相等判断指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    if (src1->type->isFloatType()) {
                        st1 = std::to_string(src1->real_float);
                    } else {
                        st1 = std::to_string(src1->real_int);
                    }
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    if (src1->type->isFloatType()) {
                        st2 = std::to_string(src2->real_float);
                    } else {
                        st2 = std::to_string(src2->real_int);
                    }
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = icmp ne " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = icmp ne " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_AND_I:

            // 有符号整数与指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    st1 = std::to_string(src1->real_int);
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    st2 = std::to_string(src2->real_int);
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = and i1 " + st1 + "," + st2;
            } else {
                str = getIRName() + " = and i1 " + src1->getIRName() + "," + src2->getIRName();
            }
            break;

        case IRInstOperator::IRINST_OP_OR_I:

            // 有符号整数或指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    st1 = std::to_string(src1->real_int);
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    st2 = std::to_string(src2->real_int);
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = or i1 " + st1 + "," + st2;
            } else {
                str = getIRName() + " = or i1 " + src1->getIRName() + "," + src2->getIRName();
            }
            str = getIRName() + " = or i1 " + src1->getIRName() + "," + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_MOD_I:

            // 有符号整数取余指令，二元运算
            if (src1->isConst() || src2->isConst()) {
                std::string st1, st2;
                if (src1->isConst()) {
                    st1 = std::to_string(src1->real_int);
                } else {
                    st1 = src1->getIRName();
                }
                if (src2->isConst()) {
                    st2 = std::to_string(src2->real_int);
                } else {
                    st2 = src2->getIRName();
                }
                str = getIRName() + " = srem " + type_str + st1 + ", " + st2;
            } else {
                str = getIRName() + " = srem " + type_str + src1->getIRName() + ", " + src2->getIRName();
            }
            break;

        default:
            // 未知指令
            Instruction::toString(str);
            break;
    }
}
