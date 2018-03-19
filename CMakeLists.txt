cmake_minimum_required(VERSION 3.8)
project(leistungsnachweis_b_team)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h)
add_library(leistungsnachweis_b_team SHARED ${SOURCE_FILES})