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
CMAKE_SOURCE_DIR = /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build

# Include any dependencies generated for this target.
include CMakeFiles/mergeFilesLibShared.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mergeFilesLibShared.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mergeFilesLibShared.dir/flags.make

CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.o: CMakeFiles/mergeFilesLibShared.dir/flags.make
CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.o: ../mergeFilesLib.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.o -c /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/mergeFilesLib.c

CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/mergeFilesLib.c > CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.i

CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/mergeFilesLib.c -o CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.s

# Object files for target mergeFilesLibShared
mergeFilesLibShared_OBJECTS = \
"CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.o"

# External object files for target mergeFilesLibShared
mergeFilesLibShared_EXTERNAL_OBJECTS =

lib/libmergeFilesLibShared.so: CMakeFiles/mergeFilesLibShared.dir/mergeFilesLib.c.o
lib/libmergeFilesLibShared.so: CMakeFiles/mergeFilesLibShared.dir/build.make
lib/libmergeFilesLibShared.so: CMakeFiles/mergeFilesLibShared.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library lib/libmergeFilesLibShared.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mergeFilesLibShared.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mergeFilesLibShared.dir/build: lib/libmergeFilesLibShared.so

.PHONY : CMakeFiles/mergeFilesLibShared.dir/build

CMakeFiles/mergeFilesLibShared.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mergeFilesLibShared.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mergeFilesLibShared.dir/clean

CMakeFiles/mergeFilesLibShared.dir/depend:
	cd /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build/CMakeFiles/mergeFilesLibShared.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mergeFilesLibShared.dir/depend

