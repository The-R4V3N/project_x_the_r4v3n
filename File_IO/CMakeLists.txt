cmake_minimum_required(VERSION 3.10)

set(app cmake_gernerated_app)
set(fileName File_Io)

project(${fileName})

set(Headers 
    File_Io.h
)

set(Sources 
    File_Io.cpp
)

add_library(${app} STATIC ${Sources} ${Headers})
add_executable(File_Io File_Io.cpp)
target_link_libraries(File_Io PRIVATE ${app})