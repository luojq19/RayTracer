# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.0_1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.0_1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/build

# Include any dependencies generated for this target.
include CMakeFiles/PA1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PA1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PA1.dir/flags.make

CMakeFiles/PA1.dir/src/image.cpp.o: CMakeFiles/PA1.dir/flags.make
CMakeFiles/PA1.dir/src/image.cpp.o: ../src/image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PA1.dir/src/image.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA1.dir/src/image.cpp.o -c /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/src/image.cpp

CMakeFiles/PA1.dir/src/image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA1.dir/src/image.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/src/image.cpp > CMakeFiles/PA1.dir/src/image.cpp.i

CMakeFiles/PA1.dir/src/image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA1.dir/src/image.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/src/image.cpp -o CMakeFiles/PA1.dir/src/image.cpp.s

CMakeFiles/PA1.dir/src/main.cpp.o: CMakeFiles/PA1.dir/flags.make
CMakeFiles/PA1.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PA1.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA1.dir/src/main.cpp.o -c /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/src/main.cpp

CMakeFiles/PA1.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA1.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/src/main.cpp > CMakeFiles/PA1.dir/src/main.cpp.i

CMakeFiles/PA1.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA1.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/src/main.cpp -o CMakeFiles/PA1.dir/src/main.cpp.s

# Object files for target PA1
PA1_OBJECTS = \
"CMakeFiles/PA1.dir/src/image.cpp.o" \
"CMakeFiles/PA1.dir/src/main.cpp.o"

# External object files for target PA1
PA1_EXTERNAL_OBJECTS =

../bin/PA1: CMakeFiles/PA1.dir/src/image.cpp.o
../bin/PA1: CMakeFiles/PA1.dir/src/main.cpp.o
../bin/PA1: CMakeFiles/PA1.dir/build.make
../bin/PA1: deps/vecmath/libvecmath.a
../bin/PA1: CMakeFiles/PA1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/PA1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PA1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PA1.dir/build: ../bin/PA1

.PHONY : CMakeFiles/PA1.dir/build

CMakeFiles/PA1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PA1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PA1.dir/clean

CMakeFiles/PA1.dir/depend:
	cd /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/build /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/build /Users/jiaqiluo/Desktop/learning/CG/Homeworks/pathTracer/code/build/CMakeFiles/PA1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PA1.dir/depend

