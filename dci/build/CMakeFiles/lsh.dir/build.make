# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xt/tong/mopsi/locality_sensitive_hashing/dci

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xt/tong/mopsi/locality_sensitive_hashing/dci/build

# Include any dependencies generated for this target.
include CMakeFiles/lsh.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lsh.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lsh.dir/flags.make

CMakeFiles/lsh.dir/main_dci.cpp.o: CMakeFiles/lsh.dir/flags.make
CMakeFiles/lsh.dir/main_dci.cpp.o: ../main_dci.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xt/tong/mopsi/locality_sensitive_hashing/dci/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lsh.dir/main_dci.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lsh.dir/main_dci.cpp.o -c /home/xt/tong/mopsi/locality_sensitive_hashing/dci/main_dci.cpp

CMakeFiles/lsh.dir/main_dci.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lsh.dir/main_dci.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xt/tong/mopsi/locality_sensitive_hashing/dci/main_dci.cpp > CMakeFiles/lsh.dir/main_dci.cpp.i

CMakeFiles/lsh.dir/main_dci.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lsh.dir/main_dci.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xt/tong/mopsi/locality_sensitive_hashing/dci/main_dci.cpp -o CMakeFiles/lsh.dir/main_dci.cpp.s

CMakeFiles/lsh.dir/main_dci.cpp.o.requires:
.PHONY : CMakeFiles/lsh.dir/main_dci.cpp.o.requires

CMakeFiles/lsh.dir/main_dci.cpp.o.provides: CMakeFiles/lsh.dir/main_dci.cpp.o.requires
	$(MAKE) -f CMakeFiles/lsh.dir/build.make CMakeFiles/lsh.dir/main_dci.cpp.o.provides.build
.PHONY : CMakeFiles/lsh.dir/main_dci.cpp.o.provides

CMakeFiles/lsh.dir/main_dci.cpp.o.provides.build: CMakeFiles/lsh.dir/main_dci.cpp.o

CMakeFiles/lsh.dir/lshdci.cpp.o: CMakeFiles/lsh.dir/flags.make
CMakeFiles/lsh.dir/lshdci.cpp.o: ../lshdci.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xt/tong/mopsi/locality_sensitive_hashing/dci/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lsh.dir/lshdci.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lsh.dir/lshdci.cpp.o -c /home/xt/tong/mopsi/locality_sensitive_hashing/dci/lshdci.cpp

CMakeFiles/lsh.dir/lshdci.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lsh.dir/lshdci.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xt/tong/mopsi/locality_sensitive_hashing/dci/lshdci.cpp > CMakeFiles/lsh.dir/lshdci.cpp.i

CMakeFiles/lsh.dir/lshdci.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lsh.dir/lshdci.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xt/tong/mopsi/locality_sensitive_hashing/dci/lshdci.cpp -o CMakeFiles/lsh.dir/lshdci.cpp.s

CMakeFiles/lsh.dir/lshdci.cpp.o.requires:
.PHONY : CMakeFiles/lsh.dir/lshdci.cpp.o.requires

CMakeFiles/lsh.dir/lshdci.cpp.o.provides: CMakeFiles/lsh.dir/lshdci.cpp.o.requires
	$(MAKE) -f CMakeFiles/lsh.dir/build.make CMakeFiles/lsh.dir/lshdci.cpp.o.provides.build
.PHONY : CMakeFiles/lsh.dir/lshdci.cpp.o.provides

CMakeFiles/lsh.dir/lshdci.cpp.o.provides.build: CMakeFiles/lsh.dir/lshdci.cpp.o

# Object files for target lsh
lsh_OBJECTS = \
"CMakeFiles/lsh.dir/main_dci.cpp.o" \
"CMakeFiles/lsh.dir/lshdci.cpp.o"

# External object files for target lsh
lsh_EXTERNAL_OBJECTS =

lsh: CMakeFiles/lsh.dir/main_dci.cpp.o
lsh: CMakeFiles/lsh.dir/lshdci.cpp.o
lsh: CMakeFiles/lsh.dir/build.make
lsh: /usr/local/lib/libopencv_videostab.so.3.0.0
lsh: /usr/local/lib/libopencv_videoio.so.3.0.0
lsh: /usr/local/lib/libopencv_video.so.3.0.0
lsh: /usr/local/lib/libopencv_superres.so.3.0.0
lsh: /usr/local/lib/libopencv_stitching.so.3.0.0
lsh: /usr/local/lib/libopencv_shape.so.3.0.0
lsh: /usr/local/lib/libopencv_photo.so.3.0.0
lsh: /usr/local/lib/libopencv_objdetect.so.3.0.0
lsh: /usr/local/lib/libopencv_ml.so.3.0.0
lsh: /usr/local/lib/libopencv_imgproc.so.3.0.0
lsh: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
lsh: /usr/local/lib/libopencv_highgui.so.3.0.0
lsh: /usr/local/lib/libopencv_hal.a
lsh: /usr/local/lib/libopencv_flann.so.3.0.0
lsh: /usr/local/lib/libopencv_features2d.so.3.0.0
lsh: /usr/local/lib/libopencv_cudev.so.3.0.0
lsh: /usr/local/lib/libopencv_cudawarping.so.3.0.0
lsh: /usr/local/lib/libopencv_cudastereo.so.3.0.0
lsh: /usr/local/lib/libopencv_cudaoptflow.so.3.0.0
lsh: /usr/local/lib/libopencv_cudaobjdetect.so.3.0.0
lsh: /usr/local/lib/libopencv_cudalegacy.so.3.0.0
lsh: /usr/local/lib/libopencv_cudaimgproc.so.3.0.0
lsh: /usr/local/lib/libopencv_cudafilters.so.3.0.0
lsh: /usr/local/lib/libopencv_cudafeatures2d.so.3.0.0
lsh: /usr/local/lib/libopencv_cudacodec.so.3.0.0
lsh: /usr/local/lib/libopencv_cudabgsegm.so.3.0.0
lsh: /usr/local/lib/libopencv_cudaarithm.so.3.0.0
lsh: /usr/local/lib/libopencv_core.so.3.0.0
lsh: /usr/local/lib/libopencv_calib3d.so.3.0.0
lsh: /usr/local/lib/libopencv_cudawarping.so.3.0.0
lsh: /usr/local/lib/libopencv_objdetect.so.3.0.0
lsh: /usr/local/lib/libopencv_cudafilters.so.3.0.0
lsh: /usr/local/lib/libopencv_cudaarithm.so.3.0.0
lsh: /usr/local/lib/libopencv_features2d.so.3.0.0
lsh: /usr/local/lib/libopencv_ml.so.3.0.0
lsh: /usr/local/lib/libopencv_highgui.so.3.0.0
lsh: /usr/local/lib/libopencv_videoio.so.3.0.0
lsh: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
lsh: /usr/local/lib/libopencv_flann.so.3.0.0
lsh: /usr/local/lib/libopencv_video.so.3.0.0
lsh: /usr/local/lib/libopencv_imgproc.so.3.0.0
lsh: /usr/local/lib/libopencv_core.so.3.0.0
lsh: /usr/local/lib/libopencv_cudev.so.3.0.0
lsh: /usr/local/lib/libopencv_hal.a
lsh: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
lsh: CMakeFiles/lsh.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable lsh"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lsh.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lsh.dir/build: lsh
.PHONY : CMakeFiles/lsh.dir/build

CMakeFiles/lsh.dir/requires: CMakeFiles/lsh.dir/main_dci.cpp.o.requires
CMakeFiles/lsh.dir/requires: CMakeFiles/lsh.dir/lshdci.cpp.o.requires
.PHONY : CMakeFiles/lsh.dir/requires

CMakeFiles/lsh.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lsh.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lsh.dir/clean

CMakeFiles/lsh.dir/depend:
	cd /home/xt/tong/mopsi/locality_sensitive_hashing/dci/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xt/tong/mopsi/locality_sensitive_hashing/dci /home/xt/tong/mopsi/locality_sensitive_hashing/dci /home/xt/tong/mopsi/locality_sensitive_hashing/dci/build /home/xt/tong/mopsi/locality_sensitive_hashing/dci/build /home/xt/tong/mopsi/locality_sensitive_hashing/dci/build/CMakeFiles/lsh.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lsh.dir/depend

