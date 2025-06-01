///
/// @file IRCode.cpp
/// @brief IR指令序列类实现
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>新做
/// </table>
///
#include "IRCode.h"
#include "Function.h"
#include "Instructions/LabelInstruction.h"

using std::ifstream;
using std::getline;
using std::regex;
using std::smatch;

/// @brief 析构函数，增加function的释放
InterCode::~InterCode() {
    Delete();
    for (auto &kv : functions_) delete kv.second;
    functions_.clear();
}

bool InterCode::parseFromFile(const std::string &filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return false;

    std::regex  defRE(R"(^\s*define.*@([^(\s]+))");   // 捕获函数名
    std::string line;
    Function   *currFun = nullptr;

    while (std::getline(ifs, line)) {
        std::smatch m;
        if (std::regex_search(line, m, defRE)) {          // 遇到 define
            std::string fname = m[1].str();
            currFun = new Function(fname);                // 轻量构造
            functions_[fname] = currFun;
            currFun->appendRawLine(line);
            continue;
        }

        if (currFun) {
            currFun->appendRawLine(line);
            if (line.find('}') != std::string::npos) {    // 函数结束
                currFun->finalizeRaw();
                currFun = nullptr;
            }
        }
    }
    return !functions_.empty();
}

const Function *InterCode::getFunction(const std::string &name) const {
    auto it = functions_.find(name);
    return (it == functions_.end()) ? nullptr : it->second;
}

/// @brief 添加一个指令块，添加到尾部，并清除原来指令块的内容
/// @param block 指令块，请注意加入后会自动清空block的指令
void InterCode::addInst(InterCode & block)
{
    std::vector<Instruction *> & insert = block.getInsts();

    code.insert(code.end(), insert.begin(), insert.end());

    // InterCode析构会清理资源，因此移动指令到code中后必须清理，否则会释放多次导致程序例外
    // 当然，这里也可不清理，但InterCode的析构函数不能清理，需专门的函数清理即可。
    insert.clear();
}

/// @brief 添加一条中间指令
/// @param inst IR指令
void InterCode::addInst(Instruction * inst)
{
    code.push_back(inst);
}

/// @brief 获取指令序列
/// @return 指令序列
std::vector<Instruction *> & InterCode::getInsts()
{
    return code;
}

/// @brief 删除所有指令
void InterCode::Delete()
{
    // 不能直接删除指令，需要先清除操作数
    for (auto inst: code) {
        inst->clearOperands();
    }

    // 资源清理
    for (auto inst: code) {
        delete inst;
    }

    code.clear();
}
