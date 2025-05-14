///
/// @file IRCode.cpp
/// @brief IR指令序列类实现
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>新做
/// </table>
///
#include "IRCode.h"

/// @brief 析构函数
InterCode::~InterCode()
{
    Delete();
}

/// @brief 添加一个指令块，添加到尾部，并清除原来指令块的内容
/// @param block 指令块，请注意加入后会自动清空block的指令
// void InterCode::addInst(InterCode & block)
// {
//     std::vector<Instruction *> & insert = block.getInsts();

//     code.insert(code.end(), insert.begin(), insert.end());

//     // InterCode析构会清理资源，因此移动指令到code中后必须清理，否则会释放多次导致程序例外
//     // 当然，这里也可不清理，但InterCode的析构函数不能清理，需专门的函数清理即可。
//     insert.clear();
// }
void InterCode::addInst(InterCode & block)
{
    std::vector<Instruction *> & insert = block.getInsts();

    // 先处理 code 的最后一条和 insert 的第一条
    while (!code.empty() && !insert.empty()) {
        Instruction * last = code.back();
        Instruction * first = insert.front();
        if (last->getOp() == IRInstOperator::IRINST_OP_GOTO && first->getOp() == IRInstOperator::IRINST_OP_GOTO) {
            delete first; // 如果需要释放内存
            insert.erase(insert.begin());
        } else {
            break;
        }
    }

    // 新建一个临时vector用于去除连续goto或label
    std::vector<Instruction *> filtered;
    for (size_t i = 0; i < insert.size(); ++i) {
        bool skip = false;
        if (!filtered.empty()) {
            Instruction * prev = filtered.back();
            if ((insert[i]->getOp() == IRInstOperator::IRINST_OP_GOTO &&
                 prev->getOp() == IRInstOperator::IRINST_OP_GOTO)) {
                delete insert[i];
                skip = true;
            }
        }
        if (!skip) {
            filtered.push_back(insert[i]);
        }
    }

    code.insert(code.end(), filtered.begin(), filtered.end());

    // 清理原始vector
    insert.clear();
}

/// @brief 添加一条中间指令
/// @param inst IR指令
void InterCode::addInst(Instruction * inst)
{
    code.push_back(inst);
}

/// @brief 获取指令序列
/// @return 指令序列
std::vector<Instruction *> & InterCode::getInsts()
{
    return code;
}

/// @brief 删除所有指令
void InterCode::Delete()
{
    // 不能直接删除指令，需要先清除操作数
    for (auto inst: code) {
        inst->clearOperands();
    }

    // 资源清理
    for (auto inst: code) {
        delete inst;
    }

    code.clear();
}
