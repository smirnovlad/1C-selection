# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vlad/Projects/CLionProjects/1C-selection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vlad/Projects/CLionProjects/1C-selection/build

# Include any dependencies generated for this target.
include CMakeFiles/1C_selection.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/1C_selection.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/1C_selection.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1C_selection.dir/flags.make

CMakeFiles/1C_selection.dir/main.cpp.o: CMakeFiles/1C_selection.dir/flags.make
CMakeFiles/1C_selection.dir/main.cpp.o: /home/vlad/Projects/CLionProjects/1C-selection/main.cpp
CMakeFiles/1C_selection.dir/main.cpp.o: CMakeFiles/1C_selection.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlad/Projects/CLionProjects/1C-selection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1C_selection.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1C_selection.dir/main.cpp.o -MF CMakeFiles/1C_selection.dir/main.cpp.o.d -o CMakeFiles/1C_selection.dir/main.cpp.o -c /home/vlad/Projects/CLionProjects/1C-selection/main.cpp

CMakeFiles/1C_selection.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1C_selection.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vlad/Projects/CLionProjects/1C-selection/main.cpp > CMakeFiles/1C_selection.dir/main.cpp.i

CMakeFiles/1C_selection.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1C_selection.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vlad/Projects/CLionProjects/1C-selection/main.cpp -o CMakeFiles/1C_selection.dir/main.cpp.s

# Object files for target 1C_selection
1C_selection_OBJECTS = \
"CMakeFiles/1C_selection.dir/main.cpp.o"

# External object files for target 1C_selection
1C_selection_EXTERNAL_OBJECTS =

1C_selection: CMakeFiles/1C_selection.dir/main.cpp.o
1C_selection: CMakeFiles/1C_selection.dir/build.make
1C_selection: CMakeFiles/1C_selection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/vlad/Projects/CLionProjects/1C-selection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 1C_selection"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1C_selection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1C_selection.dir/build: 1C_selection
.PHONY : CMakeFiles/1C_selection.dir/build

CMakeFiles/1C_selection.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1C_selection.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1C_selection.dir/clean

CMakeFiles/1C_selection.dir/depend:
	cd /home/vlad/Projects/CLionProjects/1C-selection/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vlad/Projects/CLionProjects/1C-selection /home/vlad/Projects/CLionProjects/1C-selection /home/vlad/Projects/CLionProjects/1C-selection/build /home/vlad/Projects/CLionProjects/1C-selection/build /home/vlad/Projects/CLionProjects/1C-selection/build/CMakeFiles/1C_selection.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/1C_selection.dir/depend
