#include <cassert>
#include <cmath>
#include <iostream>

// exercise 1 - Circle

inline static const double pi = 3.14159265358979323846;

double circArea(double radius) { return radius * radius * pi; }
float circArea(float radius) { return radius * radius * (float)pi; }

// exercise 2 - Factorial

unsigned int factorial(unsigned int num) {
  unsigned int result = 1;
  while (num > 0) {
    result *= num--;
  }
  return result;
}

// exercise 3 - Prime

bool isPrime(int num) {
  if (0 == num || 1 == num || -1 == num) {
    return false;
  }
  if (num < 0) {
    num *= -1;
  }
  if (num == 2 || num == -2) {
    return true;
  }
  if (num % 2 == 0) {
    return false;
  }

  int upperLimit = sqrt(abs(num));
  for (int i = 3; i <= upperLimit; i += 2) {
    if (num % i == 0)
      return false;
  }
  return true;
}

// exercise 3 - Fibonacci

unsigned int fibonacci(unsigned int n) {
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

// exercise 4 - Palindrome

inline static bool isPalindromeTwoDigit(unsigned int n) {
  if (n == 11 || //
      n == 22 || //
      n == 33 || //
      n == 44 || //
      n == 55 || //
      n == 66 || //
      n == 77 || //
      n == 88 || //
      n == 99) {
    return true;
  } else {
    return false;
  }
}

inline static unsigned int removeFirstDigit(unsigned int n) {
  unsigned int numberOfDigits = (unsigned int)log10((double)n) + 1;
  assert(numberOfDigits > 1);
  unsigned int offset = pow(10, numberOfDigits - 1);
  return n - offset * (n / offset);
}

inline static unsigned int removeLastDigit(unsigned int n) {
  return (n - (n % 10)) / 10;
}

bool isPalindrome(unsigned int n) {
  if (n < 10) {
    return true;
  }
  if (isPalindromeTwoDigit(n)) {
    return true;
  }
  if (n < 100) {
    return false;
  }

  const unsigned int last_digit = n - 10 * removeLastDigit(n);

  const unsigned int num_of_digits = (unsigned int)log10((double)n);
  const unsigned int first_digit =
      (n - removeFirstDigit(n)) / (pow(10, num_of_digits));

  if (first_digit != last_digit) {
    return false;
  } else {
    n = removeFirstDigit(removeLastDigit(n));
    if (n < 10) {
      return true;
    }
    return isPalindrome(n);
  }
}

// TESTS

static inline void testPalindrone() {
  try {
    assert(isPalindrome(3223) == true);
    assert(isPalindrome(32) == false);
    assert(isPalindrome(22) == true);
    assert(isPalindrome(121) == true);
    assert(isPalindrome(111) == true);
    assert(isPalindrome(123) == false);
    assert(isPalindrome(11331) == false);
    assert(isPalindrome(322) == false);
    std::cout << "INFO: All tests for palindrome passed successfully!"
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "ERROR: Palindrome test failed: " << e.what() << std::endl;
  }
}

static inline void testFibonacci() {
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
    std::cout << "INFO: All tests for fibonacci passed successfully!"
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "ERROR: Fibonacci test failed: " << e.what() << std::endl;
  }
}

static inline void testFactorial() {
  try {
    assert(factorial(0) == 1);
    assert(factorial(1) == 1);
    assert(factorial(2) == 2);
    assert(factorial(3) == 6);
    assert(factorial(4) == 24);
    assert(factorial(5) == 120);
    assert(factorial(6) == 720);
    assert(factorial(7) == 5040);
    assert(factorial(8) == 40320);
    assert(factorial(9) == 362880);
    std::cout << "INFO: All tests for factorial passed successfully!"
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "ERROR: Factorial test failed: " << e.what() << std::endl;
  }
}

static inline void testPrime() {
  try {
    // positive
    assert(isPrime(0) == false);
    assert(isPrime(1) == false);
    assert(isPrime(2) == true);
    assert(isPrime(3) == true);
    assert(isPrime(4) == false);
    assert(isPrime(5) == true);
    assert(isPrime(6) == false);
    assert(isPrime(7) == true);
    assert(isPrime(8) == false);
    assert(isPrime(9) == false);
    // negative
    assert(isPrime(-1) == false);
    assert(isPrime(-2) == true);
    assert(isPrime(-3) == true);
    assert(isPrime(-4) == false);
    assert(isPrime(-5) == true);
    assert(isPrime(-6) == false);
    assert(isPrime(-7) == true);
    assert(isPrime(-8) == false);
    assert(isPrime(-9) == false);
    // large
    assert(isPrime(104729) == true);
    assert(isPrime(104731) == false);
    std::cout << "INFO: All tests for factorial passed successfully!"
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "ERROR: Factorial test failed: " << e.what() << std::endl;
  }
}

// Run tests

int main() {
  testPrime();
  testPalindrone();
  testFactorial();
  testFibonacci();
  return 0;
}
