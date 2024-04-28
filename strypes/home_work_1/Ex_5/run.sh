#! /usr/bin/bash

# Find the largest number
largest=$(sort -rn numbers.txt | head -n 1)
echo "The largest number is: $largest"

# Find the smallest number
smallest=$(sort -n numbers.txt | head -n 1)
echo "The smallest number is: $smallest"
