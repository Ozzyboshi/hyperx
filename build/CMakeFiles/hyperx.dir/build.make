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
CMAKE_SOURCE_DIR = /root/ACE/game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/ACE/game/build

# Include any dependencies generated for this target.
include CMakeFiles/hyperx.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hyperx.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hyperx.dir/flags.make

CMakeFiles/hyperx.dir/src/flood.c.obj: CMakeFiles/hyperx.dir/flags.make
CMakeFiles/hyperx.dir/src/flood.c.obj: ../src/flood.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ACE/game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/hyperx.dir/src/flood.c.obj"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hyperx.dir/src/flood.c.obj   -c /root/ACE/game/src/flood.c

CMakeFiles/hyperx.dir/src/flood.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hyperx.dir/src/flood.c.i"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/ACE/game/src/flood.c > CMakeFiles/hyperx.dir/src/flood.c.i

CMakeFiles/hyperx.dir/src/flood.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hyperx.dir/src/flood.c.s"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/ACE/game/src/flood.c -o CMakeFiles/hyperx.dir/src/flood.c.s

CMakeFiles/hyperx.dir/src/flood.c.obj.requires:

.PHONY : CMakeFiles/hyperx.dir/src/flood.c.obj.requires

CMakeFiles/hyperx.dir/src/flood.c.obj.provides: CMakeFiles/hyperx.dir/src/flood.c.obj.requires
	$(MAKE) -f CMakeFiles/hyperx.dir/build.make CMakeFiles/hyperx.dir/src/flood.c.obj.provides.build
.PHONY : CMakeFiles/hyperx.dir/src/flood.c.obj.provides

CMakeFiles/hyperx.dir/src/flood.c.obj.provides.build: CMakeFiles/hyperx.dir/src/flood.c.obj


CMakeFiles/hyperx.dir/src/geometry.c.obj: CMakeFiles/hyperx.dir/flags.make
CMakeFiles/hyperx.dir/src/geometry.c.obj: ../src/geometry.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ACE/game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hyperx.dir/src/geometry.c.obj"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hyperx.dir/src/geometry.c.obj   -c /root/ACE/game/src/geometry.c

CMakeFiles/hyperx.dir/src/geometry.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hyperx.dir/src/geometry.c.i"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/ACE/game/src/geometry.c > CMakeFiles/hyperx.dir/src/geometry.c.i

CMakeFiles/hyperx.dir/src/geometry.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hyperx.dir/src/geometry.c.s"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/ACE/game/src/geometry.c -o CMakeFiles/hyperx.dir/src/geometry.c.s

CMakeFiles/hyperx.dir/src/geometry.c.obj.requires:

.PHONY : CMakeFiles/hyperx.dir/src/geometry.c.obj.requires

CMakeFiles/hyperx.dir/src/geometry.c.obj.provides: CMakeFiles/hyperx.dir/src/geometry.c.obj.requires
	$(MAKE) -f CMakeFiles/hyperx.dir/build.make CMakeFiles/hyperx.dir/src/geometry.c.obj.provides.build
.PHONY : CMakeFiles/hyperx.dir/src/geometry.c.obj.provides

CMakeFiles/hyperx.dir/src/geometry.c.obj.provides.build: CMakeFiles/hyperx.dir/src/geometry.c.obj


CMakeFiles/hyperx.dir/src/main.c.obj: CMakeFiles/hyperx.dir/flags.make
CMakeFiles/hyperx.dir/src/main.c.obj: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ACE/game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/hyperx.dir/src/main.c.obj"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hyperx.dir/src/main.c.obj   -c /root/ACE/game/src/main.c

CMakeFiles/hyperx.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hyperx.dir/src/main.c.i"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/ACE/game/src/main.c > CMakeFiles/hyperx.dir/src/main.c.i

CMakeFiles/hyperx.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hyperx.dir/src/main.c.s"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/ACE/game/src/main.c -o CMakeFiles/hyperx.dir/src/main.c.s

CMakeFiles/hyperx.dir/src/main.c.obj.requires:

.PHONY : CMakeFiles/hyperx.dir/src/main.c.obj.requires

CMakeFiles/hyperx.dir/src/main.c.obj.provides: CMakeFiles/hyperx.dir/src/main.c.obj.requires
	$(MAKE) -f CMakeFiles/hyperx.dir/build.make CMakeFiles/hyperx.dir/src/main.c.obj.provides.build
.PHONY : CMakeFiles/hyperx.dir/src/main.c.obj.provides

CMakeFiles/hyperx.dir/src/main.c.obj.provides.build: CMakeFiles/hyperx.dir/src/main.c.obj


CMakeFiles/hyperx.dir/src/mygame.c.obj: CMakeFiles/hyperx.dir/flags.make
CMakeFiles/hyperx.dir/src/mygame.c.obj: ../src/mygame.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ACE/game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/hyperx.dir/src/mygame.c.obj"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hyperx.dir/src/mygame.c.obj   -c /root/ACE/game/src/mygame.c

CMakeFiles/hyperx.dir/src/mygame.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hyperx.dir/src/mygame.c.i"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/ACE/game/src/mygame.c > CMakeFiles/hyperx.dir/src/mygame.c.i

CMakeFiles/hyperx.dir/src/mygame.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hyperx.dir/src/mygame.c.s"
	/opt/amiga/bin/m68k-amigaos-gcc --sysroot=/opt/amiga $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/ACE/game/src/mygame.c -o CMakeFiles/hyperx.dir/src/mygame.c.s

CMakeFiles/hyperx.dir/src/mygame.c.obj.requires:

.PHONY : CMakeFiles/hyperx.dir/src/mygame.c.obj.requires

CMakeFiles/hyperx.dir/src/mygame.c.obj.provides: CMakeFiles/hyperx.dir/src/mygame.c.obj.requires
	$(MAKE) -f CMakeFiles/hyperx.dir/build.make CMakeFiles/hyperx.dir/src/mygame.c.obj.provides.build
.PHONY : CMakeFiles/hyperx.dir/src/mygame.c.obj.provides

CMakeFiles/hyperx.dir/src/mygame.c.obj.provides.build: CMakeFiles/hyperx.dir/src/mygame.c.obj


# Object files for target hyperx
hyperx_OBJECTS = \
"CMakeFiles/hyperx.dir/src/flood.c.obj" \
"CMakeFiles/hyperx.dir/src/geometry.c.obj" \
"CMakeFiles/hyperx.dir/src/main.c.obj" \
"CMakeFiles/hyperx.dir/src/mygame.c.obj"

# External object files for target hyperx
hyperx_EXTERNAL_OBJECTS =

../hyperx: CMakeFiles/hyperx.dir/src/flood.c.obj
../hyperx: CMakeFiles/hyperx.dir/src/geometry.c.obj
../hyperx: CMakeFiles/hyperx.dir/src/main.c.obj
../hyperx: CMakeFiles/hyperx.dir/src/mygame.c.obj
../hyperx: CMakeFiles/hyperx.dir/build.make
../hyperx: ace/libace.a
../hyperx: ../src/music_ptr_linkable.o
../hyperx: CMakeFiles/hyperx.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/ACE/game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ../hyperx"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hyperx.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hyperx.dir/build: ../hyperx

.PHONY : CMakeFiles/hyperx.dir/build

CMakeFiles/hyperx.dir/requires: CMakeFiles/hyperx.dir/src/flood.c.obj.requires
CMakeFiles/hyperx.dir/requires: CMakeFiles/hyperx.dir/src/geometry.c.obj.requires
CMakeFiles/hyperx.dir/requires: CMakeFiles/hyperx.dir/src/main.c.obj.requires
CMakeFiles/hyperx.dir/requires: CMakeFiles/hyperx.dir/src/mygame.c.obj.requires

.PHONY : CMakeFiles/hyperx.dir/requires

CMakeFiles/hyperx.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hyperx.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hyperx.dir/clean

CMakeFiles/hyperx.dir/depend:
	cd /root/ACE/game/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ACE/game /root/ACE/game /root/ACE/game/build /root/ACE/game/build /root/ACE/game/build/CMakeFiles/hyperx.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hyperx.dir/depend

