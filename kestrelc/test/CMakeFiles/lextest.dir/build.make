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
include test/CMakeFiles/lextest.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/lextest.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/lextest.dir/flags.make

test/CMakeFiles/lextest.dir/lextest.cpp.o: test/CMakeFiles/lextest.dir/flags.make
test/CMakeFiles/lextest.dir/lextest.cpp.o: test/lextest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fnoyanisi/Code/Compilers101/kestrelc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/lextest.dir/lextest.cpp.o"
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lextest.dir/lextest.cpp.o -c /Users/fnoyanisi/Code/Compilers101/kestrelc/test/lextest.cpp

test/CMakeFiles/lextest.dir/lextest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lextest.dir/lextest.cpp.i"
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/fnoyanisi/Code/Compilers101/kestrelc/test/lextest.cpp > CMakeFiles/lextest.dir/lextest.cpp.i

test/CMakeFiles/lextest.dir/lextest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lextest.dir/lextest.cpp.s"
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/fnoyanisi/Code/Compilers101/kestrelc/test/lextest.cpp -o CMakeFiles/lextest.dir/lextest.cpp.s

# Object files for target lextest
lextest_OBJECTS = \
"CMakeFiles/lextest.dir/lextest.cpp.o"

# External object files for target lextest
lextest_EXTERNAL_OBJECTS =

test/lextest: test/CMakeFiles/lextest.dir/lextest.cpp.o
test/lextest: test/CMakeFiles/lextest.dir/build.make
test/lextest: src/liblexical.a
test/lextest: test/CMakeFiles/lextest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/fnoyanisi/Code/Compilers101/kestrelc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lextest"
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lextest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/lextest.dir/build: test/lextest

.PHONY : test/CMakeFiles/lextest.dir/build

test/CMakeFiles/lextest.dir/clean:
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc/test && $(CMAKE_COMMAND) -P CMakeFiles/lextest.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/lextest.dir/clean

test/CMakeFiles/lextest.dir/depend:
	cd /Users/fnoyanisi/Code/Compilers101/kestrelc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/fnoyanisi/Code/Compilers101/kestrelc /Users/fnoyanisi/Code/Compilers101/kestrelc/test /Users/fnoyanisi/Code/Compilers101/kestrelc /Users/fnoyanisi/Code/Compilers101/kestrelc/test /Users/fnoyanisi/Code/Compilers101/kestrelc/test/CMakeFiles/lextest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/lextest.dir/depend

