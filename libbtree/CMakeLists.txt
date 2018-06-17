set(libbtree_src Collection.h BPlusTree.h test.h test.cpp SortList.h)

add_library(libbtree STATIC ${libbtree_src})

# Specify here the include directories exported by this library
target_include_directories(libbtree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
