/**
 * @file Graph.cpp
 * @author GitHub Copilot
 * @brief 流图生成实现
 * @version 0.1
 * @date 2024-07-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Analysis/FGraph.h"
#include "Common.h"
#include <filesystem>

bool F_Graph::buildCFG(Module* module) {
    if (cfgGenerator) {
        delete cfgGenerator;
    }
    
    cfgGenerator = new CFG_Generator(module);
    if (!cfgGenerator) {
        minic_log(LOG_ERROR, "创建CFG生成器失败");
        return false;
    }
    
    // 执行CFG分析，不输出结果
    return cfgGenerator->run(false);
}

bool F_Graph::buildDFG(Module* module) {
    if (dfgGenerator) {
        delete dfgGenerator;
    }
    
    dfgGenerator = new DFG_Generator(module);
    if (!dfgGenerator) {
        minic_log(LOG_ERROR, "创建DFG生成器失败");
        return false;
    }
    
    // 执行DFG分析，不输出结果
    return dfgGenerator->run(false);
}

bool F_Graph::drawCFG(const std::string& outputFile) {
    if (!cfgGenerator) {
        minic_log(LOG_ERROR, "未构建CFG，请先调用buildCFG");
        return false;
    }
    
    // 创建输出目录
    std::filesystem::path outputPath(outputFile);
    std::filesystem::create_directories(outputPath.parent_path());
    
    // 重新运行CFG生成器，这次输出图形
    return cfgGenerator->run(true);
}

bool F_Graph::drawDFG(const std::string& outputFile) {
    if (!dfgGenerator) {
        minic_log(LOG_ERROR, "未构建DFG，请先调用buildDFG");
        return false;
    }
    
    // 创建输出目录
    std::filesystem::path outputPath(outputFile);
    std::filesystem::create_directories(outputPath.parent_path());
    
    // 重新运行DFG生成器，这次输出图形
    return dfgGenerator->run(true);
}
