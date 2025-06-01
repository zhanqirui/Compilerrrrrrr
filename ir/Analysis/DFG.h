#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

class CFG;
class Instruction;

/**
 * @brief 数据流图节点
 */
struct DFGNode {
    Instruction                     *inst;
    std::unordered_set<DFGNode *>    preds;
    std::unordered_set<DFGNode *>    succs;
};

/**
 * @brief 数据流图 (Data-Flow Graph) —— 预留骨架
 */
class DFG {
public:
    explicit DFG(CFG *cfg);

    void build();              ///< TODO: 根据 def-use 填充
    void dumpDot(std::ostream &os) const;

private:
    CFG                                               *cfg_;
    std::vector<std::unique_ptr<DFGNode>>              nodes_;
    std::unordered_map<Instruction *, DFGNode *>       inst2node_;
};
