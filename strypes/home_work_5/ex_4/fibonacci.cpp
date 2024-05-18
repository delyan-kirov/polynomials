#include <cassert>
#include <iostream>

inline unsigned int fibonacci(unsigned int n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1 || n == 2) {
    return 1;
  }

  int n_prev = 1;
  int n_curr = 1;

  while (n - 2) {
    int keeper = n_curr;
    n_curr += n_prev;
    n_prev = keeper;
    n--;
  }
  return n_curr;
}

// Test function to assert Fibonacci sequence
bool testFibonacci() {
  try {
    assert(fibonacci(0) == 0);
    assert(fibonacci(1) == 1);
    assert(fibonacci(2) == 1);
    assert(fibonacci(3) == 2);
    assert(fibonacci(4) == 3);
    assert(fibonacci(5) == 5);
    assert(fibonacci(6) == 8);
    assert(fibonacci(7) == 13);
    assert(fibonacci(8) == 21);
    assert(fibonacci(9) == 34);
    std::cout << "All tests passed successfully!" << std::endl;
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Test failed: " << e.what() << std::endl;
    return false;
  }
}

int main() {
  if (!testFibonacci()) {
    return 1;
  }
  return 0;
}
