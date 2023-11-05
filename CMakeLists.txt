cmake_minimum_required(VERSION 3.16)
project(SymMFEA)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 REQUIRED)

include_directories(source)
include_directories(include)


file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS RELATIVE ${CMAKE_SOURCE_DIR} "include/*.h" "source/*.cpp" )
add_executable(SymMFEA main.cpp ${APP_SOURCES})

