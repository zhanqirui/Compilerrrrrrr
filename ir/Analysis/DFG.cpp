#include "Analysis/DFG.h"
#include "Analysis/CFG.h"
#include "Analysis/BasicBlock.h"
#include "Instruction.h"

DFG::DFG(CFG *cfg) : cfg_(cfg) {}

void DFG::build() {
    /* 仅留空实现，待后续数据流分析补充 */
}

void DFG::dumpDot(std::ostream &os) const {
    os << "digraph DFG {\n}\n";
}
