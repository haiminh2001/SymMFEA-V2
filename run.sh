cmake -S . source -B cmake-build-debug --debug
cd cmake-build-debug && make && ./SymMFEA
echo ""