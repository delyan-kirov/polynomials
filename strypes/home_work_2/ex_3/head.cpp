#include <fstream>
#include <iostream>
#include <vector>

void handle_n_flag_no_file(int max_lines) {
  using std::cin;
  using std::cout;
  using std::endl;
  using std::string;

  int line_count = 0;

  // nothing to do
  if (max_lines == 0) {
    std::cout << "HERE!";
    return;

    // read first max_lines lines
  } else if (max_lines > 0) {
    while (!cin.eof()) {
      string line;
      std::getline(cin, line); // Read a line from stdin

      line_count++; // count lines

      // Process the input line
      cout << line << endl;

      if (line_count >= max_lines) {
        return;
      }
    }
  }

  // read until new line
  if (max_lines < 0) {
    while (!cin.eof()) {
      string line;
      std::getline(cin, line); // Read a line from stdin

      line_count++; // count lines

      // Process the input line
      cout << "Read: " << line << "Line: " << max_lines << endl;

      if (max_lines >= line_count) {
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

void print_usage(void) {
  std::cerr << "Usage: head"
            << " [-n MAX_LINES] [-q] [--help] [FILE1 FILE2 ...]" << std::endl;
  std::cerr << "Options:" << std::endl;
  std::cerr << "  -n MAX_LINES   Output at most MAX_LINES lines per file"
            << std::endl;
  std::cerr << "  -q             Quiet mode (suppress error messages)"
            << std::endl;
  std::cerr << "  --help         Display this usage message" << std::endl;
  std::cerr << "Arguments:" << std::endl;
  std::cerr << "  FILE1 FILE2 ...   Input files to process" << std::endl;
}

int main(int argc, char *argv[]) {
  bool qflag = false;
  bool helpflag = false;
  int max_lines = 20;
  std::vector<std::string> files;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-n") {
      if (i + 1 < argc && std::isdigit(argv[i + 1][0])) {
        max_lines = std::atoi(argv[i + 1]);
        ++i; // skip the next argument since it's the value for -n
      } else {
        std::cerr << "bad usage: -n flag must be followed by an integer.\n";
        return 1;
      }
    } else if (arg == "-q") {
      qflag = true;
    } else if (arg == "--help") {
      helpflag = true;
    } else {
      files.push_back(arg);
    }
  }

  if (files.empty()) {
    handle_n_flag_no_file(max_lines);
  } else if (files.size() == 1) {
    bool could_open_file = handle_n_flag_with_file(files[0], max_lines);
    if (!could_open_file) {
      std::cout << "error: could not open file: " << files[0] << std::endl;
    }
  } else if (!qflag && files.size() > 1) {
    for (const auto &file : files) {
      std::cout << "==> " << file << " <==" << std::endl;
      bool could_open_file = handle_n_flag_with_file(files[0], max_lines);
      if (!could_open_file) {
        std::cout << "error: could not open file: " << files[0] << std::endl;
      } else {
        std::cout << "\n";
      }
      std::cout << "\n";
    }
  } else if (files.size() > 1) {
    for (const auto &_ : files) {
      bool could_open_file = handle_n_flag_with_file(files[0], max_lines);
      if (!could_open_file) {
        std::cout << "error: could not open file: " << files[0] << std::endl;
      } else {
        std::cout << "\n";
      }
    }
  }
  if (helpflag) {
    print_usage();
  }

  return 0;
}
