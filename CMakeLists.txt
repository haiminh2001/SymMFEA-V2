cmake_minimum_required(VERSION 3.16)
project(SymMFEA)

set(CMAKE_CXX_STANDARD 14)

include_directories(source)
include_directories(include)
include_directories(include/components)
include_directories(include/components/functions)
include_directories(include/evolution)
include_directories(include/evolution/algorithms)
include_directories(include/evolution/population)
include_directories(include/evolution/reproducer)

add_executable(SymMFEA
        source/components/functions/sum.cpp
        source/components/functions/node.cpp
        include/components/functions/sum.h
        include/components/functions/node.h
        main.cpp
        include/components/functions/product.h
        source/components/functions/product.cpp
        include/components/tree.h
        source/components/tree.cpp
        include/components/functions/operand.h
        source/components/functions/operand.cpp
        include/evolution/population/population.h
        include/evolution/population/individual.h
        source/evolution/population/individual.cpp)
