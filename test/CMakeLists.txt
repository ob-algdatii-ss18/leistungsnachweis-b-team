file(GLOB SRCS *.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(testBTree ${SRCS})

target_link_libraries(testBTree
        src
        gtest
        gmock
        )

include_directories("..")

install(TARGETS testBTree DESTINATION bin)