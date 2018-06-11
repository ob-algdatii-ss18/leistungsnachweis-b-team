cmake_minimum_required(VERSION 3.8)
project(leistungsnachweis_b_team)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")

enable_testing()

add_subdirectory(main)
add_subdirectory(gtest)
add_subdirectory(libbtree)
add_subdirectory(test)
