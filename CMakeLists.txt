cmake_minimum_required(VERSION 3.10)

PROJECT(PoC) #Proof Of Concept

add_subdirectory (File_IO)
add_subdirectory (CAN_Messages)
add_subdirectory (Main_Components)

message(STATUS "Generated Include path = ${CAN_Messages_INCLUDE_DIR}, sources = ${CAN_Messages_SOURCES}")

