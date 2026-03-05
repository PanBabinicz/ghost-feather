#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage build.sh <build-type>"
    exit
fi

if [ $1 != "debug" ] &&                   \
   [ $1 != "release" ] &&                 \
   [ $1 != "release_with_debug_info" ] && \
   [ $1 != "minimum_size_release" ]; then
    echo "Invalid build type..."
    exit
fi

cmake --preset $1
cmake --build --preset $1
