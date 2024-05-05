# Makefile for ex_2

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++11

# Source files
SRCS = compare.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = compare

# Default rules
.DEFAULT_GOAL := all
all: $(TARGET) clean

# Rule to run tests and write output to result.txt
.PHONY: test
test: $(TARGET)
	./$(TARGET) > result.txt

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
.PHONY: clean
clean:
	rm -f $(OBJS)
