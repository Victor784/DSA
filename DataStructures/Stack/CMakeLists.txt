cmake_minimum_required(VERSION 3.25)
project(Stack)

message("-> Stack generation started...")

add_library(Stack INTERFACE)

target_include_directories(Stack INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Stack
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
) 
message("-> Finished Stack generation...")