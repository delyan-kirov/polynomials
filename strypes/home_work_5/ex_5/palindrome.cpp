#include <cassert>
#include <cmath>
#include <iostream>

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

void runTest() {
  try {
    assert(isPalindrome(3223) == true);
    assert(isPalindrome(32) == false);
    assert(isPalindrome(22) == true);
    assert(isPalindrome(121) == true);
    assert(isPalindrome(111) == true);
    assert(isPalindrome(123) == false);
    assert(isPalindrome(11331) == false);
    assert(isPalindrome(322) == false);
    std::cout << "All tests passed successfully!\n";
  } catch (const std::exception &e) {
    std::cerr << "Error occurred: " << e.what() << std::endl;
  }
}

int main() {
  runTest();
  return 0;
}
