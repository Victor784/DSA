cmake_minimum_required(VERSION 3.25)
project(DynamicArray)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/DynamicArray.cpp ${CMAKE_CURRENT_SOURCE_DIR}/DynamicArray.hpp)
message("-> DynamicArray generation started...")

add_library(DynamicArray ${SOURCES})

target_include_directories(DynamicArray PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(DynamicArray
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
) 
message("-> Finished DynamicArray generation...")