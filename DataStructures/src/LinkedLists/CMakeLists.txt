cmake_minimum_required(VERSION 3.25)
project(LinkedLists)

message("-> LinkedLists generation started...")

add_library(LinkedLists INTERFACE)

target_include_directories(LinkedLists INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(LinkedLists
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
) 
message("-> Finished LinkedLists generation...")