cmake_minimum_required(VERSION 3.25)
project(DataStructuresProject)
set(CMAKE_CXX_STANDARD 20)


message("-> CMake generation started...")
#Modules
add_subdirectory(DynamicArray)
add_subdirectory(LinkedLists)
add_subdirectory(Stack)

add_library(DataStructures INTERFACE)

#Linking
target_link_libraries(DataStructures INTERFACE DynamicArray)
target_link_libraries(DataStructures INTERFACE LinkedLists)
target_link_libraries(DataStructures INTERFACE Stack)

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

add_dependencies(DynamicArrayTest DynamicArray)
add_dependencies(LinkedListsTest LinkedLists )
add_dependencies(StackTest Stack )

# Some other fixture
#add_executable(SomeOtherTest test/SomeOtherTest.cpp)
#set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/lib")
#target_include_directories(SomeOtherTest PUBLIC ${HEADERS_DIR})
#target_link_libraries(SomeOtherTest gtest gtest_main SomeOtherDependency)
#add_test(NAME SomeOtherTest COMMAND SomeOtherTest)

