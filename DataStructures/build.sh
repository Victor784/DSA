#!/bin/bash

SCRIPT_DIR=$(realpath "$(dirname "$0")")

# Change directory to the build directory
cd "${SCRIPT_DIR}/build"

# Run CMake build
cmake --build .

# Lib and header ease of use 
cd ".."
mkdir -p "lib"
cd "lib"

# Destination directory
DEST_DIR="$(pwd)"

# Source directory - add here all hpp headers once created

DYNAMICARRAY_HEADER_SOURCE="${SCRIPT_DIR}/DynamicArray/DynamicArray.hpp"
SINGLYLINKEDLISTS_HEADER_SOURCE="${SCRIPT_DIR}/LinkedLists/SinglyLinkedList.hpp"
DOUBLYLINKEDLISTS_HEADER_SOURCE="${SCRIPT_DIR}/LinkedLists/DoublyLinkedList.hpp"
STACK_HEADER_SOURCE="${SCRIPT_DIR}/Stack/Stack.hpp"
QUEUE_HEADER_SOURCE="${SCRIPT_DIR}/Queue/Queue.hpp"
HASHTABLE_HEADER_SOURCE="${SCRIPT_DIR}/HashTable/HashTable.hpp"
#echo ${DYNAMICARRAY_HEADER_SOURCE}
#echo ${DEST_DIR}

# Copy the source header to the destination directory  copy the headers
cp  "${DYNAMICARRAY_HEADER_SOURCE}" "${DEST_DIR}"
cp  "${SINGLYLINKEDLISTS_HEADER_SOURCE}" "${DEST_DIR}"
cp  "${DOUBLYLINKEDLISTS_HEADER_SOURCE}" "${DEST_DIR}"
cp  "${STACK_HEADER_SOURCE}" "${DEST_DIR}"
cp  "${QUEUE_HEADER_SOURCE}" "${DEST_DIR}"
cp  "${HASHTABLE_HEADER_SOURCE}" "${DEST_DIR}"


# automatic find and copy of all .lib files compiled and existing

#cd "../build/lib/Debug"
#find . -type f -name "*.lib" -exec cp {} "${DEST_DIR}" \;
