#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage build.sh <build-type>"
    echo "For more information chech --help"
    exit
fi

if [ $1 == "--help" ]; then
    echo "Valid build types:"
    echo "1. debug - The debug build using Ninja Multi-Config generator"
    echo "2. release - The release build using Ninja Multi-Config generator"
    echo "3. release_with_debug_info - The release with debug info build using Ninja Multi-Config generator"
    echo "3. minimum_size_release - The minimum size release build using Ninja Multi-Config generator"
    exit
elif [ $1 != "debug" ] &&                   \
     [ $1 != "release" ] &&                 \
     [ $1 != "release_with_debug_info" ] && \
     [ $1 != "minimum_size_release" ]; then
    echo "Invalid build type..."
    echo "For more information chech --help"
    exit
fi

cmake --preset $1
cmake --build --preset $1
