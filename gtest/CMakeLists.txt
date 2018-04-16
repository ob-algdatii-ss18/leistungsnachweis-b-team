set(gtest_src gtest.h gtest-all.cc)

add_library(gtest STATIC ${gtest_src})

target_include_directories(gtest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})