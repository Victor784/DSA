#!/bin/bash

(

cd "build/Debug"

for exe_file in *.exe; do
    # Check if the file is executable
    if [ -x "$exe_file" ]; then
        # Run the executable
        "./$exe_file"
    else
        echo "Error: $exe_file is not executable."
    fi
done
)