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
CMAKE_SOURCE_DIR = /home/youngdashu/sysopy/lab1/NowakAdam/cw01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/youngdashu/sysopy/lab1/NowakAdam/cw01/build

# Include any dependencies generated for this target.
include CMakeFiles/mergeFilesLib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mergeFilesLib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mergeFilesLib.dir/flags.make

CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.o: CMakeFiles/mergeFilesLib.dir/flags.make
CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.o: ../mergeFilesLib.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.o -c /home/youngdashu/sysopy/lab1/NowakAdam/cw01/mergeFilesLib.c

CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/youngdashu/sysopy/lab1/NowakAdam/cw01/mergeFilesLib.c > CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.i

CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/youngdashu/sysopy/lab1/NowakAdam/cw01/mergeFilesLib.c -o CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.s

# Object files for target mergeFilesLib
mergeFilesLib_OBJECTS = \
"CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.o"

# External object files for target mergeFilesLib
mergeFilesLib_EXTERNAL_OBJECTS =

libmergeFilesLib.a: CMakeFiles/mergeFilesLib.dir/mergeFilesLib.c.o
libmergeFilesLib.a: CMakeFiles/mergeFilesLib.dir/build.make
libmergeFilesLib.a: CMakeFiles/mergeFilesLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libmergeFilesLib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/mergeFilesLib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mergeFilesLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mergeFilesLib.dir/build: libmergeFilesLib.a

.PHONY : CMakeFiles/mergeFilesLib.dir/build

CMakeFiles/mergeFilesLib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mergeFilesLib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mergeFilesLib.dir/clean

CMakeFiles/mergeFilesLib.dir/depend:
	cd /home/youngdashu/sysopy/lab1/NowakAdam/cw01/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/youngdashu/sysopy/lab1/NowakAdam/cw01 /home/youngdashu/sysopy/lab1/NowakAdam/cw01 /home/youngdashu/sysopy/lab1/NowakAdam/cw01/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/build/CMakeFiles/mergeFilesLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mergeFilesLib.dir/depend
