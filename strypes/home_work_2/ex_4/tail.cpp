#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void handle_n_flag_no_file(int numLines) {
  std::vector<std::string> lines;
  std::string line;

  // Read lines into vector from stdin
  while (std::getline(std::cin, line)) {
    lines.push_back(line);
  }

  int totalLines = lines.size();
  int startLine = std::max(0, totalLines - numLines);

  // Print lines from startLine to the end
  for (int i = startLine; i < totalLines; ++i) {
    std::cout << lines[i] << std::endl;
  }
}

bool handle_n_flag_with_file(const std::string &filename, int numLines) {
  std::ifstream file(filename);
  std::vector<std::string> lastLines(numLines);
  int index = 0;
  numLines = std::abs(numLines); // Ensure numLines is positive

  if (!file.is_open()) {
    return false; // Return false if file couldn't be opened
  }

  // Read lines into circular buffer
  std::string line;
  while (std::getline(file, line)) {
    lastLines[index % numLines] = line;
    index++;
  }

  // Print the last few lines
  for (int i = 0; i < numLines; ++i) {
    line = lastLines[(index + i) % numLines];
    if (line == "") {
      continue;
    }
    std::cout << lastLines[(index + i) % numLines] << std::endl;
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
