# Makefile for compiling tail.cpp with g++

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra

# Target executable
TARGET := tail

# Source files
SRCS := tail.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Rule for linking object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule for compiling source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) $(OBJS)
