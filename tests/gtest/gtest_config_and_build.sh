#!/bin/bash

rm -rf build
cmake -G "Ninja" -S . -B build -DPROJECT_ROOT_DIR=$(pwd)/../..
cmake --build build
cd build && ctest
