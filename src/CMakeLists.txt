cmake_minimum_required(VERSION 3.2)
project(divis)

set(SOURCE_FILES main.cpp)

add_subdirectory(bitchess)
include_directories(include)
include_directories(bitchess)

find_package(Threads)


add_executable(bchess ${SOURCE_FILES})
target_link_libraries(bchess bitchess ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS bchess DESTINATION bin)

