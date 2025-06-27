#!/bin/bash
set -e

"./build/minic" -S -A -o "./tests/test1-1.s" "./tests/test1-1.c"
aarch64-linux-gnu-gcc -g -static -include "./tests/sylib.h" -o "./tests/test1-1" "./tests/test1-1.s" "./tests/sylib.c"
qemu-aarch64 ./tests/test1-1
