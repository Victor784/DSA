cmake_minimum_required(VERSION 3.25)
project(BinaryTree)

message("-> BinaryTree generation started...")

add_library(BinaryTree INTERFACE)

target_include_directories(BinaryTree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(BinaryTree
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
) 
message("-> Finished BinaryTree generation...")