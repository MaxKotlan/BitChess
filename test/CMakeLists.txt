cmake_minimum_required(VERSION 3.2)
project(test_runner)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp test-board.cpp tests.h test-coordinate.cpp test-move.cpp)

include_directories(${BITCHESS_INCLUDE_DIR})

add_executable(test_runner ${SOURCE_FILES})
target_link_libraries(test_runner bitchess)

install(TARGETS test_runner DESTINATION bin)

