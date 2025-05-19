#!/bin/bash

rundir="."
casename="test1-1"

if [ $# -gt 1 ]; then
    rundir=$1
    casename=$2
elif [ $# -gt 0 ]; then
    casename=$1
fi

OSKind=$(uname -s)
OS3264=$(uname -m)
LinuxDisID=$(lsb_release -i -s)
LinuxRelease=$(lsb_release -r -s)

IRRunToolPath="${rundir}/tools/IRCompiler/${OSKind}-${OS3264}/${LinuxDisID}-${LinuxRelease}/IRCompiler"

echo "run host"

# 使用clang进行编译直接运行
if ! clang -g -include tests/std.h -o "${rundir}/tests/${casename}-0" "${rundir}/tests/${casename}.c" "${rundir}/tests/std.c"
then
    exit 1
fi

"${rundir}/tests/${casename}-0"
printf "\n%d\n" $?

echo "IRCompiler run"

# 生成DragonIR
if ! "${rundir}/cmake-build-debug/minic" -S -I -o "${rundir}/tests/${casename}.ir" "${rundir}/tests/${casename}.c"
then
    exit 1
fi

"${IRRunToolPath}" -R "${rundir}/tests/${casename}.ir"

printf "\n%d\n" $?

echo "qemu arm64"

# 生成ARM64汇编语言

if ! "${rundir}/cmake-build-debug/minic" -S -A -o "${rundir}/tests/${casename}.s" "${rundir}/tests/${casename}.c"
then
    exit 1
fi

# 交叉编译程序成ARM64程序
aarch64-linux-gnu-gcc -g -static -include "${rundir}/tests/std.h" -o "${rundir}/tests/${casename}" "${rundir}/tests/${casename}.s" "${rundir}/tests/std.c"

# 通过qemu运行
qemu-aarch64-static "${rundir}/tests/${casename}"

printf "\n%d\n" $?