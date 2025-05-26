‘’‘

# cmake根据CMakeLists.txt进行配置与检查，这里使用clang编译器并且是Debug模式
cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++
# cmake，其中--parallel说明是并行编译，也可用-j选项
cmake --build build --parallel

cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++
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

clang  -S -emit-llvm -o ./tests/test1-1.ll ./tests/test1-1.c

’‘’


clang -S -emit-llvm -o ./tests/test1-1S.ll ./tests/test1-1.c
lli tests/test1-1.ll
echo $?

./build/minic -S -I -A -o ./tests/test1-1.ll ./tests/test1-1.c`

clang -o tests/test1-1 tests/test1-1.ll tests/std.c


./tests/test1-1

./build/minic -S -I -A -o ./tests/test1-7.ll ./tests/test1-7.c
lli tests/test1-7.ll
echo $?