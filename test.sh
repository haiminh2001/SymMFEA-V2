#!/bin/bash
cmake -S . source -B cmake-tests
cd cmake-tests && make 
echo "Build Test succeeded"
./SymMFEA_test