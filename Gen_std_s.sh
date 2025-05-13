#!/bin/bash
set -e

aarch64-linux-gnu-gcc -S -include "./tests/std.h" -o "./tests/test1-1-std.s" "./tests/test1-1.c"