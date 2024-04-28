CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Wpedantic
TARGET=main

.PHONY: all clean help test

all: $(TARGET)

$(TARGET): main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

test: $(TARGET)
	@echo "Example test with weight 70kg and height 1.75m"
	./$(TARGET) --mass=70 --height=1.75 
	@echo "Example test with weight 70kg and height 1.75m and Treften measure"
	./$(TARGET) --mass=70 --height=1.75 --treften 

help:
	@echo "Usage: make [target]"
	@echo "Targets:"
	@echo "  all       : Compile the program (default)"
	@echo "  test      : Run tests"
	@echo "  clean     : Remove compiled files"
	@echo "  help      : Display this help message (default)"

clean:
	rm -f $(TARGET) *.o
