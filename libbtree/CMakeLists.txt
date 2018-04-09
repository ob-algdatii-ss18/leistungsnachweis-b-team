set(libbtree_src Collection.h Adder.cpp Adder.h BPlusTree.cpp BPlusTree.h LinkedList.cpp LinkedList.h OrderedList.cpp OrderedList.h)

add_library(libbtree STATIC ${libbtree_src})

# Specify here the include directories exported by this library
target_include_directories(libbtree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
