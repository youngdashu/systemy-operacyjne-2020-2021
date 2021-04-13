cmake_minimum_required(VERSION 3.19.6)

project(cw01)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./lib)
set(COMPILE_OPT, "-O0")

add_executable(zad2 ./zad2.c)

add_library(mergeFilesLib STATIC ./mergeFilesLib.c)

target_compile_options(mergeFilesLib PUBLIC ${COMPILE_OPT})

target_link_libraries(zad2 mergeFilesLib)

set(CMAKE_C_FLAGS "-std=gnu11")

add_compile_options( -Wall )



