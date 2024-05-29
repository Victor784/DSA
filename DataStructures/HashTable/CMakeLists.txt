cmake_minimum_required(VERSION 3.25)
project(HashTable)

message("-> HashTable generation started...")

add_library(HashTable INTERFACE)

target_include_directories(HashTable INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(HashTable
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
) 
message("-> Finished HashTable generation...")