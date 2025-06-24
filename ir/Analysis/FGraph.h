/**
 * @file FGraph.h
 * @author GitHub Copilot
 * @brief 流图生成接口
 * @version 0.1
 * @date 2024-07-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Module.h"
#include "CFG.h"
#include "DFG.h"
#include <string>

class F_Graph {
private:
    CFG_Generator* cfgGenerator;
    DFG_Generator* dfgGenerator;

public:
    F_Graph() : cfgGenerator(nullptr), dfgGenerator(nullptr) {}
    ~F_Graph() {
        if (cfgGenerator) delete cfgGenerator;
        if (dfgGenerator) delete dfgGenerator;
    }

    // 构建控制流图
    bool buildCFG(Module* module);
    
    // 构建数据流图
    bool buildDFG(Module* module);
    
    // 绘制控制流图
    bool drawCFG(const std::string& outputFile);
    
    // 绘制数据流图
    bool drawDFG(const std::string& outputFile);

    // 调试活跃变量分析
    void debugLivenessAnalysis();
};
