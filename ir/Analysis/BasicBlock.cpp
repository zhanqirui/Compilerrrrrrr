#include "Analysis/BasicBlock.h"
#include "Instruction.h"

BasicBlock::BasicBlock(const std::string &labelName) : label_(labelName) {}

void BasicBlock::appendInst(Instruction *inst) { insts_.push_back(inst); }

Instruction *BasicBlock::getTerminator() const {
    if (insts_.empty()) return nullptr;
    return insts_.back();          // 构建阶段保证最后一条为终结指令
}

std::unordered_set<BasicBlock *> &BasicBlock::getPreds() { return preds_; }
std::unordered_set<BasicBlock *> &BasicBlock::getSuccs() { return succs_; }

const std::vector<Instruction *> &BasicBlock::getInsts() const { return insts_; }
const std::string                &BasicBlock::getLabel() const { return label_; }
