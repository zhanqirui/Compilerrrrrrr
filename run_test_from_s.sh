#!/bin/bash
set -e

./Gen_exe_from_my_s.sh
qemu-aarch64 ./tests/test  