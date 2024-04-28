#!/bin/bash

# Name of the project's source directory

SCRIPT_DIR=$(realpath "$(dirname "$0")")

SOURCE_DIR="${SCRIPT_DIR}"

# Path to your the build directory
BUILD_DIR="${SOURCE_DIR}/build"

# Create the build directory if it doesn't exist
mkdir -p "${BUILD_DIR}"
(
# Change directory to the build directory
cd "${BUILD_DIR}"

echo $(pwd)
# Run CMake configuration
cmake ".."
)