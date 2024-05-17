#include <iostream>
#include <optional>

unsigned int factorial(unsigned int num) {
  uint result = 1;
  while (num > 0) {
    result *= num--;
  }
  return result;
}

std::optional<int> factorial(int num) {
  if (num < 0) {
    return std::nullopt;
  }
  int result = 1;
  while (num > 0) {
    result *= num--;
  }
  return result;
}

int main() {
  for (unsigned int i = 0; i < 13; i++) {
    std::cout << "The factorial of: " << i << " is: " << factorial(i)
              << std::endl;
  }
  for (int i = -3; i < 13; i++) {
    auto factorial_i = factorial(i);
    if (!factorial_i.has_value()) {
      continue;
    }
    std::cout << "The factorial of: " << i << " is: " << factorial_i.value()
              << std::endl;
  }
  return 0;
}
