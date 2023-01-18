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
add_library(File_Io_lib ${SourcesLib})


# Adding the executable
add_executable(my_app ${SourcesApp})

# Link mmy library to an executable
target_link_libraries(my_app File_Io_lib)