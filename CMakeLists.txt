cmake_minimum_required(VERSION 3.8)
project(leistungsnachweis_b_team)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

set(SOURCE_FILES main.cpp)
add_executable(BTree ${SOURCE_FILES})

target_link_libraries(BTree LINK_PUBLIC src)

# GoogleTest

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

add_subdirectory(test)

enable_testing()

add_test(AddTest test/AddTest.cpp --gtest_output=xml:report.xml)

#set(SOURCE_FILES src/library.cpp src/library.h src/main.cpp src/Add.cpp src/Add.h test/AddTest.cpp test/main.cpp)
#add_library(leistungsnachweis_b_team SHARED ${SOURCE_FILES})
#add_executable(btrees ${SOURCE_FILES})
