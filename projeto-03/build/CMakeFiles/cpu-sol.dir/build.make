# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/lib64/python3.7/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib64/python3.7/site-packages/cmake/data/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ec2-user/fred/projeto3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ec2-user/fred/projeto3/build

# Include any dependencies generated for this target.
include CMakeFiles/cpu-sol.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpu-sol.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpu-sol.dir/flags.make

CMakeFiles/cpu-sol.dir/cpu-sol.cpp.o: CMakeFiles/cpu-sol.dir/flags.make
CMakeFiles/cpu-sol.dir/cpu-sol.cpp.o: ../cpu-sol.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ec2-user/fred/projeto3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpu-sol.dir/cpu-sol.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpu-sol.dir/cpu-sol.cpp.o -c /home/ec2-user/fred/projeto3/cpu-sol.cpp

CMakeFiles/cpu-sol.dir/cpu-sol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpu-sol.dir/cpu-sol.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ec2-user/fred/projeto3/cpu-sol.cpp > CMakeFiles/cpu-sol.dir/cpu-sol.cpp.i

CMakeFiles/cpu-sol.dir/cpu-sol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpu-sol.dir/cpu-sol.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ec2-user/fred/projeto3/cpu-sol.cpp -o CMakeFiles/cpu-sol.dir/cpu-sol.cpp.s

# Object files for target cpu-sol
cpu__sol_OBJECTS = \
"CMakeFiles/cpu-sol.dir/cpu-sol.cpp.o"

# External object files for target cpu-sol
cpu__sol_EXTERNAL_OBJECTS =

cpu-sol: CMakeFiles/cpu-sol.dir/cpu-sol.cpp.o
cpu-sol: CMakeFiles/cpu-sol.dir/build.make
cpu-sol: CMakeFiles/cpu-sol.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ec2-user/fred/projeto3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cpu-sol"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpu-sol.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpu-sol.dir/build: cpu-sol

.PHONY : CMakeFiles/cpu-sol.dir/build

CMakeFiles/cpu-sol.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpu-sol.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpu-sol.dir/clean

CMakeFiles/cpu-sol.dir/depend:
	cd /home/ec2-user/fred/projeto3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ec2-user/fred/projeto3 /home/ec2-user/fred/projeto3 /home/ec2-user/fred/projeto3/build /home/ec2-user/fred/projeto3/build /home/ec2-user/fred/projeto3/build/CMakeFiles/cpu-sol.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpu-sol.dir/depend
