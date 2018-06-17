add_executable(btree-example1 example1.cpp)
add_executable(btree-example2 example2.cpp)
add_executable(btree-example3 example3.cpp)
add_executable(btree-example4 example4.cpp)

target_link_libraries(btree-example1 libbtree)
target_link_libraries(btree-example2 libbtree)
target_link_libraries(btree-example3 libbtree)
target_link_libraries(btree-example4 libbtree)