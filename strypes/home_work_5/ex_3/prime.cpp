#include <cmath>
#include <iostream>

bool isPrime(int num) {
  if (0 == num || 1 == num || -1 == num) {
    return false;
  }
  if (num < 0) {
    num *= -1;
  }
  if (num % 2 == 0) {
    return true;
  }

  int upperLimit = sqrt(abs(num));
  for (int i = 3; i <= upperLimit; i += 2) {
    if (num % i == 0)
      return false;
  }
  return true;
}

int main() {
  for (int i = -10; i < 10; i++) {
    std::cout << "Number " << i << " is prime: " << isPrime(i) << std::endl;
  }
}
