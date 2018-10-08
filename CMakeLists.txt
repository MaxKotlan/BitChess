cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(BITCHESS_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/bitchess)

add_subdirectory(src)
add_subdirectory(test)


