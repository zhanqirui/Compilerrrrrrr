#include "CFG.h"
#include "BasicBlock.h"

#include "Function.h"
#include "Instruction.h"
#include "Instructions/LabelInstruction.h"
#include "Instructions/BranchInstruction.h"
#include "Instructions/GotoInstruction.h"

#include <unordered_set>

CFG::CFG(Function *func) : func_(func) {}

void CFG::buildBlocks() {
    std::vector<Instruction *> &insts = func_->getInterCode().getInsts();
    std::unordered_set<Instruction *> leaders;

    if (!insts.empty()) leaders.insert(insts.front());   // 规则 1

    for (Instruction *inst : insts) {
        if (dynamic_cast<LabelInstruction *>(inst))          // 规则 2
            leaders.insert(inst);

        if (auto *br = dynamic_cast<BranchInstruction *>(inst)) {  // 规则 3
            leaders.insert(br->getTrueTarget());
            if (br->getFalseTarget()) leaders.insert(br->getFalseTarget());
        }
        if (auto *go = dynamic_cast<GotoInstruction *>(inst))
            leaders.insert(go->getTarget());
    }

    BasicBlock *current = nullptr;
    for (Instruction *inst : insts) {
        if (leaders.count(inst)) {
            LabelInstruction *lbl = dynamic_cast<LabelInstruction *>(inst);
            std::string blockName = lbl ? lbl->getLabelName() : "entry";
            blocks_.push_back(std::make_unique<BasicBlock>(blockName));
            current = blocks_.back().get();
            label2Block_[blockName] = current;
        }
        current->appendInst(inst);
    }
}

void CFG::connectBlocks() {
    for (const auto &bbPtr : blocks_) {
        Instruction *term = bbPtr->getTerminator();
        if (!term) continue;

        if (auto *br = dynamic_cast<BranchInstruction *>(term)) {
            BasicBlock *succT = label2Block_.at(br->getTrueTarget()->getLabelName());
            bbPtr->getSuccs().insert(succT);
            succT->getPreds().insert(bbPtr.get());

            if (br->getFalseTarget()) {
                BasicBlock *succF = label2Block_.at(br->getFalseTarget()->getLabelName());
                bbPtr->getSuccs().insert(succF);
                succF->getPreds().insert(bbPtr.get());
            }
        }
        else if (auto *go = dynamic_cast<GotoInstruction *>(term)) {
            BasicBlock *succ = label2Block_.at(go->getTarget()->getLabelName());
            bbPtr->getSuccs().insert(succ);
            succ->getPreds().insert(bbPtr.get());
        }
        /* ExitInstruction —— 无后继 */
    }
}

void CFG::dumpDot(std::ostream &os) const {
    os << "digraph CFG_" << func_->getName() << " {\n";
    for (const auto &bbPtr : blocks_) {
        os << "  \"" << bbPtr->getLabel() << "\" [shape=box];\n";
        for (BasicBlock *succ : bbPtr->getSuccs()) {
            os << "  \"" << bbPtr->getLabel() << "\" -> \"" << succ->getLabel() << "\";\n";
        }
    }
    os << "}\n";
}

BasicBlock *CFG::getEntry() const {
    return blocks_.empty() ? nullptr : blocks_.front().get();
}

const std::vector<std::unique_ptr<BasicBlock>> &CFG::getBlocks() const {
    return blocks_;
}
