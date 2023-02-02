
cmake_minimum_required(VERSION 3.10)

project(project_x, CXX)

set(sources src/main.cpp)

include_directories(${CAN_Messages_INCLUDE_DIR})
include_directories(${FIlE_IO_INCLUDE_DIR})

add_executable (main_component ${sources} ${CAN_Messages_SOURCE})

#it tells to cmake to build the target "generate_sources_from_json" BEFORE "main_component"
add_dependencies (main_component generate_sources_from_json)

target_link_libraries(main_component FIlE_IO)



