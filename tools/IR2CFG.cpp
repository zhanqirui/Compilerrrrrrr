#include <fstream>
#include <iostream>

#include "ir/IRCode.h"
#include "Analysis/CFG.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: IR2CFG <ir-file> [--dot <dot-out>]\n";
        return 1;
    }

    InterCode ic;
    if (!ic.parseFromFile(argv[1])) {
        std::cerr << "Parse failed: " << argv[1] << '\n';
        return 2;
    }

    const Function *func = ic.getFunction("main");
    if (func == nullptr) {
        std::cerr << "Function 'main' not found.\n";
        return 3;
    }

	// 暂时删除这种用法
    // CFG cfg(const_cast<Function *>(func));
    // cfg.build();

    // if (argc == 4 && std::string(argv[2]) == "--dot") {
    //     std::ofstream ofs(argv[3]);
    //     cfg.dumpDot(ofs);
    //     std::cout << "DOT written to " << argv[3] << '\n';
    // } else {
    //     cfg.dumpDot(std::cout);
    // }
    return 0;
}
