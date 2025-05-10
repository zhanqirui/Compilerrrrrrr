#!/bin/bash
set -e

cd build
cpack -G ZIP --config CPackSourceConfig.cmake