/**
 * @file DFG.cpp
 * @brief 仅支持Arm64指令选择器注册的IRINST_OP的数据流图分析实现，保留高级分析
 */

#include "Analysis/DFG.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>

/**
 * @brief DFG_Node构造函数
 * 
 * @param _inst 指令
 */
DFG_Node::DFG_Node(Instruction * _inst)
    : inst(_inst), is_load(false), is_store(false), mem_addr(nullptr), mem_value(nullptr)
{
    // 检查是否是load/store指令并设置相关标志
    IRInstOperator op = inst->getOp();
    is_load = (op == IRInstOperator::IRINST_OP_LOAD);
    is_store = (op == IRInstOperator::IRINST_OP_STORE);
    
    // 记录内存访问信息
    if (is_load && inst->getOperandsNum() >= 1) {
        mem_addr = inst->getOperand(0); // load指令的地址操作数
        mem_value = inst; // load指令的结果就是从内存中加载的值
    } else if (is_store && inst->getOperandsNum() >= 2) {
        mem_value = inst->getOperand(1); // store指令的值操作数
        mem_addr = inst->getOperand(0);  // store指令的地址操作数
    }
}

/**
 * @brief 获取节点标签(用于可视化)
 * 
 * @return std::string 
 */
std::string DFG_Node::getLabel() const {
    std::string label;
    inst->toString(label);
    
    // 添加额外的内存访问信息
    if (is_load) {
        label += "\n[LOAD]";
    } else if (is_store) {
        label += "\n[STORE]";
    }
    
    return label;
}

/**
 * @brief DFG_Function析构函数
 */
DFG_Function::~DFG_Function() {
    for (auto node : nodes) {
        delete node;
    }
    nodes.clear();
    instToNode.clear();
    memoryReads.clear();
    memoryWrites.clear();
}

/**
 * @brief 添加节点
 * 
 * @param inst 指令
 * @return DFG_Node* 
 */
DFG_Node* DFG_Function::addNode(Instruction* inst) {
    auto it = instToNode.find(inst);
    if (it != instToNode.end()) {
        return it->second;
    }

    DFG_Node* node = new DFG_Node(inst);
    nodes.push_back(node);
    instToNode[inst] = node;
    
    // 如果是内存访问指令，更新内存访问映射
    if (node->is_load && node->mem_addr) {
        memoryReads[node->mem_addr].push_back(node);
    } else if (node->is_store && node->mem_addr) {
        memoryWrites[node->mem_addr].push_back(node);
    }
    
    return node;
}

/**
 * @brief 添加边
 * 
 * @param src 源节点
 * @param dst 目标节点
 * @param type 依赖类型
 */
void DFG_Function::addEdge(DFG_Node* src, DFG_Node* dst, DependencyType type) {
    // 检查边是否已存在
    DFG_Node::Edge new_edge(dst, type);
    if (std::find_if(src->outputs.begin(), src->outputs.end(), 
                    [&](const DFG_Node::Edge& e) { return e.node == dst && e.type == type; }) 
        != src->outputs.end()) {
        return; // 边已存在，不重复添加
    }

    // 添加边
    src->outputs.push_back(DFG_Node::Edge(dst, type));
    dst->inputs.push_back(DFG_Node::Edge(src, type));
}

/**
 * @brief 分析函数中的内存访问
 */
void DFG_Function::analyzeMemoryAccesses() {
    // 这个函数在buildFunctionDFG中通过addNode自动维护了memoryReads和memoryWrites
    // 如果未来需要更复杂的内存访问分析，可以在这里添加
}

/**
 * @brief DFG_Generator析构函数
 */
DFG_Generator::~DFG_Generator() {
    for (auto func : functions) {
        delete func;
    }
    functions.clear();
    funcMap.clear();
}

/**
 * @brief 根据函数名获取DFG
 * 
 * @param name 函数名
 * @return DFG_Function* 
 */
DFG_Function* DFG_Generator::getFunction(const std::string& name) const {
    auto it = funcMap.find(name);
    if (it != funcMap.end()) {
        return it->second;
    }
    return nullptr;
}

/**
 * @brief 为单个函数构建DFG
 * 
 * @param func IR函数
 * @return DFG_Function* 
 */
DFG_Function* DFG_Generator::buildFunctionDFG(Function* func) {
    if (!func) return nullptr;

    // 创建函数DFG
    DFG_Function* dfg_func = new DFG_Function(func->getName());
    
    // 遍历所有指令，创建DFG节点
    for (auto inst : func->getInterCode().getInsts()) {
        // 跳过标签指令和入口指令
        if (inst->getOp() == IRInstOperator::IRINST_OP_LABEL || 
			inst->getOp() == IRInstOperator::IRINST_OP_ENTRY || 
			inst->getOp() == IRInstOperator::IRINST_OP_GOTO  ||
			inst->getOp() == IRInstOperator::IRINST_OP_ARG ){
			continue;  // 跳过标签和分支指令
		}
        
        // 为指令创建节点
        dfg_func->addNode(inst);
    }
    
    // 分析函数中的内存访问
    dfg_func->analyzeMemoryAccesses();
    
    return dfg_func;
}

/**
 * @brief 添加寄存器依赖边 (SSA形式的数据依赖)
 * 
 * @param dfg_func 函数DFG
 * @param ir_func IR函数
 */
void DFG_Generator::addRegisterDependencyEdges(DFG_Function* dfg_func, Function* ir_func) {
    // 创建值到定义它的指令的映射
    std::unordered_map<Value*, DFG_Node*> valueDefs;
    
    // 第一遍：收集所有指令定义的值
    for (auto inst : ir_func->getInterCode().getInsts()) {
        if (inst->getOp() == IRInstOperator::IRINST_OP_LABEL || 
			inst->getOp() == IRInstOperator::IRINST_OP_ENTRY || 
			inst->getOp() == IRInstOperator::IRINST_OP_GOTO  ||
			inst->getOp() == IRInstOperator::IRINST_OP_ARG) {
			continue;  // 跳过标签和分支指令
		}
        
        auto node_it = dfg_func->instToNode.find(inst);
        if (node_it == dfg_func->instToNode.end()) continue;
        
        // 如果指令定义了一个值，记录下来
        if (inst->hasResultValue()) {
            valueDefs[inst] = node_it->second;
        }
    }
    
    // 第二遍：为每条指令添加寄存器依赖边
    for (auto inst : ir_func->getInterCode().getInsts()) {
        if (inst->getOp() == IRInstOperator::IRINST_OP_LABEL || 
			inst->getOp() == IRInstOperator::IRINST_OP_ENTRY || 
			inst->getOp() == IRInstOperator::IRINST_OP_GOTO  ||
			inst->getOp() == IRInstOperator::IRINST_OP_ARG) {
			continue;  // 跳过标签和分支指令
		}
        
        auto dst_it = dfg_func->instToNode.find(inst);
        if (dst_it == dfg_func->instToNode.end()) continue;
        
        DFG_Node* dst_node = dst_it->second;
        
        // 获取指令的操作数
        for (unsigned i = 0; i < inst->getOperandsNum(); i++) {
            Value* operand = inst->getOperand(i);
            if (!operand) continue;
            
            // 如果操作数是由指令定义的，添加RAW依赖边
            auto def_it = valueDefs.find(operand);
            if (def_it != valueDefs.end()) {
                DFG_Node* src_node = def_it->second;
                if (src_node) {
                    dfg_func->addEdge(src_node, dst_node, DependencyType::RAW);
                }
            }
        }
    }
}

/**
 * @brief 添加内存依赖边 (Load/Store之间的依赖)
 * 
 * @param dfg_func 函数DFG
 */
void DFG_Generator::addMemoryDependencyEdges(DFG_Function* dfg_func) {
    // 处理每个内存地址
    for (const auto& entry : dfg_func->memoryWrites) {
        Value* addr = entry.first;
        const auto& writes = entry.second;
        
        // 查找同一地址的读操作
        auto read_it = dfg_func->memoryReads.find(addr);
        if (read_it != dfg_func->memoryReads.end()) {
            const auto& reads = read_it->second;
            
            // 添加从写到读的依赖(RAW)
            for (auto write_node : writes) {
                for (auto read_node : reads) {
                    // 如果写操作在读操作之前，则存在RAW依赖
                    dfg_func->addEdge(write_node, read_node, DependencyType::MEMORY_RAW);
                }
            }
            
            // 添加从读到写的依赖(WAR)
            for (auto read_node : reads) {
                for (auto write_node : writes) {
                    // 如果读操作在写操作之前，则存在WAR依赖
                    dfg_func->addEdge(read_node, write_node, DependencyType::MEMORY_WAR);
                }
            }
        }
        
        // 添加写与写之间的依赖(WAW)
        for (size_t i = 0; i < writes.size(); ++i) {
            for (size_t j = i + 1; j < writes.size(); ++j) {
                dfg_func->addEdge(writes[i], writes[j], DependencyType::MEMORY_WAW);
            }
        }
    }
}


/**
 * @brief 获取边的颜色(用于可视化)
 * 
 * @param type 依赖类型
 * @return const char* 
 */
const char* DFG_Generator::getEdgeColorForDependency(DependencyType type) {
    switch (type) {
        case DependencyType::RAW:
            return "blue";
        case DependencyType::WAR:
            return "red";
        case DependencyType::WAW:
            return "orange";
        case DependencyType::MEMORY_RAW:
            return "darkblue";
        case DependencyType::MEMORY_WAR:
            return "darkred";
        case DependencyType::MEMORY_WAW:
            return "darkorange";
        default:
            return "black";
    }
}

/**
 * @brief 获取边的样式(用于可视化)
 * 
 * @param type 依赖类型
 * @return const char* 
 */
const char* DFG_Generator::getEdgeStyleForDependency(DependencyType type) {
    switch (type) {
        case DependencyType::RAW:
        case DependencyType::WAR:
        case DependencyType::WAW:
            return "solid";
        case DependencyType::MEMORY_RAW:
        case DependencyType::MEMORY_WAR:
        case DependencyType::MEMORY_WAW:
            return "dashed";
        case DependencyType::CONTROL:
            return "dotted";
        default:
            return "solid";
    }
}

/**
 * @brief 绘制DFG图
 * 
 * @param dfg_func 函数DFG
 * @param output_dir 输出目录
 */
void DFG_Generator::drawDFG(DFG_Function* dfg_func, const std::string& output_dir) {

//     if (!dfg_func) return;
//     
//     // 创建Graphviz上下文
//     GVC_t* gvc = gvContext();
//     
//     // 创建图
//     Agraph_t* g = agopen(const_cast<char*>(dfg_func->name.c_str()), Agdirected, nullptr);
//     
//     // 为每个DFG节点创建Graphviz节点
//     for (auto node : dfg_func->nodes) {
//         // 创建节点
//         std::string node_name = "inst_" + std::to_string(reinterpret_cast<uintptr_t>(node->inst));
//         Agnode_t* agnode_ptr = agnode(g, const_cast<char*>(node_name.c_str()), 1);
//         
//         // 设置节点标签和属性
//         std::string label = node->getLabel();
//         agsafeset(agnode_ptr, const_cast<char*>("label"), const_cast<char*>(label.c_str()), const_cast<char*>(""));
//         agsafeset(agnode_ptr, const_cast<char*>("shape"), const_cast<char*>("box"), const_cast<char*>(""));
//         
//         // 为不同类型的指令设置不同的颜色
//         if (node->is_load) {
//             agsafeset(agnode_ptr, const_cast<char*>("style"), const_cast<char*>("filled"), const_cast<char*>(""));
//             agsafeset(agnode_ptr, const_cast<char*>("fillcolor"), const_cast<char*>("lightblue"), const_cast<char*>(""));
//         } else if (node->is_store) {
//             agsafeset(agnode_ptr, const_cast<char*>("style"), const_cast<char*>("filled"), const_cast<char*>(""));
//             agsafeset(agnode_ptr, const_cast<char*>("fillcolor"), const_cast<char*>("lightpink"), const_cast<char*>(""));
//         }
//         
//         node->agnode = agnode_ptr;
//     }
//     
//     // 为每条数据依赖边创建Graphviz边
//     for (auto node : dfg_func->nodes) {
//         for (const auto& edge : node->outputs) {
//             Agedge_t* e = agedge(g, node->agnode, edge.node->agnode, nullptr, 1);
//             
//             // 设置边的属性(颜色、样式等)
//             agsafeset(e, const_cast<char*>("color"), 
//                      const_cast<char*>(getEdgeColorForDependency(edge.type)), 
//                      const_cast<char*>(""));
//             agsafeset(e, const_cast<char*>("style"), 
//                      const_cast<char*>(getEdgeStyleForDependency(edge.type)), 
//                      const_cast<char*>(""));
//             
//             // 添加边的标签(依赖类型)
//             std::string edge_label;
//             switch (edge.type) {
//                 case DependencyType::RAW: edge_label = "RAW"; break;
//                 case DependencyType::WAR: edge_label = "WAR"; break;
//                 case DependencyType::WAW: edge_label = "WAW"; break;
//                 case DependencyType::MEMORY_RAW: edge_label = "M-RAW"; break;
//                 case DependencyType::MEMORY_WAR: edge_label = "M-WAR"; break;
//                 case DependencyType::MEMORY_WAW: edge_label = "M-WAW"; break;
//                 case DependencyType::CONTROL: edge_label = "CTRL"; break;
//             }
//             agsafeset(e, const_cast<char*>("label"), 
//                      const_cast<char*>(edge_label.c_str()), 
//                      const_cast<char*>(""));
//         }
//     }
//     
//     // 确保输出目录存在
//     if (!std::filesystem::exists(output_dir)) {
//         std::filesystem::create_directories(output_dir);
//     }
//     
//     // 设置布局
//     gvLayout(gvc, g, "dot");
//     
//     // 生成输出文件
//     std::string output_file = output_dir + dfg_func->name + ".png";
//     FILE* fp = fopen(output_file.c_str(), "w");
//     if (fp) {
//         gvRender(gvc, g, "png", fp);
//         fclose(fp);
//         std::cout << "Generated DFG for function " << dfg_func->name << " at " << output_file << std::endl;
//     } else {
//         std::cerr << "Failed to create output file " << output_file << std::endl;
//     }
//     
//     // 清理资源
//     gvFreeLayout(gvc, g);
//     agclose(g);
//     gvFreeContext(gvc);
}

/**
 * @brief 运行DFG分析
 * 
 * @param draw_graph 是否绘制图形
 * @return true 
 * @return false 
 */
bool DFG_Generator::run(bool draw_graph) {
    if (!module) return false;
    
    // 遍历模块中的每个函数
    for (auto ir_func : module->getFunctionList()) {
        // 跳过内置函数
        if (ir_func->isBuiltin()) continue;
        
        // 构建函数的DFG
        DFG_Function* dfg_func = buildFunctionDFG(ir_func);
        if (!dfg_func) continue;
        
        // 添加各种类型的依赖边
        addRegisterDependencyEdges(dfg_func, ir_func);
        addMemoryDependencyEdges(dfg_func);
        // 保存函数DFG
        functions.push_back(dfg_func);
        funcMap[dfg_func->name] = dfg_func;
        
        // 如果需要，绘制DFG图
        if (draw_graph) {
            drawDFG(dfg_func);
        }
    }
    
    return true;
}

// /**
//  * @brief 活性分析（逆向数据流分析）
//  */
// void DFG_Function::livenessAnalysis() {
//     // 初始化
//     for (auto node : nodes) {
//         node->live_in.clear();
//         node->live_out.clear();
//     }

//     bool changed = true;
//     while (changed) {
//         changed = false;
//         // 逆序遍历节点
//         for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
//             DFG_Node* node = *it;
//             std::set<Value*> old_in = node->live_in;
//             std::set<Value*> old_out = node->live_out;

//             // live_out = 所有后继节点的live_in的并集
//             node->live_out.clear();
//             for (const auto& edge : node->outputs) {
//                 node->live_out.insert(edge.node->live_in.begin(), edge.node->live_in.end());
//             }

//             // use集合: 该指令用到的变量
//             std::set<Value*> use;
//             for (unsigned i = 0; i < node->inst->getOperandsNum(); ++i) {
//                 Value* op = node->inst->getOperand(i);
//                 if (op) use.insert(op);
//             }

//             // def集合: 该指令定义的变量
//             std::set<Value*> def;
//             if (node->inst->hasResultValue()) {
//                 def.insert(node->inst);
//             }

//             // live_in = use ∪ (live_out - def)
//             node->live_in = use;
//             for (auto v : node->live_out) {
//                 if (def.find(v) == def.end()) {
//                     node->live_in.insert(v);
//                 }
//             }

//             if (node->live_in != old_in || node->live_out != old_out) {
//                 changed = true;
//             }
//         }
//     }
// }

// /**
//  * @brief 死代码消除（基于活性分析）
//  */
// void DFG_Function::deadCodeElimination() {
//     // 先做活性分析
//     livenessAnalysis();

//     // 标记死代码
//     for (auto node : nodes) {
//         // 如果该指令定义了值，且该值不在live_out中，且无副作用，则为死代码
//         if (node->inst->hasResultValue() &&
//             node->live_out.find(node->inst) == node->live_out.end()) {
//             // 简单判断副作用：load/store/调用/分支等不消除
//             IRInstOperator op = node->inst->getOp();
//             if (op != IRInstOperator::IRINST_OP_STORE &&
//                 op != IRInstOperator::IRINST_OP_BRANCH_I &&
//                 op != IRInstOperator::IRINST_OP_BRANCH_F) {
//                 node->isDead = true;
//             }
//         }
//     }

//     // 移除死节点及其相关边
//     std::vector<DFG_Node*> new_nodes;
//     for (auto node : nodes) {
//         if (!node->isDead) {
//             new_nodes.push_back(node);
//         }
//     }
//     // 清理边
//     for (auto node : new_nodes) {
//         // 移除指向死节点的输出边
//         node->outputs.erase(
//             std::remove_if(node->outputs.begin(), node->outputs.end(),
//                 [](const DFG_Node::Edge& e) { return e.node->isDead; }),
//             node->outputs.end()
//         );
//         // 移除来自死节点的输入边
//         node->inputs.erase(
//             std::remove_if(node->inputs.begin(), node->inputs.end(),
//                 [](const DFG_Node::Edge& e) { return e.node->isDead; }),
//             node->inputs.end()
//         );
//     }
//     nodes = std::move(new_nodes);
//     // 重新构建instToNode
//     instToNode.clear();
//     for (auto node : nodes) {
//         instToNode[node->inst] = node;
//     }
// }


// // DFG_Generator接口实现
// void DFG_Generator::runLivenessAnalysis() {
//     for (auto func : functions) {
//         func->livenessAnalysis();
//     }
// }
// void DFG_Generator::runDeadCodeElimination() {
//     for (auto func : functions) {
//         func->deadCodeElimination();
//     }
// }
