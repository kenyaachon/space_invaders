# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /home/moses/.local/lib/python2.7/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/moses/.local/lib/python2.7/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/moses/Documents/c++projects/space_invadesr

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/moses/Documents/c++projects/space_invadesr

# Include any dependencies generated for this target.
include CMakeFiles/space_invaders.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/space_invaders.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/space_invaders.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/space_invaders.dir/flags.make

CMakeFiles/space_invaders.dir/main.cpp.o: CMakeFiles/space_invaders.dir/flags.make
CMakeFiles/space_invaders.dir/main.cpp.o: main.cpp
CMakeFiles/space_invaders.dir/main.cpp.o: CMakeFiles/space_invaders.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/moses/Documents/c++projects/space_invadesr/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/space_invaders.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/space_invaders.dir/main.cpp.o -MF CMakeFiles/space_invaders.dir/main.cpp.o.d -o CMakeFiles/space_invaders.dir/main.cpp.o -c /home/moses/Documents/c++projects/space_invadesr/main.cpp

CMakeFiles/space_invaders.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/space_invaders.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/moses/Documents/c++projects/space_invadesr/main.cpp > CMakeFiles/space_invaders.dir/main.cpp.i

CMakeFiles/space_invaders.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/space_invaders.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/moses/Documents/c++projects/space_invadesr/main.cpp -o CMakeFiles/space_invaders.dir/main.cpp.s

# Object files for target space_invaders
space_invaders_OBJECTS = \
"CMakeFiles/space_invaders.dir/main.cpp.o"

# External object files for target space_invaders
space_invaders_EXTERNAL_OBJECTS =

space_invaders: CMakeFiles/space_invaders.dir/main.cpp.o
space_invaders: CMakeFiles/space_invaders.dir/build.make
space_invaders: /usr/lib/x86_64-linux-gnu/libglfw.so.3.2
space_invaders: /usr/lib/x86_64-linux-gnu/libGLEW.so
space_invaders: /usr/lib/x86_64-linux-gnu/libGLX.so
space_invaders: /usr/lib/x86_64-linux-gnu/libOpenGL.so
space_invaders: CMakeFiles/space_invaders.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/moses/Documents/c++projects/space_invadesr/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable space_invaders"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/space_invaders.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/space_invaders.dir/build: space_invaders
.PHONY : CMakeFiles/space_invaders.dir/build

CMakeFiles/space_invaders.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/space_invaders.dir/cmake_clean.cmake
.PHONY : CMakeFiles/space_invaders.dir/clean

CMakeFiles/space_invaders.dir/depend:
	cd /home/moses/Documents/c++projects/space_invadesr && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/moses/Documents/c++projects/space_invadesr /home/moses/Documents/c++projects/space_invadesr /home/moses/Documents/c++projects/space_invadesr /home/moses/Documents/c++projects/space_invadesr /home/moses/Documents/c++projects/space_invadesr/CMakeFiles/space_invaders.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/space_invaders.dir/depend
