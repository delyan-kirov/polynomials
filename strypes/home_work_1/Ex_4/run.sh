#!/usr/bin/bash

# Check if numbers.txt exists
if [ ! -f "numbers.txt" ]; then
    echo "Error: numbers.txt not found."
    exit 1
fi

# Execute the C++ program with stdin redirected to numbers.txt
echo "Executing C++ program with input from numbers.txt..."
./main < numbers.txt
