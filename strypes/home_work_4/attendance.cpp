#include <cstdint>
#include <iostream>

int main(void) {
  uint64_t attendance = 0;
  int option;

  for (;;) {
    std::cout << "1. Set attendance" << std::endl;
    std::cout << "2. Clear attendance\n" << std::endl;
    std::cout << "3. Attendance info\n" << std::endl;
    std::cout << "4. Change attendance\n" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cin >> option;
    if (option == 1) {
      // to do
    } else if (option == 2) {
      // to do
    } else if (option == 3) {
      // to do
    }
    // to do
  }

  return 0;
}
