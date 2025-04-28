‘’‘
# cmake根据CMakeLists.txt进行配置与检查，这里使用clang编译器并且是Debug模式
cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++
# cmake，其中--parallel说明是并行编译，也可用-j选项
cmake --build build --parallel
’‘’

‘’‘
./build/minic -S -T -o ./tests/test1-1.png ./tests/test1-1.c

./build/minic -S -T -A -o ./tests/test1-1.png ./tests/test1-1.c

./build/minic -S -T -D -o ./tests/test1-1.png ./tests/test1-1.c

./build/minic -S -I -o ./tests/test1-1.ir ./tests/test1-1.c

./build/minic -S -I -A -o ./tests/test1-1.ir ./tests/test1-1.c

./build/minic -S -I -D -o ./tests/test1-1.ir ./tests/test1-1.c

./build/minic -S -o ./tests/test1-1.s ./tests/test1-1.c

./build/minic -S -A -o ./tests/test1-1.s ./tests/test1-1.c

./build/minic -S -D -o ./tests/test1-1.s ./tests/test1-1.c
’‘’
