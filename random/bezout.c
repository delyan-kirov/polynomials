#include <stdio.h>

const int a = 16;
const int b = 12;

struct BezoutCoefs {
  int fst;
  int snd;
  int gcd;
};

struct BezoutCoefs bezout(int a, int b) {
  int old_r = a;
  int r = b;
  int old_s = 1;
  int s = 0;

  int quotient = 0;
  int keeper = 0;

  struct BezoutCoefs result = {
      0,
      0,
      0,
  };

  while (r != 0) {
    quotient = old_r / r;

    keeper = r;
    r = old_r - quotient * keeper;
    old_r = keeper;

    keeper = s;
    s = old_s - quotient * keeper;
    old_s = keeper;
  }

  int bezout_t = b != 0 ? (old_r - old_s * a) / b : 0;

  result.fst = old_s;
  result.snd = bezout_t;
  result.gcd = old_r;

  return result;
}

int gcd(int a, int b) {
  int keeper = 0;
  int a1 = a;
  int b1 = b;

  while (b1 != 0) {
    keeper = b1;
    b1 = a1 % b1;
    a1 = keeper;
  }

  return keeper;
}

int main() {
  int result_gcd = gcd(a, b);
  struct BezoutCoefs result_bezout = bezout(a, b);

  printf("The result of gcd is: %d\n", result_gcd);
  printf("The result of bezout is: (%d, %d, %d)\n", result_bezout.fst,
         result_bezout.snd, result_bezout.gcd);

  return 0;
}
