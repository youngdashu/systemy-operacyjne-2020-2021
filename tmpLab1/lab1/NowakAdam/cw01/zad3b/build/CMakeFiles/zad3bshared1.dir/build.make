# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build

# Include any dependencies generated for this target.
include CMakeFiles/zad3bshared1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/zad3bshared1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zad3bshared1.dir/flags.make

CMakeFiles/zad3bshared1.dir/zad3b.c.o: CMakeFiles/zad3bshared1.dir/flags.make
CMakeFiles/zad3bshared1.dir/zad3b.c.o: ../zad3b.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/zad3bshared1.dir/zad3b.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zad3bshared1.dir/zad3b.c.o -c /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/zad3b.c

CMakeFiles/zad3bshared1.dir/zad3b.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zad3bshared1.dir/zad3b.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/zad3b.c > CMakeFiles/zad3bshared1.dir/zad3b.c.i

CMakeFiles/zad3bshared1.dir/zad3b.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zad3bshared1.dir/zad3b.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/zad3b.c -o CMakeFiles/zad3bshared1.dir/zad3b.c.s

# Object files for target zad3bshared1
zad3bshared1_OBJECTS = \
"CMakeFiles/zad3bshared1.dir/zad3b.c.o"

# External object files for target zad3bshared1
zad3bshared1_EXTERNAL_OBJECTS =

zad3bshared1: CMakeFiles/zad3bshared1.dir/zad3b.c.o
zad3bshared1: CMakeFiles/zad3bshared1.dir/build.make
zad3bshared1: lib/libmergeFilesLibShared1.so
zad3bshared1: CMakeFiles/zad3bshared1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable zad3bshared1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zad3bshared1.dir/link.txt --verbose=$(VERBOSE)
	./zad3bshared1 test Wspoldzielona -O1

# Rule to build all files generated by this target.
CMakeFiles/zad3bshared1.dir/build: zad3bshared1

.PHONY : CMakeFiles/zad3bshared1.dir/build

CMakeFiles/zad3bshared1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zad3bshared1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zad3bshared1.dir/clean

CMakeFiles/zad3bshared1.dir/depend:
	cd /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build/CMakeFiles/zad3bshared1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zad3bshared1.dir/depend

