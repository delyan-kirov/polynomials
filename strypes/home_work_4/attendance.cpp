#include <bitset>
#include <cstdint>
#include <iostream>
#include <limits>
#include <sys/types.h>
#include <vector>

static uint64_t ATTENDANCE = 0;

void mark_student_as_present(uint student_id) {
  uint64_t mask = 1ULL << student_id;
  ATTENDANCE |= mask;
}

void mark_student_as_absent(uint student_id) {
  uint64_t mask = ~(1ULL << student_id);
  ATTENDANCE &= mask;
}

void toggle_student_presence(uint position) {
  uint64_t mask = 1ULL << position;
  ATTENDANCE ^= mask;
}

std::vector<int> find_present_students() {
  std::vector<int> present;
  for (int i = 0; i < 64; ++i) {
    if ((ATTENDANCE >> i) & 1) {
      present.push_back(i);
    }
  }
  return present;
}

std::vector<int> find_absent_students() {
  std::vector<int> absent;
  for (int i = 0; i < 64; ++i) {
    if (!((ATTENDANCE >> i) & 1)) {
      absent.push_back(i);
    }
  }
  return absent;
}

uint enter_student_id() {
  uint student_id = 0;
  for (;;) {
    std::cout << "Select student id, from 0 to 63" << std::endl;
    if (!(std::cin >> student_id) || student_id > 63) {
      std::cerr << "Invalid input. Please enter a valid student id."
                << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      return student_id;
    }
  }
}

uint enter_option() {
  uint option = 0;
  for (;;) {
    std::cout << "Select option from 1 to 5" << std::endl;
    if (!(std::cin >> option) || option > 5 || option == 0) {
      std::cerr << "Invalid input. Please enter a valid option" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      return option;
    }
  }
}

void print_menu_options() {
  std::cout << "1. Set attendance" << std::endl;
  std::cout << "2. Clear attendance" << std::endl;
  std::cout << "3. Attendance info" << std::endl;
  std::cout << "4. Change attendance" << std::endl;
  std::cout << "5. Exit" << std::endl;
}

int main(void) {
  uint64_t attendance = 0;
  uint option;

  for (;;) {
    print_menu_options();
    option = enter_option();
    uint student_id = 0;

    switch (option) {
    case 1:
      student_id = enter_student_id();
      mark_student_as_present(student_id);
      break;

    case 2:
      student_id = enter_student_id();
      mark_student_as_absent(student_id);
      break;

    case 3:
      std::cout << "PRESENT:\n";
      for (int student : find_present_students()) {
        std::cout << " " << student << "\n";
      }
      std::cout << "ABSENT:\n";
      for (int student : find_absent_students()) {
        std::cout << " " << student << "\n";
      }
      break;

    case 4:
      student_id = enter_student_id();
      toggle_student_presence(student_id);
      break;

    case 5:
      goto EXIT;
      break;

    default:
      std::cerr << "The option: " << option << ", is not recognized"
                << std::endl;
      std::cout << "Please provide a number from 1 to 5" << std::endl;
      break;
    }
  }

EXIT:

  return 0;
}
