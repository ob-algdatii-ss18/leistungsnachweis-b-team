set(main_src main.cpp ../libbtree/SortList.h)

add_executable(btree-main ${main_src})

target_link_libraries(btree-main libbtree)
