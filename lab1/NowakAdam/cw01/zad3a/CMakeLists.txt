cmake_minimum_required(VERSION 3.19.6)

project(cw01)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./lib)
set(COMPILE_OPT, "-O0")

add_executable(zad3astatic ./zad3a.c)
add_executable(zad3ashared ./zad3a.c)
add_executable(zad3adynamic ./zad3a_dynamic.c)

add_library(mergeFilesLibStatic STATIC ./mergeFilesLib.c)
add_library(mergeFilesLibShared SHARED ./mergeFilesLib.c)
add_library(mergeFilesLibDynamic MODULE ./mergeFilesLib.c)

target_compile_options(mergeFilesLibStatic PUBLIC ${COMPILE_OPT})
target_compile_options(mergeFilesLibShared PUBLIC ${COMPILE_OPT})
target_compile_options(mergeFilesLibDynamic PUBLIC ${COMPILE_OPT})

target_compile_options(zad3adynamic PUBLIC ${COMPILE_OPT})

target_link_libraries(zad3astatic mergeFilesLibStatic)
target_link_libraries(zad3ashared mergeFilesLibShared)
target_link_libraries(zad3adynamic ${CMAKE_DL_LIBS})

add_custom_command(TARGET zad3astatic POST_BUILD COMMAND ./zad3astatic test )
add_custom_command(TARGET zad3ashared POST_BUILD COMMAND ./zad3ashared test )
add_custom_command(TARGET zad3adynamic POST_BUILD COMMAND ./zad3adynamic test )

set(CMAKE_C_FLAGS "-std=gnu11")

add_compile_options( -Wall )




