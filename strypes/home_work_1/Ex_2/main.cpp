#include <cmath>
#include <iostream>
#include <ostream>
#include <string>

double calc_BMI(double mass, double height) {
  return mass / std::pow(height, 2);
}

double calc_BMI_Treften(double mass, double height) {
  return 1.3 * mass / std::pow(height, 2.5);
}

int main(int argc, char *argv[]) {
  double mass = 0.0;
  double height = 0.0;
  bool treften = false;

  // Parse command-line arguments
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.substr(0, 7) == "--mass=") {
      mass = std::stod(arg.substr(7));
    } else if (arg.substr(0, 9) == "--height=") {
      height = std::stod(arg.substr(9));
    } else if (arg == "--treften") {
      treften = true;
    } else if (arg == "--help") {
      std::cout << "Usage: " << argv[0]
                << " --mass=value --height=value [--treften] [--help]\n";
      return 0;
    }
  }

  // Sanity check
  if (mass <= 0.0 || height <= 0.0) {
    std::cerr << "USAGE: " << argv[0]
              << " --mass=value --height=value [--treften]" << std::endl
              << "Please provide valid mass and height values" << std::endl
              << "INFO: Current mass is: " << mass << std::endl
              << "INFO: Current height is: " << height << std::endl
              << "Values must be greater than zero to pass sanity check"
              << std::endl;

    return 1;
  }

  double bmi = 0.0;

  if (treften) {
    bmi = calc_BMI_Treften(mass, height);
  } else {
    bmi = calc_BMI(mass, height);
  }

  std::cout << "INFO: Current mass is: " << mass << std::endl
            << "INFO: Current height is: " << height << std::endl
            << "INFO: Using Treften: " << std::boolalpha << treften << std::endl
            << "RESULT: BMI is: " << bmi << std::endl;

  return 0;
}
