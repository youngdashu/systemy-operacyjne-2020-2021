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
CMAKE_SOURCE_DIR = /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2/build

# Include any dependencies generated for this target.
include CMakeFiles/zad2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/zad2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zad2.dir/flags.make

CMakeFiles/zad2.dir/zad2.c.o: CMakeFiles/zad2.dir/flags.make
CMakeFiles/zad2.dir/zad2.c.o: ../zad2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/zad2.dir/zad2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zad2.dir/zad2.c.o -c /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2/zad2.c

CMakeFiles/zad2.dir/zad2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zad2.dir/zad2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2/zad2.c > CMakeFiles/zad2.dir/zad2.c.i

CMakeFiles/zad2.dir/zad2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zad2.dir/zad2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2/zad2.c -o CMakeFiles/zad2.dir/zad2.c.s

# Object files for target zad2
zad2_OBJECTS = \
"CMakeFiles/zad2.dir/zad2.c.o"

# External object files for target zad2
zad2_EXTERNAL_OBJECTS =

zad2: CMakeFiles/zad2.dir/zad2.c.o
zad2: CMakeFiles/zad2.dir/build.make
zad2: libmergeFilesLib.a
zad2: CMakeFiles/zad2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable zad2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zad2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/zad2.dir/build: zad2

.PHONY : CMakeFiles/zad2.dir/build

CMakeFiles/zad2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zad2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zad2.dir/clean

CMakeFiles/zad2.dir/depend:
	cd /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2 /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2 /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2/build /home/youngdashu/sysopy/lab1/NowakAdam/cw01/zad2/build/CMakeFiles/zad2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zad2.dir/depend

