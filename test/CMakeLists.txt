cmake_minimum_required(VERSION 3.2)
project(test_runner)

set(SOURCE_FILES main.cpp test-board.cpp tests.h test-coordinate.cpp test-move.cpp)

include_directories(${BITCHESS_INCLUDE_DIR})

find_package(Threads)

add_executable(test_runner ${SOURCE_FILES} )
target_link_libraries(test_runner bitchess ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS test_runner DESTINATION bin)

