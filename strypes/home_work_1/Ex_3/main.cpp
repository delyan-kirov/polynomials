#include <cmath>
#include <iostream>
#include <string>

static const double pi = 3.14159265358979323846; // Define pi

// Function to calculate the volume of a cylinder
double calculateCylinderVolumeUp(double radius, double height) {
  return pi * pow(radius, 2) * height; // Volume formula for a cylinder
}

// Function to calculate the volume of a cylinder oriented sideways
double calculateCylinderVolumeLateral(double radius, double height,
                                      double length) {
  return pi * pow(radius, 2) *
         length; // Volume formula for a cylinder oriented sideways
}

int main(int argc, char *argv[]) {
  double radius = 0.0;
  double height = 0.0;
  double length = 0.0;
  bool up = false;
  bool down = false;

  // Parse command-line arguments
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.substr(0, 9) == "--radius=") {
      radius = std::stod(arg.substr(9));
    } else if (arg.substr(0, 9) == "--height=") {
      height = std::stod(arg.substr(9));
    } else if (arg.substr(0, 9) == "--length=") {
      length = std::stod(arg.substr(9));
    } else if (arg == "--up") {
      up = true;
    } else if (arg == "--down") {
      down = true;
    } else if (arg == "--help") {
      std::cout << "Usage: " << argv[0]
                << " --radius=value --height=value [--up] [--down] [--help]\n";
      return 0;
    }
  }

  // Check if either radius or height is not provided or non-positive
  if (radius <= 0 || height <= 0) {
    std::cerr << "Error: Both radius and height must be positive values.\n";
    return 1;
  }

  // Check if both up and down are set
  if (up && down) {
    std::cerr << "Error: Both --up and --down options cannot be set "
                 "simultaneously.\n";
    return 1;
  }

  if (up) {
    double volume = calculateCylinderVolumeUp(radius, height);
    std::cout << "The cylinder is oriented upwards." << std::endl
              << "The volume of the cylinder is: " << volume << std::endl;
  }

  if (down) {
    double volume = calculateCylinderVolumeLateral(radius, height, length);
    std::cout << "The cylinder is oriented sideways." << std::endl
              << "The volume of the cylinder is: " << volume << std::endl;
  }

  return 0;
}
