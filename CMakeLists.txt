cmake_minimum_required(VERSION 3.16)
project(SymMFEA)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)
find_package(NumCpp REQUIRED)
find_package(Boost 1.71.0 COMPONENTS date_time)



include_directories(source)
include_directories(include)



file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS RELATIVE ${CMAKE_SOURCE_DIR} "include/*.h" "source/*.cpp" )

add_executable(SymMFEA main.cpp ${APP_SOURCES})

if(Boost_FOUND)
      include_directories(${Boost_INCLUDE_DIRS})
      target_link_libraries(SymMFEA ${Boost_DATE_TIME_LIBRARY} )
endif()