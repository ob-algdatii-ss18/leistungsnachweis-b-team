file(GLOB SRCS *.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(libbtree-test ${SRCS} TestBPlusTree.cpp TestSortList.cpp CollectionTest.cpp)

if (UNIX AND NOT APPLE)
    target_link_libraries(libbtree-test libbtree gtest pthread)
else()
    target_link_libraries(libbtree-test libbtree gtest)
endif()

include_directories("..")

install(TARGETS libbtree-test DESTINATION bin)

add_test(NAME libtreetest COMMAND libbtree-test)
