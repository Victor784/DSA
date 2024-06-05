cmake_minimum_required(VERSION 3.25)
project(DataStructuresProject)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

message("-> CMake generation started...")
#Modules
add_subdirectory(src/DynamicArray)
add_subdirectory(src/LinkedLists)
add_subdirectory(src/Stack)
add_subdirectory(src/Queue)
add_subdirectory(src/HashTable)


add_library(DataStructures INTERFACE)

#Linking
target_link_libraries(DataStructures INTERFACE DynamicArray)
target_link_libraries(DataStructures INTERFACE LinkedLists)
target_link_libraries(DataStructures INTERFACE Stack)
target_link_libraries(DataStructures INTERFACE Queue)
target_link_libraries(DataStructures INTERFACE HashTable)

install(TARGETS DataStructures
        EXPORT DataStructuresTargets
        INCLUDES DESTINATION include
)
message("-> CMake generation finished successfully...")

#Testing framework 
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(googletest EXCLUDE_FROM_ALL)
enable_testing()


# add; link; and catalog tests
# DynamicArrayTest fixture
add_executable(DynamicArrayTest test/DynamicArrayTest.cpp)
set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/lib")
target_include_directories(DynamicArrayTest PUBLIC ${HEADERS_DIR})
target_link_libraries(DynamicArrayTest gtest gtest_main DynamicArray)
add_test(NAME DynamicArrayTest COMMAND DynamicArrayTest)

# LinkedLists fixture
add_executable(LinkedListsTest test/LinkedListsTest.cpp)
set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/lib")
target_include_directories(LinkedListsTest PUBLIC ${HEADERS_DIR})
target_link_libraries(LinkedListsTest gtest gtest_main LinkedLists)
add_test(NAME LinkedListsTest COMMAND LinkedListsTest)

# Stack fixture
add_executable(StackTest test/StackTest.cpp)
set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/lib")
target_include_directories(StackTest PUBLIC ${HEADERS_DIR})
target_link_libraries(StackTest gtest gtest_main Stack)
add_test(NAME StackTest COMMAND StackTest)

# Queue fixture
add_executable(QueueTest test/QueueTest.cpp)
set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/lib")
target_include_directories(QueueTest PUBLIC ${HEADERS_DIR})
target_link_libraries(QueueTest gtest gtest_main Queue)
add_test(NAME QueueTest COMMAND QueueTest)

# HashTable fixture
add_executable(HashTableTest test/HashTableTest.cpp)
set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/lib")
target_include_directories(HashTableTest PUBLIC ${HEADERS_DIR})
target_link_libraries(HashTableTest gtest gtest_main HashTable)
add_test(NAME HashTableTest COMMAND HashTableTest)

add_dependencies(DynamicArrayTest DynamicArray)
add_dependencies(LinkedListsTest LinkedLists )
add_dependencies(StackTest Stack )
add_dependencies(QueueTest Queue )
add_dependencies(HashTableTest HashTable )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Some other fixture
#add_executable(SomeOtherTest test/SomeOtherTest.cpp)
#set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/lib")
#target_include_directories(SomeOtherTest PUBLIC ${HEADERS_DIR})
#target_link_libraries(SomeOtherTest gtest gtest_main SomeOtherDependency)
#add_test(NAME SomeOtherTest COMMAND SomeOtherTest)