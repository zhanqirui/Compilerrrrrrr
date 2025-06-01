#pragma once
#include <string>
#include <vector>
#include <unordered_set>

class Instruction;   // 前向声明

/**
 * @brief 非 SSA 的基本块，只记录顺序指令和 CFG 边
 */
class BasicBlock {
public:
    explicit BasicBlock(const std::string &labelName);

    /* 指令管理 */
    void                appendInst(Instruction *inst);
    Instruction        *getTerminator() const;

    /* CFG 前驱 / 后继集合 */
    std::unordered_set<BasicBlock *> &getPreds();
    std::unordered_set<BasicBlock *> &getSuccs();

    /* 只读访问 */
    const std::vector<Instruction *> &getInsts() const;
    const std::string                &getLabel() const;

private:
    std::string                       label_;
    std::vector<Instruction *>        insts_;
    std::unordered_set<BasicBlock *>  preds_;
    std::unordered_set<BasicBlock *>  succs_;
};
