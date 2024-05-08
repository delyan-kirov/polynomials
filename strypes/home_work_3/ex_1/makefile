CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra

.PHONY: all clean test numbers

all: xor numbers test

# create executable
xor: xor.cpp
	$(CXX) $(CXXFLAGS) -o xor xor.cpp

# create the numbers.txt file and add 1 0
numbers:
	echo "1 0" > numbers.txt

# test program with the run.sh script
test:
	echo Runnng test with 1 and 0
	bash run.sh

clean:
	rm -f xor
