# Makefile for Exercise 1

# Define the compiler
CC := g++

# Define compilation flags
CFLAGS := -Wall -Wextra -std=c++11

# Define targets and dependencies
.PHONY: all clean

# Set the default goal to be 'all'
.DEFAULT_GOAL := all

# Target: all
all: program clean

# Target: program
program: program.o swap.o
	$(CC) $^ -o $@

# Target: program.o
program.o: program.cpp
	$(CC) -E $< -o program.i
	$(CC) -S program.i -o program.s
	$(CC) -c program.s -o $@

# Target: swap.o
swap.o: swap.cpp
	$(CC) -E $< -o swap.i
	$(CC) -S swap.i -o swap.s
	$(CC) -c swap.s -o $@

# Target: clean
clean:
	rm -f *.o *.i *.s
