cmake_minimum_required(VERSION 3.8)
project(leistungsnachweis_b_team)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(main)
add_subdirectory(gtest)
add_subdirectory(libbtree)
add_subdirectory(test)
