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
include E00/CMakeFiles/E00.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include E00/CMakeFiles/E00.dir/compiler_depend.make

# Include the progress variables for this target.
include E00/CMakeFiles/E00.dir/progress.make

# Include the compile flags for this target's objects.
include E00/CMakeFiles/E00.dir/flags.make

E00/CMakeFiles/E00.dir/main.c.o: E00/CMakeFiles/E00.dir/flags.make
E00/CMakeFiles/E00.dir/main.c.o: /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/main.c
E00/CMakeFiles/E00.dir/main.c.o: /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/val0.txt
E00/CMakeFiles/E00.dir/main.c.o: /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/val1.txt
E00/CMakeFiles/E00.dir/main.c.o: /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/val2.txt
E00/CMakeFiles/E00.dir/main.c.o: /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/val3.txt
E00/CMakeFiles/E00.dir/main.c.o: E00/CMakeFiles/E00.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object E00/CMakeFiles/E00.dir/main.c.o"
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT E00/CMakeFiles/E00.dir/main.c.o -MF CMakeFiles/E00.dir/main.c.o.d -o CMakeFiles/E00.dir/main.c.o -c /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/main.c

E00/CMakeFiles/E00.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/E00.dir/main.c.i"
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/main.c > CMakeFiles/E00.dir/main.c.i

E00/CMakeFiles/E00.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/E00.dir/main.c.s"
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/main.c -o CMakeFiles/E00.dir/main.c.s

# Object files for target E00
E00_OBJECTS = \
"CMakeFiles/E00.dir/main.c.o"

# External object files for target E00
E00_EXTERNAL_OBJECTS =

E00/E00: E00/CMakeFiles/E00.dir/main.c.o
E00/E00: E00/CMakeFiles/E00.dir/build.make
E00/E00: E00/CMakeFiles/E00.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable E00"
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_directory /Users/diegocampanale/CLionProjects/ASD_24/L06/E00 /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/../L06_export/E00/
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E remove /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/../L06_export/E00/CMakeLists.txt
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_if_different /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/val0.txt /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00/val0.txt
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_if_different /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/val1.txt /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00/val1.txt
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_if_different /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/val2.txt /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00/val2.txt
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E copy_if_different /Users/diegocampanale/CLionProjects/ASD_24/L06/E00/val3.txt /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00/val3.txt
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/E00.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
E00/CMakeFiles/E00.dir/build: E00/E00
.PHONY : E00/CMakeFiles/E00.dir/build

E00/CMakeFiles/E00.dir/clean:
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 && $(CMAKE_COMMAND) -P CMakeFiles/E00.dir/cmake_clean.cmake
.PHONY : E00/CMakeFiles/E00.dir/clean

E00/CMakeFiles/E00.dir/depend:
	cd /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/diegocampanale/CLionProjects/ASD_24/L06 /Users/diegocampanale/CLionProjects/ASD_24/L06/E00 /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00 /Users/diegocampanale/CLionProjects/ASD_24/L06/cmake-build-debug/E00/CMakeFiles/E00.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : E00/CMakeFiles/E00.dir/depend
