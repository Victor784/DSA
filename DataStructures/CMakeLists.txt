cmake_minimum_required(VERSION 3.25)
project(DataStructuresProject)
set(CMAKE_CXX_STANDARD 20)


message("-> CMake generation started...")
#Modules
add_subdirectory(DynamicArray)

add_library(DataStructures INTERFACE)

#Linking
target_link_libraries(DataStructures INTERFACE DynamicArray)

install(TARGETS DataStructures
        EXPORT DataStructuresTargets
        INCLUDES DESTINATION include
)
message("-> CMake generation finished successfully...")