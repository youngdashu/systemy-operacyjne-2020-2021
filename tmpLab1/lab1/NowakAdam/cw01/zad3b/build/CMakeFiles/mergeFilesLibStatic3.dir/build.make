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
include CMakeFiles/mergeFilesLibStatic3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mergeFilesLibStatic3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mergeFilesLibStatic3.dir/flags.make

CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.o: CMakeFiles/mergeFilesLibStatic3.dir/flags.make
CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.o: ../mergeFilesLib.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.o -c /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/mergeFilesLib.c

CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/mergeFilesLib.c > CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.i

CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/mergeFilesLib.c -o CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.s

# Object files for target mergeFilesLibStatic3
mergeFilesLibStatic3_OBJECTS = \
"CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.o"

# External object files for target mergeFilesLibStatic3
mergeFilesLibStatic3_EXTERNAL_OBJECTS =

libmergeFilesLibStatic3.a: CMakeFiles/mergeFilesLibStatic3.dir/mergeFilesLib.c.o
libmergeFilesLibStatic3.a: CMakeFiles/mergeFilesLibStatic3.dir/build.make
libmergeFilesLibStatic3.a: CMakeFiles/mergeFilesLibStatic3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libmergeFilesLibStatic3.a"
	$(CMAKE_COMMAND) -P CMakeFiles/mergeFilesLibStatic3.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mergeFilesLibStatic3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mergeFilesLibStatic3.dir/build: libmergeFilesLibStatic3.a

.PHONY : CMakeFiles/mergeFilesLibStatic3.dir/build

CMakeFiles/mergeFilesLibStatic3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mergeFilesLibStatic3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mergeFilesLibStatic3.dir/clean

CMakeFiles/mergeFilesLibStatic3.dir/depend:
	cd /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3b/build/CMakeFiles/mergeFilesLibStatic3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mergeFilesLibStatic3.dir/depend

