cmake_minimum_required(VERSION 3.16)
project(SymMFEA)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(source)
include_directories(source/components)
include_directories(source/components/functions)

add_executable(SymMFEA
        include/components/functions/add.cpp
        include/components/functions/node.cpp
        source/components/functions/add.h
        source/components/functions/node.h
        main.cpp)
