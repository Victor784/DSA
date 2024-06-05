cmake_minimum_required(VERSION 3.25)
project(Queue)

message("-> Queue generation started...")

add_library(Queue INTERFACE)

target_include_directories(Queue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Stack
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
) 
message("-> Finished Queue generation...")