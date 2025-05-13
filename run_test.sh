#!/bin/bash
set -e

./Gen_my_s.sh
qemu-aarch64 ./tests/test  