cmake_minimum_required(VERSION 3.16)
project(SymMFEA)

option(BUILD_TESTS "Build all tests." OFF) # Turn off by default

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)
find_package(Threads REQUIRED)

include_directories(source)
include_directories(include)
include_directories(${EIGEN3_INCLUDE_DIR})

# Test
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    enable_testing()
    find_package(GTest REQUIRED)

    include(GoogleTest)
    file(GLOB_RECURSE TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
    file(GLOB_RECURSE APP_SOURCES "${CMAKE_SOURCE_DIR}/source/*.cpp" "${CMAKE_SOURCE_DIR}/include/*.h")

    set(TEST_NAME ${PROJECT_NAME}_test)
    add_executable(${TEST_NAME} ${TEST_SOURCES} ${APP_SOURCES})
    target_link_libraries(${TEST_NAME} GTest::GTest GTest::Main)
    gtest_discover_tests(${TEST_NAME}
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}")
    set_target_properties(${TEST_NAME} PROPERTIES FOLDER tests)

else()
    # Main
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -O3")
    # add_compile_options("-ffast-math")
endif()

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS RELATIVE ${CMAKE_SOURCE_DIR} "source/*.cpp" "include/*.h")


add_executable(SymMFEA main.cpp ${APP_SOURCES})

target_link_libraries(SymMFEA
    PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
)