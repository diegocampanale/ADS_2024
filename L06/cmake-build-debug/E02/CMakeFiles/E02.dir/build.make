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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/diegocampanale/CLionProjects/ASD_24/L06

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug

# Include any dependencies generated for this target.
include E02/CMakeFiles/E02.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include E02/CMakeFiles/E02.dir/compiler_depend.make

# Include the progress variables for this target.
include E02/CMakeFiles/E02.dir/progress.make

# Include the compile flags for this target's objects.
include E02/CMakeFiles/E02.dir/flags.make

E02/CMakeFiles/E02.dir/main.c.o: E02/CMakeFiles/E02.dir/flags.make
E02/CMakeFiles/E02.dir/main.c.o: /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/main.c
E02/CMakeFiles/E02.dir/main.c.o: /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/easy_test_set.txt
E02/CMakeFiles/E02.dir/main.c.o: /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/hard_test_set
E02/CMakeFiles/E02.dir/main.c.o: /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/very_easy_test_set.txt
E02/CMakeFiles/E02.dir/main.c.o: /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/very_very_easy_test_set.txt
E02/CMakeFiles/E02.dir/main.c.o: E02/CMakeFiles/E02.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object E02/CMakeFiles/E02.dir/main.c.o"
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT E02/CMakeFiles/E02.dir/main.c.o -MF CMakeFiles/E02.dir/main.c.o.d -o CMakeFiles/E02.dir/main.c.o -c /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/main.c

E02/CMakeFiles/E02.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/E02.dir/main.c.i"
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/main.c > CMakeFiles/E02.dir/main.c.i

E02/CMakeFiles/E02.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/E02.dir/main.c.s"
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/main.c -o CMakeFiles/E02.dir/main.c.s

# Object files for target E02
E02_OBJECTS = \
"CMakeFiles/E02.dir/main.c.o"

# External object files for target E02
E02_EXTERNAL_OBJECTS =

E02/E02: E02/CMakeFiles/E02.dir/main.c.o
E02/E02: E02/CMakeFiles/E02.dir/build.make
E02/E02: E02/CMakeFiles/E02.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable E02"
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_directory /Users/diegocampanale/CLionProjects/ASD_24/L06/E02 /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/../L06_export/E02/
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E remove /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/../L06_export/E02/CMakeLists.txt
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_if_different /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/easy_test_set.txt /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02/easy_test_set.txt
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_if_different /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/hard_test_set /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02/hard_test_set
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_if_different /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/very_easy_test_set.txt /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02/very_easy_test_set.txt
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_if_different /Users/diegocampanale/CLionProjects/ASD_24/L06/E02/very_very_easy_test_set.txt /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02/very_very_easy_test_set.txt
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/E02.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
E02/CMakeFiles/E02.dir/build: E02/E02
.PHONY : E02/CMakeFiles/E02.dir/build

E02/CMakeFiles/E02.dir/clean:
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 && $(CMAKE_COMMAND) -P CMakeFiles/E02.dir/cmake_clean.cmake
.PHONY : E02/CMakeFiles/E02.dir/clean

E02/CMakeFiles/E02.dir/depend:
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/diegocampanale/CLionProjects/ASD_24/L06 /Users/diegocampanale/CLionProjects/ASD_24/L06/E02 /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02 /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E02/CMakeFiles/E02.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : E02/CMakeFiles/E02.dir/depend

