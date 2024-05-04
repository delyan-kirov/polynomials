#include <fstream>
#include <iostream>

void handle_n_flag_no_file(int max_lines) {
  using std::cout, std::endl, std::cin, std::string;

  int line_count = 0;

  // nothing to do
  if (line_count == 0) {
    return;

    // read first line_count lines
  } else if (line_count > 0) {
    while (!cin.eof()) {
      string line;
      std::getline(cin, line); // Read a line from stdin

      line_count++; // count lines

      // Process the input line
      cout << "Read: " << line << "Line: " << line_count << endl;

      if (line_count >= max_lines) {
        return;
      }
    }
  }

  // read until new line
  if (line_count < 0) {
    while (!cin.eof()) {
      string line;
      std::getline(cin, line); // Read a line from stdin

      line_count++; // count lines

      // Process the input line
      cout << "Read: " << line << "Line: " << line_count << endl;

      if (line_count >= max_lines) {
        break;
      }
    }
    return;
  }
  return;
}

bool handle_n_flag_with_file(const std::string &filename, int numLines) {
  // Open the file
  std::ifstream file(filename);

  // Check if the file opened successfully
  if (!file.is_open()) {
    return false;
  }

  // Read and display the first numLines lines of the file
  std::string line;
  int lineCount = 0;
  while (lineCount < numLines && std::getline(file, line)) {
    std::cout << line << std::endl;
    lineCount++;
  }

  // Close the file
  file.close();
  return true;
}

int main(int argc, char *argv[]) {
  // Define variables to hold flag values and defaults
  bool nFlag = false;
  bool cFlag = false;
  bool qFlag = false;
  bool vFlag = false;
  bool zFlag = false;
  bool helpFlag = false;
  int lineCount = 10; // Default line count
  bool badUsage = false;

  // Iterate through command-line arguments
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    // Check for flags
    if (arg == "-n") {
      nFlag = true;
      // Ensure there's another argument after the flag
      if (i + 1 < argc) {
        // Parse the integer value
        lineCount = std::atoi(argv[++i]);
        if (lineCount <= 0) {
          std::cerr << "Error: Invalid line count provided.\n";
          return 1;
        }
      } else {
        std::cerr << "Error: Missing argument for -n flag.\n";
        badUsage = true;
      }
    } else if (arg == "-c") {

      cFlag = true;
      // Ensure there's another argument after the flag
      if (i + 1 < argc) {
        // Parse the integer value
        lineCount = std::atoi(argv[++i]);
        if (lineCount <= 0) {
          std::cerr << "Error: Invalid line count provided.\n";
          return 1;
        }
      } else {
        std::cerr << "Error: Missing argument for -n flag.\n";
        badUsage = true;
      }
    } else if (arg == "-c" || arg == "-q" || arg == "-v" || arg == "-z" ||
               arg == "--help") {
      // Other flags
    } else {
      // Unrecognized argument
      std::cerr << "Error: Unrecognized argument: " << arg << "\n";
      badUsage = true;
    }
  }

  if (badUsage) {
    std::cerr << "Bad usage. Usage: ./program [-n <line_count>] [-c] [-q] [-v] "
                 "[-z] [--help]\n";
    return 1;
  }

  // Print parsed values
  std::cout << "Flags:\n";
  std::cout << "-n: " << std::boolalpha << nFlag
            << " (line count: " << lineCount << ")\n";

  return 0;
}
