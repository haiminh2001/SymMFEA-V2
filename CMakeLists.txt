cmake_minimum_required(VERSION 3.16)
project(SymMFEA)

set(CMAKE_CXX_STANDARD 14)

include_directories(source)
include_directories(include)
include_directories(include/components)
include_directories(include/components/functions)

add_executable(SymMFEA
        source/components/functions/sum.cpp
        source/components/functions/node.cpp
        include/components/functions/sum.h
        include/components/functions/node.h
        main.cpp
        include/components/functions/product.h
        source/components/functions/product.cpp
        include/components/tree.h
        source/components/tree.cpp)
