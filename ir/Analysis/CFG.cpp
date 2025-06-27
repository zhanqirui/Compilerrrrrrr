#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
// #include <gvc.h>
#include <filesystem>
#include "CFG.h"
#include "BranchifCondition.h"
#include <set>
#include <iomanip>
#include <unordered_map>

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

  /// @brief 识别到跳转
 /// @param ir_inst ir语句
 /// @return 翻译是否成功，true：成功，false：失败
 bool CFG_Generator::branch_inst(Instruction * ir_inst)
 {
	 // 跳转指令也去掉'\t'后塞入当前块内
	 getCurrentFunction()->currentBlock->irInstructions.push_back(ir_inst);

	 BranchifCondition * gotoInst = dynamic_cast<BranchifCondition *>(ir_inst);
	 // 区分 br 与 bc

	 if (gotoInst->getTrueTarget() == gotoInst->getFalseTarget()) {
		 // br，只添加一个出口

		 auto label_name = gotoInst->getTrueTarget()->getLabelName();
		 getCurrentFunction()->currentBlock->exits.push_back(label_name);
	 }

	 else if (gotoInst->getTrueTarget() != gotoInst->getFalseTarget()) {
		 // bc，添加两个出口

		 auto label_name1 = gotoInst->getTrueTarget()->getLabelName();
		 getCurrentFunction()->currentBlock->exits.push_back(label_name1);

		 //去除label name中的第一个字符"."后，放进block中
		 auto label_name2 = gotoInst->getFalseTarget()->getLabelName();
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

				 // 新增：如果 to_block 除了 label 还有其它指令，不合并
				 if (to_block->irInstructions.size() > 1)
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
 
 // 活性分析辅助函数：获取指令的use和def集合
 static void getInstUseDef(Instruction* inst, std::set<std::string>& use, std::set<std::string>& def) {
	// 针对跳转指令特殊处理，不把label作为变量
	if (inst->getOp() == IRInstOperator::IRINST_OP_BRANCH_I) {
		// 只收集条件表达式中的变量（如条件跳转的条件变量），不收集label
		auto condVars = inst->getOperand(0); 
		if(condVars)
			use.insert(condVars->getIRName());
		// 跳转指令一般没有def
		return;
	}
	// 其它指令，正常收集
	auto useVars = inst->getUseVars();
	auto defVars = inst->getDefVars();
	use.insert(useVars.begin(), useVars.end());
	def.insert(defVars.begin(), defVars.end());
}

 // CFG_function::livenessAnalysis
 void CFG_function::livenessAnalysis() {
	// 1. 初始化每个block的use/def集合
	for (auto block : blocks) {
		block->use.clear();
		block->def.clear();
		block->live_in.clear();
		block->live_out.clear();
		std::set<std::string> cur_def;
		for (auto inst : block->irInstructions) {
			std::set<std::string> use, def;
			getInstUseDef(inst, use, def);
			for (const auto& v : use) {
				if (cur_def.find(v) == cur_def.end())
					block->use.insert(v);
			}
			for (const auto& v : def) {
				block->def.insert(v);
				cur_def.insert(v);
			}
		}
	}

	// 2. 迭代求解in/out集合
	bool changed;
	do {
		changed = false;
		for (auto block : blocks) {
			std::set<std::string> old_in = block->live_in;
			std::set<std::string> old_out = block->live_out;

			// out[B] = 并集所有后继的in
			block->live_out.clear();
			for (const auto& exit_label : block->exits) {
				auto it = blockMap.find(exit_label);
				if (it != blockMap.end()) {
					CFG_block* succ = it->second;
					block->live_out.insert(succ->live_in.begin(), succ->live_in.end());
				}
			}
			// in[B] = use[B] ∪ (out[B] - def[B])
			block->live_in = block->use;
			for (const auto& v : block->live_out) {
				if (block->def.find(v) == block->def.end())
					block->live_in.insert(v);
			}

			if (block->live_in != old_in || block->live_out != old_out)
				changed = true;
		}
	} while (changed);
}

// CFG_function::debugLiveness
void CFG_function::debugLiveness(std::ostream& os) {
	os << "==== Liveness Analysis for function: " << name << " ====\n";
	for (size_t i = 0; i < blocks.size(); ++i) {
		auto block = blocks[i];
		os << "Block " << (block->blk_label.empty() ? std::to_string(i) : block->blk_label[0]) << ":\n";
		os << "  use: ";
		for (const auto& v : block->use) os << v << " ";
		os << "\n  def: ";
		for (const auto& v : block->def) os << v << " ";
		os << "\n  live_in: ";
		for (const auto& v : block->live_in) os << v << " ";
		os << "\n  live_out: ";
		for (const auto& v : block->live_out) os << v << " ";
		os << "\n";
	}
	os << "========================================\n";
}

// 新增：CFG_function::debugLiveIntervals
void CFG_function::debugLiveIntervals(std::ostream& os) {
	os << "==== LiveIntervals for function: " << name << " ====\n";
	for (const auto& kv : name2value) {
		const std::string& var = kv.first;
		Value* val = kv.second;
		if (val && val->live_begin != -1 && val->live_end != -1) {
			os << "  " << var << ": [" << val->live_begin << ", " << val->live_end << "]\n";
		}
	}
	os << "========================================\n";
}

// CFG_Generator::runLivenessAnalysis
void CFG_Generator::runLivenessAnalysis() {
	for (auto func : functions) {
		func->livenessAnalysis();
	}
}

// CFG_Generator::debugLiveness
void CFG_Generator::debugLiveness(std::ostream& os) {
	for (auto func : functions) {
		func->debugLiveness(os);
	}
 }

 /// @brief 死代码块删除 - 删除永远不会被执行的基本块
/// @details 该函数通过可达性分析识别从函数入口可达的所有基本块，
///          然后删除那些不可达的死代码块。死代码块通常是由于：
///          1. 无条件跳转后的代码
///          2. 条件永远为假的分支
///          3. 孤立的代码块（没有任何入口）
void CFG_Generator::deadCodeElimination()
{
    // 逐个函数处理
    for (CFG_function * cfg_func : functions) {
        std::set<CFG_block*> reachable_blocks;
        std::vector<CFG_block*> worklist;
        
        // 如果函数没有基本块，跳过
        if (cfg_func->blocks.empty()) {
            continue;
        }
        
        // 从函数入口开始（第一个块作为入口）
        CFG_block* entry_block = cfg_func->blocks[0];
        reachable_blocks.insert(entry_block);
        worklist.push_back(entry_block);
        
        // 使用工作列表算法进行可达性分析
        while (!worklist.empty()) {
            CFG_block* current_block = worklist.back();
            worklist.pop_back();
            
            // 遍历当前块的所有出口
            for (const std::string& exit_label : current_block->exits) {
                auto it = cfg_func->blockMap.find(exit_label);
                if (it != cfg_func->blockMap.end()) {
                    CFG_block* successor = it->second;
                    // 如果后继块未被访问过，标记为可达并加入工作列表
                    if (reachable_blocks.find(successor) == reachable_blocks.end()) {
                        reachable_blocks.insert(successor);
                        worklist.push_back(successor);
                    }
                }
            }
        }
        
        // 收集不可达的死代码块
        std::vector<CFG_block*> dead_blocks;
        for (CFG_block* block : cfg_func->blocks) {
            if (reachable_blocks.find(block) == reachable_blocks.end()) {
                dead_blocks.push_back(block);
            }
        }
        
        // 记录删除的死代码块信息（用于调试）
        cfg_func->dead_blocks_info.clear();
        for (CFG_block* dead_block : dead_blocks) {
            DeadBlockInfo info;
            info.block_label = dead_block->blk_label.empty() ? "anonymous" : dead_block->blk_label[0];
            info.instruction_count = dead_block->irInstructions.size();
            // 收集指令信息
            for (Instruction* inst : dead_block->irInstructions) {
                std::string inst_str;
                inst->toString(inst_str);
                info.instructions.push_back(inst_str);
            }
            cfg_func->dead_blocks_info.push_back(info);
        }
        
        // 删除死代码块
        for (CFG_block* dead_block : dead_blocks) {
            // 从blocks向量中移除
            auto block_it = std::find(cfg_func->blocks.begin(), cfg_func->blocks.end(), dead_block);
            if (block_it != cfg_func->blocks.end()) {
                cfg_func->blocks.erase(block_it);
            }
            
            // 从blockMap中移除所有相关标签
            for (const std::string& label : dead_block->blk_label) {
                cfg_func->blockMap.erase(label);
            }
            
            // 释放内存
            delete dead_block;
        }
        
        // 清理其他活跃块中指向已删除块的出口引用
        for (CFG_block* block : cfg_func->blocks) {
            auto it = block->exits.begin();
            while (it != block->exits.end()) {
                if (cfg_func->blockMap.find(*it) == cfg_func->blockMap.end()) {
                    // 该出口指向的块已被删除，移除该出口
                    it = block->exits.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
}

/// @brief 调试死代码删除 - 显示被删除的死代码块信息
/// @param os 输出流
/// @details 该函数显示在死代码删除过程中被移除的基本块的详细信息，
///          包括块标签、指令数量和具体的指令内容，帮助开发者了解
///          哪些代码被识别为死代码并被删除。
void CFG_Generator::debugDeadCodeElimination(std::ostream& os) {
    os << "==== Dead Code Elimination Results ====\n";
    
    for (CFG_function* cfg_func : functions) {
        os << "Function: " << cfg_func->name << "\n";
        
        // 新增：显示可达性分析的详细信息
        os << "  Reachability Analysis:\n";
        if (!cfg_func->blocks.empty()) {
            os << "    Entry block: " << (cfg_func->blocks[0]->blk_label.empty() ? 
                                        "anonymous" : cfg_func->blocks[0]->blk_label[0]) << "\n";
            
            // 显示所有基本块的可达性
            std::set<CFG_block*> reachable_blocks;
            std::vector<CFG_block*> worklist;
            
            CFG_block* entry_block = cfg_func->blocks[0];
            reachable_blocks.insert(entry_block);
            worklist.push_back(entry_block);
            
            while (!worklist.empty()) {
                CFG_block* current_block = worklist.back();
                worklist.pop_back();
                
                for (const std::string& exit_label : current_block->exits) {
                    auto it = cfg_func->blockMap.find(exit_label);
                    if (it != cfg_func->blockMap.end()) {
                        CFG_block* successor = it->second;
                        if (reachable_blocks.find(successor) == reachable_blocks.end()) {
                            reachable_blocks.insert(successor);
                            worklist.push_back(successor);
                        }
                    }
                }
            }
            
            os << "    Reachable blocks: " << reachable_blocks.size() << "/" << cfg_func->blocks.size() << "\n";
            for (CFG_block* block : cfg_func->blocks) {
                std::string block_name = block->blk_label.empty() ? "anonymous" : block->blk_label[0];
                bool is_reachable = (reachable_blocks.find(block) != reachable_blocks.end());
                os << "      " << block_name << ": " << (is_reachable ? "REACHABLE" : "UNREACHABLE") << "\n";
            }
        }
        
        if (cfg_func->dead_blocks_info.empty()) {
            os << "  No dead code blocks found.\n";
        } else {
            os << "  Dead code blocks eliminated: " << cfg_func->dead_blocks_info.size() << "\n";
            
            for (size_t i = 0; i < cfg_func->dead_blocks_info.size(); ++i) {
                const DeadBlockInfo& info = cfg_func->dead_blocks_info[i];
                os << "  Block " << (i + 1) << " [Label: " << info.block_label 
                   << ", Instructions: " << info.instruction_count << "]:\n";
                
                for (const std::string& inst : info.instructions) {
                    os << "    " << inst;
                    if (inst.back() != '\n') os << "\n";
                }
                os << "\n";
            }
        }
        
        os << "  Remaining blocks: " << cfg_func->blocks.size() << "\n";
        os << "----------------------------------------\n";
    }
    
    os << "========================================\n";
}

/// @brief 调试CFG结构 - 显示当前CFG的基本块结构信息
/// @param os 输出流
/// @details 该函数显示CFG中所有基本块的结构信息，包括：
///          - 基本块标签和ID
///          - 前驱和后继关系
///          - 基本块中的指令数量
///          这有助于验证CFG构建和优化的正确性。
void CFG_Generator::debugCFGStructure(std::ostream& os) {
    os << "==== CFG Structure Information ====\n";
    
    for (CFG_function* cfg_func : functions) {
        os << "Function: " << cfg_func->name << "\n";
        os << "Total blocks: " << cfg_func->blocks.size() << "\n\n";
        
        for (size_t i = 0; i < cfg_func->blocks.size(); ++i) {
            CFG_block* block = cfg_func->blocks[i];
            std::string block_id = block->blk_label.empty() ? 
                                   ("Block_" + std::to_string(i)) : 
                                   block->blk_label[0];
            
            os << "  " << block_id << ":\n";
            os << "    Instructions: " << block->irInstructions.size() << "\n";
            
            // 显示前驱
            os << "    Predecessors: ";
            if (block->prepos_entries.empty()) {
                os << "none";
            } else {
                for (size_t j = 0; j < block->prepos_entries.size(); ++j) {
                    if (j > 0) os << ", ";
                    os << block->prepos_entries[j];
                }
            }
            os << "\n";
            
            // 显示后继
            os << "    Successors: ";
            if (block->exits.empty()) {
                os << "none (exit block)";
            } else {
                for (size_t j = 0; j < block->exits.size(); ++j) {
                    if (j > 0) os << ", ";
                    os << block->exits[j];
                }
            }
            os << "\n\n";
        }
        
        os << "----------------------------------------\n";
    }
    
    os << "========================================\n";
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

		// 新增：收集变量名到Value*的映射
		func->name2value.clear();

		auto global_vars = symtab->getGlobalVariables();
		for (auto * var: global_vars) {
			std::string varName = var->getIRName();
			func->name2value[varName] = var;
		}

		auto vars = ir_func->getVarValues();
		// 把函数内的变量塞到当前function的name2value中
		for (auto * var: vars) {
			if (var->getIRName().empty()) continue; // 忽略匿名变量
			std::string varName = var->getIRName();
			func->name2value[varName] = var;
		}

		for (auto* v : ir_func->getInterCode().getInsts()) { // 假设IRFunction有getValueList()，否则请用你自己的变量遍历方式
		if(v -> hasResultValue())
		{
			std::string varName = v->getIRName();
			if (!varName.empty()) {
				func->name2value[varName] = v;
			}
		}
		}

		 //遍历ir
		for (auto ir: ir_func->getInterCode().getInsts()) {
			if (ir->getOp() == IRInstOperator::IRINST_OP_GOTO ) {
				//跳转指令
				goto_inst(ir);
			}
			else if(ir->getOp() == IRInstOperator::IRINST_OP_BRANCH_I) {
				//分支指令
				branch_inst(ir);
			}
			else if (ir->getOp() == IRInstOperator::IRINST_OP_LABEL || ir->getOp() == IRInstOperator::IRINST_OP_ENTRY) {
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

	 // 新增：执行死代码删除
	 deadCodeElimination();

	 //下面遍历func和func中的block，生成CFG
	 //遍历函数
	 for (auto cfg_func: functions) {
		 // 创建一个Graphviz上下文
		 // GVC_t * gvc = gvContext();

		 // 创建一个空的图
		 // Agraph_t * g = agopen("g", Agdirected, nullptr);
		 // Agraph_t *g = agopen(const_cast<char*>("g"), Agdirected, nullptr);

		 //遍历block，创建所有node
		 // for (auto cfg_block: cfg_func->blocks) {
		 // 	 //创建节点
		 // 	 // Agnode_t * n1 = agnode(g, cfg_block->blk_label[0].data(), 1);
		 // 	 Agnode_t *n1 = agnode(g, const_cast<char*>(cfg_block->blk_label[0].c_str()), 1);
		 // 	 std::string all_ir_str;
		 // 	 //把ir添加进去
		 // 	 for (const auto & ir: cfg_block->irInstructions) {
		 // 		 std::string ir_str;
		 // 		 ir->toString(ir_str);
		 // 		 all_ir_str = all_ir_str + ir_str + "\n";
		 // 	 }
		 // 	 // agsafeset(n1, "shape", "box", "");
		 // 	 // agsafeset(n1, "label", all_ir_str.data(), "");
		 // 	 agsafeset(n1, const_cast<char*>("shape"), const_cast<char*>("box"), const_cast<char*>(""));
		 // 	 agsafeset(n1, const_cast<char*>("label"), const_cast<char*>(all_ir_str.c_str()), const_cast<char*>(""));
		 // 	 cfg_func->addCFGnode(cfg_block, n1);
		 // }

		 //遍历当前函数的所有block，创建所有edge
		 // for (auto cfg_block1: cfg_func->blocks) {
		 // 	 //创建边
		 // 	 auto from_node = cfg_func->nodeMap[cfg_block1];
		 // 	 for (const auto & exit_label: cfg_block1->exits) {
		 // 		 auto to_block = cfg_func->blockMap[exit_label];
		 // 		 if (to_block != nullptr) {
		 // 			 auto to_node = cfg_func->nodeMap[to_block];
		 // 			 agedge(g, from_node, to_node, nullptr, 1);
		 // 		 }
		 // 	 }
		 // }
		 //输出图片；每一个函数输出一张图
		 // 设置布局
		 // gvLayout(gvc, g, "dot");
		 // 设置输出格式
		 // std::string dest_directory = "./CFG/"; //输出文件夹
		 // std::string outputFormat = "png";      //输出格式
		 // std::string outputFile = dest_directory + cfg_func->name + ".png";

		 // 检查文件夹是否存在
		 // if (!std::filesystem::exists(dest_directory)) {
		 // 	 // 如果文件夹不存在，则创建文件夹
		 // 	 std::filesystem::create_directories(dest_directory);
		 // }

		 // if (print_flag) {
		 // 	 // 渲染图并输出到文件
		 // 	 FILE * fp = fopen(outputFile.c_str(), "w");
		 // 	 gvRender(gvc, g, outputFormat.c_str(), fp);
		 // 	 fclose(fp);
		 // }

		 // 释放资源
		 // gvFreeLayout(gvc, g);
		 // agclose(g);
		 // gvFreeContext(gvc);
	 }

	 return true;
 }

void CFG_function::computeLiveIntervals() {
	liveIntervals.clear();
	// 指令编号递增
	int idx = 0;
	for (auto block : blocks) {
		for (auto inst : block->irInstructions) {
			std::set<std::string> use, def;
			getInstUseDef(inst, use, def);
			for (const auto& vname : use) {
				auto it = name2value.find(vname);
				if (it != name2value.end() && it->second) {
					Value* val = it->second;
					if (val->live_begin == -1) val->live_begin = idx;
					val->live_end = idx;
				}
			}
			for (const auto& vname : def) {
				auto it = name2value.find(vname);
				if (it != name2value.end() && it->second) {
					Value* val = it->second;
					if (val->live_begin == -1) val->live_begin = idx;
					val->live_end = idx;
				}
			}
			++idx;
		}
	}
}

std::vector<LiveInterval> CFG_function::getAllLiveIntervals() const {
	std::vector<LiveInterval> res;
	for (const auto& kv : liveIntervals) {
		res.push_back(kv.second);
	}
	return res;
}