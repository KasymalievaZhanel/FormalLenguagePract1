cmake_minimum_required(VERSION 3.17)
project(try)

set(CMAKE_CXX_STANDARD 20)

add_executable(try main.cpp sol.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(CTests main_tests.cpp tests.cpp headers.h sol.cpp )
target_link_libraries(CTests Threads::Threads ${GTEST_LIBRARIES})

add_executable(Main main.cpp headers.h sol.cpp)
target_link_libraries(Main)
