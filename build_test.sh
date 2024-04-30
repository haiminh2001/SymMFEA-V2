#!/bin/bash
cmake -S . source -B cmake-tests -DBUILD_TESTS=ON
cd cmake-tests && make 
echo "Build Test succeeded"
