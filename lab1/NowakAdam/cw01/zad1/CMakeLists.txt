cmake_minimum_required(VERSION 3.19.6)

project(cw01)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./lib)
set(COMPILE_OPT, "-O0")

add_executable(zad1static ./zad1.c)
add_executable(zad1shared ./zad1.c)

add_library(mergeFilesLibStatic STATIC ./mergeFilesLib.c)
add_library(mergeFilesLibShared SHARED ./mergeFilesLib.c)

target_compile_options(mergeFilesLibStatic PUBLIC ${COMPILE_OPT})
target_compile_options(mergeFilesLibShared PUBLIC ${COMPILE_OPT})

target_link_libraries(zad1static mergeFilesLibStatic)
target_link_libraries(zad1shared mergeFilesLibShared)

set(CMAKE_C_FLAGS "-std=gnu11")

add_compile_options( -Wall )