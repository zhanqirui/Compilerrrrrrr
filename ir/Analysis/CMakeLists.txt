add_library(ir-Analysis
    BasicBlock.cpp
    CFG.cpp
    DFG.cpp
)

target_link_libraries(ir-Analysis PUBLIC ir-core)