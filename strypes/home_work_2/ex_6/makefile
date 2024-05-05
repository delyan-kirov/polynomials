# Makefile for wc

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++11

# Source files
SRCS = wc.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = wc

# Default rule
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	rm -f $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Test rule
.PHONY: test
test:
	wc wc.cpp
	wc makefile

# Clean rule
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
