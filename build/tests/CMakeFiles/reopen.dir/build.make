# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\lib\glfw-3.3.6"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\build"

# Include any dependencies generated for this target.
include tests/CMakeFiles/reopen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/reopen.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/reopen.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/reopen.dir/flags.make

tests/CMakeFiles/reopen.dir/reopen.c.obj: tests/CMakeFiles/reopen.dir/flags.make
tests/CMakeFiles/reopen.dir/reopen.c.obj: tests/CMakeFiles/reopen.dir/includes_C.rsp
tests/CMakeFiles/reopen.dir/reopen.c.obj: C:/Users/Maxime/Documents/UQAC/Maths\ Appli/INF935-BARBE-CAILLES-ZAFFUTO/lib/glfw-3.3.6/tests/reopen.c
tests/CMakeFiles/reopen.dir/reopen.c.obj: tests/CMakeFiles/reopen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/reopen.dir/reopen.c.obj"
	cd /d C:\Users\Maxime\DOCUME~1\UQAC\MATHSA~1\INF935~2\build\tests && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/reopen.dir/reopen.c.obj -MF CMakeFiles\reopen.dir\reopen.c.obj.d -o CMakeFiles\reopen.dir\reopen.c.obj -c "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\lib\glfw-3.3.6\tests\reopen.c"

tests/CMakeFiles/reopen.dir/reopen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reopen.dir/reopen.c.i"
	cd /d C:\Users\Maxime\DOCUME~1\UQAC\MATHSA~1\INF935~2\build\tests && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\lib\glfw-3.3.6\tests\reopen.c" > CMakeFiles\reopen.dir\reopen.c.i

tests/CMakeFiles/reopen.dir/reopen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reopen.dir/reopen.c.s"
	cd /d C:\Users\Maxime\DOCUME~1\UQAC\MATHSA~1\INF935~2\build\tests && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\lib\glfw-3.3.6\tests\reopen.c" -o CMakeFiles\reopen.dir\reopen.c.s

tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.obj: tests/CMakeFiles/reopen.dir/flags.make
tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.obj: tests/CMakeFiles/reopen.dir/includes_C.rsp
tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.obj: C:/Users/Maxime/Documents/UQAC/Maths\ Appli/INF935-BARBE-CAILLES-ZAFFUTO/lib/glfw-3.3.6/deps/glad_gl.c
tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.obj: tests/CMakeFiles/reopen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.obj"
	cd /d C:\Users\Maxime\DOCUME~1\UQAC\MATHSA~1\INF935~2\build\tests && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.obj -MF CMakeFiles\reopen.dir\__\deps\glad_gl.c.obj.d -o CMakeFiles\reopen.dir\__\deps\glad_gl.c.obj -c "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\lib\glfw-3.3.6\deps\glad_gl.c"

tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reopen.dir/__/deps/glad_gl.c.i"
	cd /d C:\Users\Maxime\DOCUME~1\UQAC\MATHSA~1\INF935~2\build\tests && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\lib\glfw-3.3.6\deps\glad_gl.c" > CMakeFiles\reopen.dir\__\deps\glad_gl.c.i

tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reopen.dir/__/deps/glad_gl.c.s"
	cd /d C:\Users\Maxime\DOCUME~1\UQAC\MATHSA~1\INF935~2\build\tests && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\lib\glfw-3.3.6\deps\glad_gl.c" -o CMakeFiles\reopen.dir\__\deps\glad_gl.c.s

# Object files for target reopen
reopen_OBJECTS = \
"CMakeFiles/reopen.dir/reopen.c.obj" \
"CMakeFiles/reopen.dir/__/deps/glad_gl.c.obj"

# External object files for target reopen
reopen_EXTERNAL_OBJECTS =

tests/reopen.exe: tests/CMakeFiles/reopen.dir/reopen.c.obj
tests/reopen.exe: tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.obj
tests/reopen.exe: tests/CMakeFiles/reopen.dir/build.make
tests/reopen.exe: src/libglfw3.a
tests/reopen.exe: tests/CMakeFiles/reopen.dir/linklibs.rsp
tests/reopen.exe: tests/CMakeFiles/reopen.dir/objects1.rsp
tests/reopen.exe: tests/CMakeFiles/reopen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable reopen.exe"
	cd /d C:\Users\Maxime\DOCUME~1\UQAC\MATHSA~1\INF935~2\build\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\reopen.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/reopen.dir/build: tests/reopen.exe
.PHONY : tests/CMakeFiles/reopen.dir/build

tests/CMakeFiles/reopen.dir/clean:
	cd /d C:\Users\Maxime\DOCUME~1\UQAC\MATHSA~1\INF935~2\build\tests && $(CMAKE_COMMAND) -P CMakeFiles\reopen.dir\cmake_clean.cmake
.PHONY : tests/CMakeFiles/reopen.dir/clean

tests/CMakeFiles/reopen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\lib\glfw-3.3.6" "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\lib\glfw-3.3.6\tests" "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\build" "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\build\tests" "C:\Users\Maxime\Documents\UQAC\Maths Appli\INF935-BARBE-CAILLES-ZAFFUTO\build\tests\CMakeFiles\reopen.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : tests/CMakeFiles/reopen.dir/depend

