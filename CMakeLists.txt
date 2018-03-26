cmake_minimum_required(VERSION 3.8)
project(leistungsnachweis_b_team)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/library.cpp src/library.h src/main.cpp)
add_library(leistungsnachweis_b_team SHARED ${SOURCE_FILES})
add_executable(btrees ${SOURCE_FILES})
