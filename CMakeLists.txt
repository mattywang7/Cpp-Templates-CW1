cmake_minimum_required(VERSION 3.17)
project(Templates)

set(CMAKE_CXX_STANDARD 14)

add_executable(target1 part1/main.cpp part1/expressions.h)

add_executable(target2 part2/main.cpp part2/expressions.h)

add_executable(target3 part3/main.cpp)