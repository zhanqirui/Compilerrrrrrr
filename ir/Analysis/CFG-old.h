#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

#include "Analysis/BasicBlock.h"

/* 前向声明以避免循环依赖 */
class Function;
class Instruction;
class LabelInstruction;
class BranchInstruction;
class GotoInstruction;

/**
 * @brief 控制流图 (Control-Flow Graph)
 */
class CFG {
public:
    explicit CFG(Function *func);

    void buildBlocks();    ///< 依据“领导者”规则划分基本块
    void connectBlocks();  ///< 根据终结指令补全前驱 / 后继
    void build() { buildBlocks(); connectBlocks(); }

    void dumpDot(std::ostream &os) const; ///< 以 DOT 格式输出

    /* 访问接口 */
    BasicBlock                                        *getEntry() const;
    const std::vector<std::unique_ptr<BasicBlock>>    &getBlocks() const;

private:
    Function                                         *func_;
    std::unordered_map<std::string, BasicBlock *>     label2Block_;
    std::vector<std::unique_ptr<BasicBlock>>          blocks_;
};
