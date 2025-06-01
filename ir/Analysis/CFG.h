/**
 * @file drawCFG.cpp
 * @author ykykzq(https://github.com/ykykzq)
 * @brief 根据已经生成的ir文件，生成CFG
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef CFG_H
#define CFG_H

#include "Module.h"
#include "Instruction.h"
#include "GotoInstruction.h"
#include "LabelInstruction.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <gvc.h>

// CFG_block类
class CFG_block {
public:
    std::vector<std::string> entries;     // 存储该block所有的入口
    std::vector<std::string> exits;       // 存储该block所有的出口
    std::vector<Instruction *> irInstructions; // 存储所有的ir指令

    CFG_block()
    {}
};

// CFG_function类
class CFG_function {
public:
    // 当前正在活动的CFG_block
    CFG_block * currentBlock;

    std::string name; //函数的名字

    std::vector<CFG_block *> blocks;                       // 存储该函数的所有CFG_block
    std::unordered_map<std::string, CFG_block *> blockMap; // entries到block的映射

    //用来画图
    std::vector<Agnode_t *> nodes; // 存储该函数的所有CFG_block
    std::unordered_map<CFG_block *, Agnode_t *> nodeMap;

    /// @brief 当前函数的指令序列
    std::vector<Instruction *> code;

public:
    CFG_function() : currentBlock(nullptr)
    {}

    /// @brief 新建一个block
    /// @return 指向新block的指针
    CFG_block * newBlock()
    {
        auto new_block = new CFG_block(); // Corrected the variable name from new_blcok to new_block
        blocks.push_back(new_block);
        return new_block;
    }

    /// @brief 向Block中添加entries
    /// @param entry 入口,是一个字符串
    /// @param cfg_block 对应的cfg_block
    /// @return 指向新block的指针
    bool addEntry2Block(std::string entry, CFG_block * cfg_block)
    {
        //向block中添加入口
        cfg_block->entries.push_back(entry);
        blockMap[entry] = cfg_block;
        return true;
    }

    // 添加一个新的node
    void addCFGnode(CFG_block * block, Agnode_t * node)
    {
        nodes.push_back(node);
        nodeMap[block] = node;
    }

    /// @brief 遍历基本块获取指令序列
    /// @return 指令序列
    std::vector<Instruction *> & getInsts()
    {
        code.clear();
        for (auto basic_block: blocks) {
            for (auto ir: basic_block->irInstructions) {
                code.push_back(ir);
            }
        }
        return code;
    }
};

// CFG_Generator类，管理多个CFG_function对象
class CFG_Generator {
protected:
    // 存储所有的CFG_function对象
    std::vector<CFG_function *> functions;
    std::unordered_map<std::string, CFG_function *> funcMap;

    // 当前活动的CFG_function
    CFG_function * currentFunction;

    /// @brief 符号表
    Module * symtab;

public:
    CFG_Generator(Module * _symtab) : currentFunction(nullptr), symtab(_symtab)
    {}
    CFG_Generator() : currentFunction(nullptr)
    {}

    /// @brief 新建一个function
    /// @param name 新function的名字
    /// @return 指向新func的指针
    CFG_function * newFunction(std::string & name)
    {
        auto new_func = new CFG_function();
        functions.push_back(new_func);
        funcMap[name] = new_func;
        return new_func;
    }

    /// @brief 返回function列表
    /// @return function列表
    std::vector<CFG_function *> getFunctions()
    {
        return functions;
    }

    /// @brief 返回符号表
    /// @return 符号表symtab
    Module * getSymtab()
    {
        return symtab;
    }

    /// @brief 设置当前function
    /// @param function 变更的函数
    /// @return
    void setCurrentFunction(CFG_function * function)
    {
        currentFunction = function;
    }

    /// @brief 获取当前函数
    /// @param
    /// @return 指向当前函数的指针
    CFG_function * getCurrentFunction()
    {
        return currentFunction;
    }

    /// @brief 运行产生CFG
    /// @param print_flag true:生成并打印;false:只生成CFG
    /// @return 翻译是否成功，true：成功，false：失败
    bool run(bool print_flag);

protected:
    /// @brief 识别到函数定义语句
    /// @param ir_inst ir语句
    /// @return 翻译是否成功，true：成功，false：失败
    bool label_inst(Instruction * ir_inst);

    /// @brief 识别到跳转
    /// @param ir_inst ir语句
    /// @return 翻译是否成功，true：成功，false：失败
    bool goto_inst(Instruction * ir_inst);

    /// @brief 识别到其他语句
    /// @param ir_inst ir语句
    /// @return 翻译是否成功，true：成功，false：失败
    bool default_expr_inst(Instruction * ir_inst);
};

#endif // CFG_H
