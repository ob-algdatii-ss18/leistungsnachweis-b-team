file(GLOB SRCS *.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(libbtree-test ${SRCS} TestBPlusTree.cpp)

target_link_libraries(libbtree-test libbtree gtest)

include_directories("..")

install(TARGETS libbtree-test DESTINATION bin)
