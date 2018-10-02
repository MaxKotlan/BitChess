cmake_minimum_required(VERSION 3.2)
project(bitchess C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(SOURCE_FILES bitchess.h bitchess.cpp)

add_library(bitchess SHARED STATIC ${SOURCE_FILES})

install(TARGETS bitchess DESTINATION lib)
install(FILES bitchess.h DESTINATION include/bitchess)
