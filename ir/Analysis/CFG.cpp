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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <gvc.h>
#include <filesystem>
#include "CFG.h"

/// @brief 识别到label语句
/// @param ir_inst ir语句
/// @return 翻译是否成功，true：成功，false：失败
bool CFG_Generator::label_inst(Instruction * ir_inst)
{

    //取出label的名字
    //去除label name中的第一个字符"."和最后的":""
    auto label_name = ir_inst->getLabelName();

    //同时还需要检查当前的block是否已经有出口。
    //没有出口代表平滑流入新的block，设置出口
    if (getCurrentFunction()->currentBlock != nullptr) {
        if (getCurrentFunction()->currentBlock->exits.empty()) {
            getCurrentFunction()->currentBlock->exits.push_back(label_name);
        }
    }

    //新建并更换当前function的block
    //并把label作为当前block的唯一索引，添加到block入口中
    auto new_block = getCurrentFunction()->newBlock();
    getCurrentFunction()->addLabel2Block(label_name, new_block);
    getCurrentFunction()->currentBlock = new_block;

    // label塞入当前块内
    getCurrentFunction()->currentBlock->irInstructions.push_back(ir_inst);

    return true;
}

/// @brief 识别到跳转
/// @param ir_inst ir语句
/// @return 翻译是否成功，true：成功，false：失败
bool CFG_Generator::goto_inst(Instruction * ir_inst)
{
    // 跳转指令也去掉'\t'后塞入当前块内
    getCurrentFunction()->currentBlock->irInstructions.push_back(ir_inst);

    GotoInstruction * gotoInst = dynamic_cast<GotoInstruction *>(ir_inst);
    // 区分 br 与 bc

    if (gotoInst->getTrueLabel() == gotoInst->getFalseLabel()) {
        // br，只添加一个出口

        auto label_name = gotoInst->getTrueLabel()->getLabelName();
        getCurrentFunction()->currentBlock->exits.push_back(label_name);
    }

    else if (gotoInst->getTrueLabel() != gotoInst->getFalseLabel()) {
        // bc，添加两个出口

        auto label_name1 = gotoInst->getTrueLabel()->getLabelName();
        getCurrentFunction()->currentBlock->exits.push_back(label_name1);

        //去除label name中的第一个字符"."后，放进block中
        auto label_name2 = gotoInst->getFalseLabel()->getLabelName();
        getCurrentFunction()->currentBlock->exits.push_back(label_name2);
    }

    else {
        // 取出第一个单词失败
        return false;
    }
    return true;
}

/// @brief 识别到其他语句
/// @param ir_inst ir语句
/// @return 翻译是否成功，true：成功，false：失败
bool CFG_Generator::default_expr_inst(Instruction * ir_inst)
{
    // 这里是对第二种情况的处理逻辑
    // 去除'\t'后塞入到当前function的当前block里
    getCurrentFunction()->currentBlock->irInstructions.push_back(ir_inst);

    return true;
}

/// @brief CFG代码块合并，合并前缀和后缀为1的block
void CFG_Generator::block_merge()
{
    // 逐个函数处理
    for (CFG_function * cfg_func : functions) {
		std::unordered_map<std::string, bool> del_block;

		// 注意：可能在循环里删除 block，因此用索引而非 range-for
		for (std::size_t i = 0; i < cfg_func->blocks.size(); ++i) {
			CFG_block * cfg_block = cfg_func->blocks[i];

            bool changed = false;

			do {
				// to_block是决定要不要删除的，cfg_block是to_block的前一个，是一定会保留的
                changed = false;

				if (cfg_block->exits.size() != 1)
                    break; // 最后一个了

                const std::string exit_label = cfg_block->exits[0];
                auto target_it = cfg_func->blockMap.find(exit_label);
                if (target_it == cfg_func->blockMap.end())
                    break; // 不在同一函数里，跳过

                CFG_block * to_block = target_it->second;
                if (cfg_block == to_block)
                    break; // 自环，不合并

                // 只处理 单入口和出口 的基本块
                if (to_block->prepos_entries.size() != 1 || to_block->blk_label.size() != 1)
                    break;

                const std::string now_blk_label = cfg_block->blk_label[0];
                if (del_block.find(now_blk_label) != del_block.end())
                    break; // 已经标记为删除，跳过

                // 指令迁移
                cfg_block->irInstructions.pop_back();
                cfg_block->irInstructions.insert(cfg_block->irInstructions.begin(),
                                                to_block->irInstructions.begin() + 1,
                                                to_block->irInstructions.end());

                // 出口标签迁移
                cfg_block->exits = to_block->exits;

                // // 更新所有后驱的入口
                // for (std::string & lbl : to_block->exits)
                // {
                // 	auto next_it = cfg_func->blockMap.find(lbl);
                // 	CFG_block * next_block = next_it->second;
                // 	next_block->blk_label = to_block->blk_label;
                // }

                // 记录需要删除的冗余块
                del_block[to_block->blk_label[0]] = true;
                changed = true;
            } while (changed == true);
        }

        // 删除标记的冗余块
		for (const auto & del_blk : del_block) {
			const std::string & del_blk_label = del_blk.first;
			auto it = cfg_func->blockMap.find(del_blk_label);
			if (it != cfg_func->blockMap.end()) {
				CFG_block * block_to_delete = it->second;
				cfg_func->blocks.erase(std::remove(cfg_func->blocks.begin(), cfg_func->blocks.end(), block_to_delete), cfg_func->blocks.end());
				cfg_func->blockMap.erase(del_blk_label);
				delete block_to_delete;
			}
		}
    }
}

void CFG_Generator::add_prepose_entries2Block()
{
	for (CFG_function * cfg_func : this->functions) {
		for (CFG_block * cfg_block : cfg_func->blocks) {
			for (const std::string & exit_label : cfg_block->exits) {
				auto it = cfg_func->blockMap.find(exit_label);
				if (it != cfg_func->blockMap.end()) {
					CFG_block * to_block = it->second;
					to_block->prepos_entries.push_back(cfg_block->blk_label[0]);
				}
			}
		}
	}
}

/// @brief 运行产生CFG
/// @param print_flag true:生成并打印;false:只生成CFG
/// @return 翻译是否成功，true：成功，false：失败
bool CFG_Generator::run(bool print_flag)
{
    //遍历每个function
    for (auto ir_func: symtab->getFunctionList()) {
		if (ir_func->isBuiltin())
            continue;
        // 新建并更换当前的fuction
        // auto func = newFunction(ir_func->getName());
        std::string fname = ir_func->getName();
		auto func = newFunction(fname);
        setCurrentFunction(func);
        currentFunction->name = ir_func->getName();

        //遍历ir
        for (auto ir: ir_func->getInterCode().getInsts()) {
            if (ir->getOp() == IRInstOperator::IRINST_OP_GOTO) {
                //跳转指令
                goto_inst(ir);
            } else if (ir->getOp() == IRInstOperator::IRINST_OP_LABEL || ir->getOp() == IRInstOperator::IRINST_OP_ENTRY) {
                // label
                label_inst(ir);
            } else {
                //其他指令均塞进去
                default_expr_inst(ir);
            }
        }
    }

	add_prepose_entries2Block();

    block_merge();

    //下面遍历func和func中的block，生成CFG
    //遍历函数
    for (auto cfg_func: functions) {
        // 创建一个Graphviz上下文
        GVC_t * gvc = gvContext();

        // 创建一个空的图
        // Agraph_t * g = agopen("g", Agdirected, nullptr);
		Agraph_t *g = agopen(const_cast<char*>("g"), Agdirected, nullptr);

        //遍历block，创建所有node
        for (auto cfg_block: cfg_func->blocks) {
            //创建节点
            // Agnode_t * n1 = agnode(g, cfg_block->blk_label[0].data(), 1);
			Agnode_t *n1 = agnode(g, const_cast<char*>(cfg_block->blk_label[0].c_str()), 1);
            std::string all_ir_str;
            //把ir添加进去
            for (const auto & ir: cfg_block->irInstructions) {
                std::string ir_str;
                ir->toString(ir_str);
                all_ir_str = all_ir_str + ir_str + "\n";
            }
            // agsafeset(n1, "shape", "box", "");
            // agsafeset(n1, "label", all_ir_str.data(), "");
			agsafeset(n1, const_cast<char*>("shape"), const_cast<char*>("box"), const_cast<char*>(""));
			agsafeset(n1, const_cast<char*>("label"), const_cast<char*>(all_ir_str.c_str()), const_cast<char*>(""));
            cfg_func->addCFGnode(cfg_block, n1);
        }

        //遍历当前函数的所有block，创建所有edge
        for (auto cfg_block1: cfg_func->blocks) {
            //创建边
            auto from_node = cfg_func->nodeMap[cfg_block1];
            for (const auto & exit_label: cfg_block1->exits) {
                auto to_block = cfg_func->blockMap[exit_label];
                if (to_block != nullptr) {
                    auto to_node = cfg_func->nodeMap[to_block];
                    agedge(g, from_node, to_node, nullptr, 1);
                }
            }
        }
        //输出图片；每一个函数输出一张图
        // 设置布局
        gvLayout(gvc, g, "dot");
        // 设置输出格式
        std::string dest_directory = "./CFG/"; //输出文件夹
        std::string outputFormat = "png";      //输出格式
        std::string outputFile = dest_directory + cfg_func->name + ".png";

        // 检查文件夹是否存在
        if (!std::filesystem::exists(dest_directory)) {
            // 如果文件夹不存在，则创建文件夹
            std::filesystem::create_directories(dest_directory);
        }

        if (print_flag) {
            // 渲染图并输出到文件
            FILE * fp = fopen(outputFile.c_str(), "w");
            gvRender(gvc, g, outputFormat.c_str(), fp);
            fclose(fp);
        }

        // 释放资源
        gvFreeLayout(gvc, g);
        agclose(g);
        gvFreeContext(gvc);
    }

    return true;
}
