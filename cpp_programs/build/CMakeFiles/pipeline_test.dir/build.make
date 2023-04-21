# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jetson/Downloads/openeb/cpp_programs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jetson/Downloads/openeb/cpp_programs/build

# Include any dependencies generated for this target.
include CMakeFiles/pipeline_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pipeline_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pipeline_test.dir/flags.make

CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o: CMakeFiles/pipeline_test.dir/flags.make
CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o: ../pipeline_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jetson/Downloads/openeb/cpp_programs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o -c /home/jetson/Downloads/openeb/cpp_programs/pipeline_test.cpp

CMakeFiles/pipeline_test.dir/pipeline_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pipeline_test.dir/pipeline_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jetson/Downloads/openeb/cpp_programs/pipeline_test.cpp > CMakeFiles/pipeline_test.dir/pipeline_test.cpp.i

CMakeFiles/pipeline_test.dir/pipeline_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pipeline_test.dir/pipeline_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jetson/Downloads/openeb/cpp_programs/pipeline_test.cpp -o CMakeFiles/pipeline_test.dir/pipeline_test.cpp.s

CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o.requires:

.PHONY : CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o.requires

CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o.provides: CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/pipeline_test.dir/build.make CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o.provides.build
.PHONY : CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o.provides

CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o.provides.build: CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o


# Object files for target pipeline_test
pipeline_test_OBJECTS = \
"CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o"

# External object files for target pipeline_test
pipeline_test_EXTERNAL_OBJECTS =

pipeline_test: CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o
pipeline_test: CMakeFiles/pipeline_test.dir/build.make
pipeline_test: /home/jetson/Downloads/openeb/build/lib/libmetavision_sdk_driver.so.3.1.2
pipeline_test: /home/jetson/Downloads/openeb/build/lib/libmetavision_sdk_ui.so.3.1.2
pipeline_test: /home/jetson/Downloads/openeb/build/lib/libmetavision_hal_discovery.so.3.1.2
pipeline_test: /home/jetson/Downloads/openeb/build/lib/libmetavision_hal.so.3.1.2
pipeline_test: /home/jetson/Downloads/openeb/build/lib/libmetavision_sdk_core.so.3.1.2
pipeline_test: /usr/lib/aarch64-linux-gnu/libopencv_highgui.so.4.1.1
pipeline_test: /home/jetson/Downloads/openeb/build/lib/libmetavision_sdk_base.so.3.1.2
pipeline_test: /usr/lib/aarch64-linux-gnu/libopencv_videoio.so.4.1.1
pipeline_test: /usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so.4.1.1
pipeline_test: /usr/lib/aarch64-linux-gnu/libopencv_imgproc.so.4.1.1
pipeline_test: /usr/lib/aarch64-linux-gnu/libboost_filesystem.so
pipeline_test: /usr/lib/aarch64-linux-gnu/libboost_system.so
pipeline_test: /usr/lib/aarch64-linux-gnu/libboost_timer.so
pipeline_test: /usr/lib/aarch64-linux-gnu/libopencv_core.so.4.1.1
pipeline_test: /usr/lib/aarch64-linux-gnu/libglfw.so.3.2
pipeline_test: /usr/lib/aarch64-linux-gnu/libGLX.so
pipeline_test: /usr/lib/aarch64-linux-gnu/libOpenGL.so
pipeline_test: /usr/lib/aarch64-linux-gnu/libGLEW.so
pipeline_test: CMakeFiles/pipeline_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jetson/Downloads/openeb/cpp_programs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pipeline_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pipeline_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pipeline_test.dir/build: pipeline_test

.PHONY : CMakeFiles/pipeline_test.dir/build

CMakeFiles/pipeline_test.dir/requires: CMakeFiles/pipeline_test.dir/pipeline_test.cpp.o.requires

.PHONY : CMakeFiles/pipeline_test.dir/requires

CMakeFiles/pipeline_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pipeline_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pipeline_test.dir/clean

CMakeFiles/pipeline_test.dir/depend:
	cd /home/jetson/Downloads/openeb/cpp_programs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jetson/Downloads/openeb/cpp_programs /home/jetson/Downloads/openeb/cpp_programs /home/jetson/Downloads/openeb/cpp_programs/build /home/jetson/Downloads/openeb/cpp_programs/build /home/jetson/Downloads/openeb/cpp_programs/build/CMakeFiles/pipeline_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pipeline_test.dir/depend

