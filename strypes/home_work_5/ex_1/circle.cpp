#include <iostream>

inline const static double pi = 3.14159265358979323846;

double circArea(double radius) { return radius * radius * pi; }
float circArea(float radius) { return radius * radius * (float)pi; }

int main() {
  double radius = 2.3;
  std::cout << "Area with radius: " << radius << " is: " << circArea(radius)
            << "\n";
  return 0;
}
