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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/fnoyanisi/Code/Compilers101/kestrelc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/fnoyanisi/Code/Compilers101/kestrelc

# Include any dependencies generated for this target.
include src/CMakeFiles/kestrelc.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/kestrelc.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/kestrelc.dir/flags.make

src/CMakeFiles/kestrelc.dir/kestrelc.cpp.o: src/CMakeFiles/kestrelc.dir/flags.make
src/CMakeFiles/kestrelc.dir/kestrelc.cpp.o: src/kestrelc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fnoyanisi/Code/Compilers101/kestrelc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/kestrelc.dir/kestrelc.cpp.o"
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kestrelc.dir/kestrelc.cpp.o -c /Users/fnoyanisi/Code/Compilers101/kestrelc/src/kestrelc.cpp

src/CMakeFiles/kestrelc.dir/kestrelc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kestrelc.dir/kestrelc.cpp.i"
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/fnoyanisi/Code/Compilers101/kestrelc/src/kestrelc.cpp > CMakeFiles/kestrelc.dir/kestrelc.cpp.i

src/CMakeFiles/kestrelc.dir/kestrelc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kestrelc.dir/kestrelc.cpp.s"
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/fnoyanisi/Code/Compilers101/kestrelc/src/kestrelc.cpp -o CMakeFiles/kestrelc.dir/kestrelc.cpp.s

# Object files for target kestrelc
kestrelc_OBJECTS = \
"CMakeFiles/kestrelc.dir/kestrelc.cpp.o"

# External object files for target kestrelc
kestrelc_EXTERNAL_OBJECTS =

src/kestrelc: src/CMakeFiles/kestrelc.dir/kestrelc.cpp.o
src/kestrelc: src/CMakeFiles/kestrelc.dir/build.make
src/kestrelc: src/liblexical.a
src/kestrelc: src/CMakeFiles/kestrelc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/fnoyanisi/Code/Compilers101/kestrelc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable kestrelc"
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kestrelc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/kestrelc.dir/build: src/kestrelc

.PHONY : src/CMakeFiles/kestrelc.dir/build

src/CMakeFiles/kestrelc.dir/clean:
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc/src && $(CMAKE_COMMAND) -P CMakeFiles/kestrelc.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/kestrelc.dir/clean

src/CMakeFiles/kestrelc.dir/depend:
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/fnoyanisi/Code/Compilers101/kestrelc /Users/fnoyanisi/Code/Compilers101/kestrelc/src /Users/fnoyanisi/Code/Compilers101/kestrelc /Users/fnoyanisi/Code/Compilers101/kestrelc/src /Users/fnoyanisi/Code/Compilers101/kestrelc/src/CMakeFiles/kestrelc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/kestrelc.dir/depend

