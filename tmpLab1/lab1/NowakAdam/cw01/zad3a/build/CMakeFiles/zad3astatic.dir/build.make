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
include CMakeFiles/zad3astatic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/zad3astatic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zad3astatic.dir/flags.make

CMakeFiles/zad3astatic.dir/zad3a.c.o: CMakeFiles/zad3astatic.dir/flags.make
CMakeFiles/zad3astatic.dir/zad3a.c.o: ../zad3a.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/zad3astatic.dir/zad3a.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zad3astatic.dir/zad3a.c.o -c /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/zad3a.c

CMakeFiles/zad3astatic.dir/zad3a.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zad3astatic.dir/zad3a.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/zad3a.c > CMakeFiles/zad3astatic.dir/zad3a.c.i

CMakeFiles/zad3astatic.dir/zad3a.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zad3astatic.dir/zad3a.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/zad3a.c -o CMakeFiles/zad3astatic.dir/zad3a.c.s

# Object files for target zad3astatic
zad3astatic_OBJECTS = \
"CMakeFiles/zad3astatic.dir/zad3a.c.o"

# External object files for target zad3astatic
zad3astatic_EXTERNAL_OBJECTS =

zad3astatic: CMakeFiles/zad3astatic.dir/zad3a.c.o
zad3astatic: CMakeFiles/zad3astatic.dir/build.make
zad3astatic: libmergeFilesLibStatic.a
zad3astatic: CMakeFiles/zad3astatic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable zad3astatic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zad3astatic.dir/link.txt --verbose=$(VERBOSE)
	./zad3astatic test

# Rule to build all files generated by this target.
CMakeFiles/zad3astatic.dir/build: zad3astatic

.PHONY : CMakeFiles/zad3astatic.dir/build

CMakeFiles/zad3astatic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zad3astatic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zad3astatic.dir/clean

CMakeFiles/zad3astatic.dir/depend:
	cd /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad3a/build/CMakeFiles/zad3astatic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zad3astatic.dir/depend

