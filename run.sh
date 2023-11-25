cmake -S . source -B cmake-build-debug 
cd cmake-build-debug && make 
echo "Build succeeded"
./SymMFEA
