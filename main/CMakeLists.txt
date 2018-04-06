set(main_src main.cpp)

add_executable(btree-main ${main_src})

target_link_libraries(btree-main libbtree)
