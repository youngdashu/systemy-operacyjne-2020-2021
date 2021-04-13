cmake_minimum_required(VERSION 3.19.6)

project(cw01)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./lib)
set(COMPILE_OPT_0, "-O0")
set(COMPILE_OPT_1, "-O1")
set(COMPILE_OPT_3, "-O3")

add_executable(zad3bstatic0 ./zad3b.c)
add_executable(zad3bshared0 ./zad3b.c)
add_executable(zad3bdynamic0 ./zad3b_dynamic.c)

add_executable(zad3bstatic1 ./zad3b.c)
add_executable(zad3bshared1 ./zad3b.c)
add_executable(zad3bdynamic1 ./zad3b_dynamic.c)

add_executable(zad3bstatic3 ./zad3b.c)
add_executable(zad3bshared3 ./zad3b.c)
add_executable(zad3bdynamic3 ./zad3b_dynamic.c)

add_library(mergeFilesLibStatic0 STATIC ./mergeFilesLib.c)
add_library(mergeFilesLibShared0 SHARED ./mergeFilesLib.c)
add_library(mergeFilesLibDynamic0 MODULE ./mergeFilesLib.c)

add_library(mergeFilesLibStatic1 STATIC ./mergeFilesLib.c)
add_library(mergeFilesLibShared1 SHARED ./mergeFilesLib.c)
add_library(mergeFilesLibDynamic1 MODULE ./mergeFilesLib.c)

add_library(mergeFilesLibStatic3 STATIC ./mergeFilesLib.c)
add_library(mergeFilesLibShared3 SHARED ./mergeFilesLib.c)
add_library(mergeFilesLibDynamic3 MODULE ./mergeFilesLib.c)

target_compile_options(mergeFilesLibStatic0 PUBLIC ${COMPILE_OPT_0})
target_compile_options(mergeFilesLibShared0 PUBLIC ${COMPILE_OPT_0})
target_compile_options(mergeFilesLibDynamic0 PUBLIC ${COMPILE_OPT_0})

target_compile_options(mergeFilesLibStatic1 PUBLIC ${COMPILE_OPT_1})
target_compile_options(mergeFilesLibShared1 PUBLIC ${COMPILE_OPT_1})
target_compile_options(mergeFilesLibDynamic1 PUBLIC ${COMPILE_OPT_1})

target_compile_options(mergeFilesLibStatic3 PUBLIC ${COMPILE_OPT_3})
target_compile_options(mergeFilesLibShared3 PUBLIC ${COMPILE_OPT_3})
target_compile_options(mergeFilesLibDynamic3 PUBLIC ${COMPILE_OPT_3})

target_link_libraries(zad3bstatic0 mergeFilesLibStatic0)
target_link_libraries(zad3bshared0 mergeFilesLibShared0)
target_link_libraries(zad3bdynamic0 ${CMAKE_DL_LIBS})

target_link_libraries(zad3bstatic1 mergeFilesLibStatic1)
target_link_libraries(zad3bshared1 mergeFilesLibShared1)
target_link_libraries(zad3bdynamic1 ${CMAKE_DL_LIBS})

target_link_libraries(zad3bstatic3 mergeFilesLibStatic3)
target_link_libraries(zad3bshared3 mergeFilesLibShared3)
target_link_libraries(zad3bdynamic3 ${CMAKE_DL_LIBS})

set(CMAKE_C_FLAGS "-std=gnu11")

add_custom_command(TARGET zad3bstatic0 POST_BUILD COMMAND ./zad3bstatic0 test Statyczna -O0 ${COMPILE_OPT_0})
add_custom_command(TARGET zad3bstatic1 POST_BUILD COMMAND ./zad3bstatic1 test Statyczna -O1 ${COMPILE_OPT_1})
add_custom_command(TARGET zad3bstatic3 POST_BUILD COMMAND ./zad3bstatic3 test Statyczna -O3 ${COMPILE_OPT_3})

add_custom_command(TARGET zad3bshared0 POST_BUILD COMMAND ./zad3bshared0 test Wspoldzielona -O0 ${COMPILE_OPT_0})
add_custom_command(TARGET zad3bshared1 POST_BUILD COMMAND ./zad3bshared1 test Wspoldzielona -O1 ${COMPILE_OPT_1})
add_custom_command(TARGET zad3bshared3 POST_BUILD COMMAND ./zad3bshared3 test Wspoldzielona -O3 ${COMPILE_OPT_3})

add_custom_command(TARGET zad3bdynamic0 POST_BUILD COMMAND ./zad3bdynamic0 test Dynamiczna -O0 ${COMPILE_OPT_0})
add_custom_command(TARGET zad3bdynamic1 POST_BUILD COMMAND ./zad3bdynamic1 test Dynamiczna -O1 ${COMPILE_OPT_1})
add_custom_command(TARGET zad3bdynamic3 POST_BUILD COMMAND ./zad3bdynamic3 test Dynamiczna -O3 ${COMPILE_OPT_3})

add_compile_options( -Wall )




