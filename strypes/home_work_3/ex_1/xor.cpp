#include <iostream>

int fn_xor(int a, int b) { return (a || b) && !(a && b); }

int main() {
  int a, b;
  if (!(std::cin >> a >> b) || (a != 0 && a != 1) || (b != 0 && b != 1)) {
    std::cerr << "Error: Input is not 0 or 1" << std::endl;
    return 1; // Return error code
  }
  std::cout << fn_xor(a, b) << std::endl;
  return 0;
}
