cmake_minimum_required(VERSION 3.16)
project(SymMFEA)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 REQUIRED)

include_directories(source)
include_directories(include)
include_directories(include/components)
include_directories(include/components/functions)
include_directories(include/components/DataUtils)
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
        include/components/tree/tree.h
        source/components/tree/tree.cpp
        include/components/functions/operand.h
        source/components/functions/operand.cpp
        include/evolution/population/population.h
        include/evolution/population/individual.h
        source/evolution/population/individual.cpp
        include/components/DataUtils/data_pool.h
        include/components/DataUtils/data_view.h
        source/components/DataUtils/data_pool.cpp
        source/components/DataUtils/data_view.cpp
        source/components/DataUtils/utils.cpp
        include/components/DataUtils/utils.h
        include/evolution/algorithms/GA.h
        source/evolution/algorithms/GA.cpp
        include/evolution/reproducer/crossover.h
        include/utils/random_utils.h
        source/utils/random_utils.cpp
        include/components/tree/tree_handler.h
        source/components/tree/tree_handler.cpp
        include/components/primitive.h
        source/components/primitive.cpp
        include/components/functions/tanh.h
        source/components/functions/tanh.cpp
)


