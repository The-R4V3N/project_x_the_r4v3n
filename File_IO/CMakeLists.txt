cmake_minimum_required(VERSION 3.10)

set(app cmake_gernerated_app)
set(fileName File_Io)

# set a project name
project(${fileName})

set(Headers 
    File_Io.h
)

set(SourcesLib 
    lib/src/File_Io.cpp
)

set(SourcesApp 
   app/src/main.cpp
)

# tell cmake to search for header files in lib/include folder
include_directories(lib/include)

# we are telling to cmake to build a library from source code
add_library(File_Io ${SourcesLib})

# Adding the executable
add_executable(my_app ${SourcesApp})

# Link mmy library to an executable
target_link_libraries(my_app File_Io)

#GoogleTest part

#include CMake module to be able to download GoogleTest code.
include(FetchContent)

# Declare git repo and tag to fetch:
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

#Download or check that googletest is downloaded:
FetchContent_MakeAvailable(googletest)

# Built Unity Test
add_executable(lib_ut_tests lib/ut/test.cpp   )
target_link_libraries(lib_ut_tests gtest gtest_main File_Io)

#lib/ut/ut_lib_test.cpp