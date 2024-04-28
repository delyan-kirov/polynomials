#include <iostream>
#include <sstream>
#include <string>

int main() {
  double num1, num2, num3;
  std::string line;

  // Prompt the user to enter three real numbers line by line
  std::cout << "Enter three real numbers, one per line:\n";

  // Read the first number
  std::cout << "Number 1: ";
  if (!std::getline(std::cin, line)) {
    std::cerr << "Error: Failed to read input.\n";
    return 1;
  }
  std::istringstream(line) >> num1;

  // Read the second number
  std::cout << "Number 2: ";
  if (!std::getline(std::cin, line)) {
    std::cerr << "Error: Failed to read input.\n";
    return 1;
  }
  std::istringstream(line) >> num2;

  // Read the third number
  std::cout << "Number 3: ";
  if (!std::getline(std::cin, line)) {
    std::cerr << "Error: Failed to read input.\n";
    return 1;
  }
  std::istringstream(line) >> num3;

  // Find the largest number
  double max_num = num1;
  if (num2 > max_num) {
    max_num = num2;
  }
  if (num3 > max_num) {
    max_num = num3;
  }

  // Output the largest number
  std::cout << "The largest number is: " << max_num << std::endl;

  return 0;
}
