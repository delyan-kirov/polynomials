#! /usr/bin/bash

file="numbers.txt"

# Check if the file exists
if [ ! -f "$file" ]; then
    echo "Error: File 'numbers.txt' does not exist."
    exit 1
fi

# Read numbers from the file
./xor < "$file"
