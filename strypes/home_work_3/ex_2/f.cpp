#include <cstdio>
#include <iostream>

int zero_based(int a, int b, int c) {
  return (a || b || !c)      //
         && (!a || b || c)   //
         && (!a || b || !c)  //
         && (!a || !b || c); //
}

int one_based(int a, int b, int c) {
  return (!a && !b && !c)   //
         || (!a && b && !c) //
         || (!a && b && c)  //
         || (a && b && c);  //
}

// formula from [[https://www.boolean-algebra.com/kmap/]]
int reduced(int a, int b, int c) { return (!a && !c) || (b && c); }

int table(int a, int b, int c) {
  if (a == 0 && b == 0 && c == 0) {
    return 1;
  }
  if (a == 0 && b == 0 && c == 1) {
    return 0;
  }
  if (a == 0 && b == 1 && c == 0) {
    return 1;
  }
  if (a == 0 && b == 1 && c == 1) {
    return 1;
  }
  if (a == 1 && b == 0 && c == 0) {
    return 0;
  }
  if (a == 1 && b == 0 && c == 1) {
    return 0;
  }
  if (a == 1 && b == 1 && c == 0) {
    return 0;
  }
  if (a == 1 && b == 1 && c == 1) {
    return 0;
  }
  return 1; // dummy return
}

bool test() {
  for (int i = 0; i <= 1; i++) {
    for (int j = 0; j <= 1; j++) {
      for (int k = 0; k <= 1; k++) {
        if (zero_based(i, j, k) != one_based(i, j, k) ||
            zero_based(i, j, k) != reduced(i, j, k) ||
            one_based(i, j, k) != reduced(i, j, k)) {
          printf("TEST: failed using parameters (%d, %d, %d)", i, j, k);
          return false;
        }
      }
    }
  }
  return true;
}

int main() {
  int a, b, c;
  if (!(std::cin >> a >> b >> c) || (a != 0 && a != 1) || (b != 0 && b != 1) ||
      (c != 0 && c != 1)) {
    std::cerr << "Error: Input is not 0 or 1" << std::endl;
    return 1;
  }
  std::cout << reduced(a, b, c) << std::endl;
  // test();
  // std::cout << zero_based(a, b, c) << std::endl;
  // std::cout << one_based(a, b, c) << std::endl;
  return 0;
}
