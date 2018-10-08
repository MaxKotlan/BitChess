cmake_minimum_required(VERSION 3.2)
project(bitchess C CXX)

set(SOURCE_FILES bitchess.h board.h coordinate.h move.h piece.h board.cpp coordinate.cpp move.cpp)

add_library(bitchess SHARED STATIC ${SOURCE_FILES})

install(TARGETS bitchess DESTINATION lib)
install(FILES bitchess.h DESTINATION include/bitchess)
