/**
 * @file DFG.h
 * @brief 增强版数据流图(Data Flow Graph)分析
 * @version 0.2
 * @date 2024-07-05
 *
 * @copyright Copyright (c) 2024
 */

#pragma once

#include "Module.h"
#include "Instruction.h"
#include "BasicBlock.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
// #include <gvc.h>
#include <set>
#include <optional>
#include <variant>

// 数据依赖类型枚举
enum class DependencyType {
    RAW,        // 读后写 (真依赖) - 指令B使用指令A定义的值
    WAR,        // 写后读 (反依赖) - 指令B修改了指令A读取的值
    WAW,        // 写后写 (输出依赖) - 指令B修改了指令A修改的相同位置
    MEMORY_RAW, // 内存读后写 - 通过内存访问的真依赖
    MEMORY_WAR, // 内存写后读 - 通过内存访问的反依赖
    MEMORY_WAW, // 内存写后写 - 通过内存访问的输出依赖
    CONTROL     // 控制依赖 - 指令B的执行取决于指令A的结果
};

// DFG节点类，表示数据流图中的一个节点
class DFG_Node {
public:
    Instruction* inst;                   // 该节点对应的指令
    
    // 通过边类型区分不同的依赖关系
    struct Edge {
        DFG_Node* node;
        DependencyType type;
        
        Edge(DFG_Node* n, DependencyType t) : node(n), type(t) {}
        
        bool operator==(const Edge& other) const {
            return node == other.node && type == other.type;
        }
    };
    
    std::vector<Edge> inputs;  // 输入边 - 该指令依赖的数据源
    std::vector<Edge> outputs; // 输出边 - 依赖该指令输出的其他指令
    
    // // 用于图形化显示
    // Agnode_t* agnode;                    // graphviz节点
    
    // 内存访问信息
    bool is_load;     // 是否是load指令
    bool is_store;    // 是否是store指令
    Value* mem_addr;  // 内存地址操作数(如果适用)
    Value* mem_value; // 内存值操作数(对store来说是源值，对load来说是目标值)

    // 活性分析相关
    std::set<Value*> live_in;
    std::set<Value*> live_out;

    // 常量传播相关
    // 如果该节点的结果是常量，则记录常量值
    std::optional<int64_t> constantValue;

    // 死代码标记
    bool isDead = false;

    DFG_Node(Instruction* _inst);
    std::string getLabel() const;
};

// DFG函数类，表示一个函数的数据流图
class DFG_Function {
public:
    std::string name;                             // 函数名
    std::vector<DFG_Node*> nodes;                 // 所有DFG节点
    std::unordered_map<Instruction*, DFG_Node*> instToNode; // 指令到节点的映射
    
    // 内存分析支持
    std::unordered_map<Value*, std::vector<DFG_Node*>> memoryReads;  // 读取指定地址的指令
    std::unordered_map<Value*, std::vector<DFG_Node*>> memoryWrites; // 写入指定地址的指令

    DFG_Function(const std::string& _name) : name(_name) {}
    ~DFG_Function();

    // 添加节点
    DFG_Node* addNode(Instruction* inst);

    // 添加边：从src到dst表示dst使用了src产生的数据
    void addEdge(DFG_Node* src, DFG_Node* dst, DependencyType type);
    
    // 分析内存访问
    void analyzeMemoryAccesses();

    // 活性分析
    void livenessAnalysis();

    // 死代码消除
    void deadCodeElimination();

    // 常量传播
    void constantPropagation();
};

// DFG生成器类
class DFG_Generator {
private:
    std::vector<DFG_Function*> functions;         // 所有函数的DFG
    std::unordered_map<std::string, DFG_Function*> funcMap; // 函数名到DFG的映射
    Module* module;                               // IR模块

public:
    DFG_Generator(Module* _module) : module(_module) {}
    ~DFG_Generator();

	// 允许的依赖类型集合，默认可空或者包含所有类型
	std::set<DependencyType> enabledDependencyTypes = {
		DependencyType::RAW,
		DependencyType::WAR,
		DependencyType::WAW,
		DependencyType::MEMORY_RAW,
		DependencyType::MEMORY_WAR,
		DependencyType::MEMORY_WAW,
		DependencyType::CONTROL
	};

	// 设置允许的依赖类型（可暴露接口）
	void setEnabledDependencyTypes(const std::set<DependencyType>& types) {
		enabledDependencyTypes = types;
	}

    // 运行DFG分析
    bool run(bool draw_graph = false);

    // 获取所有函数的DFG
    std::vector<DFG_Function*> getFunctions() const { return functions; }

    // 根据函数名获取DFG
    DFG_Function* getFunction(const std::string& name) const;

    // 运行活性分析
    void runLivenessAnalysis();

    // 运行死代码消除
    void runDeadCodeElimination();

    // 运行常量传播
    void runConstantPropagation();

    void DebugLA();

private:
    // 为单个函数构建DFG
    DFG_Function* buildFunctionDFG(Function* func);

    // 识别指令间的寄存器依赖(SSA依赖)
    void addRegisterDependencyEdges(DFG_Function* dfg_func, Function* ir_func);
    
    // 识别指令间的内存依赖
    void addMemoryDependencyEdges(DFG_Function* dfg_func);
    
    // 识别控制依赖
    void addControlDependencyEdges(DFG_Function* dfg_func, Function* ir_func);

    // 绘制DFG图
    void drawDFG(DFG_Function* dfg_func, const std::string& output_dir = "./DFG/");
    
    // 获取边的颜色(用于可视化)
    static const char* getEdgeColorForDependency(DependencyType type);
    
    // 获取边的样式(用于可视化)
    static const char* getEdgeStyleForDependency(DependencyType type);
};