#!/bin/bash
cmake -S . source -B cmake-build-debug 
cd cmake-build-debug && make 
echo "Build succeeded"
if $1; then
    ./SymMFEA
fi
