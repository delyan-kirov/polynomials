#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct FileStats {
  int bytes;
  int characters;
  int words;
  int lines;
};

FileStats calculateFileStats(const std::string &filename) {
  std::ifstream file(filename);
  FileStats stats = {-1, -1, -1,
                     -1}; // Return -1 for all counts in case of failure

  if (file.is_open()) {
    stats = {0, 0, 0, 0}; // Reset counts to 0 since file is opened successfully
    std::string line;
    while (std::getline(file, line)) {
      stats.bytes += line.size() + 1;  // +1 for newline character
      stats.characters += line.size(); // Count characters excluding newline
      std::istringstream iss(line);
      std::string word;
      while (iss >> word) {
        ++stats.words;
      }
      ++stats.lines;
    }
    file.close();
  }

  return stats;
}

FileStats calculateFileStatsNoFile() {
  FileStats stats = {0, 0, 0, 0}; // Initialize counts to 0
  std::string line;

  while (std::getline(std::cin, line)) {
    stats.bytes += line.size() + 1;  // +1 for newline character
    stats.characters += line.size(); // Count characters excluding newline
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
      ++stats.words;
    }
    ++stats.lines;
  }

  return stats;
}

void printFileStats(const FileStats &stats, bool lflag, bool wflag, bool cflag,
                    bool mflag, const std::string &file = "") {
  if (stats.bytes == -1 || stats.characters == -1 || stats.words == -1 ||
      stats.lines == -1) {
    std::cerr << "ERROR: could not open file" << std::endl;
  } else {
    if (lflag) {
      std::cout << " " << stats.lines;
    }
    if (wflag) {
      std::cout << " " << stats.words;
    }
    if (cflag) {
      std::cout << " " << stats.bytes;
    }
    if (mflag) {
      std::cout << " " << stats.characters;
    }
    if (!lflag && !wflag && !cflag && !mflag) {
      std::cout << " " << stats.lines << " " << stats.words << " "
                << stats.bytes;
    }
    std::cout << " " << file << std::endl;
  }
}

void print_usage(void) {
  std::cerr
      << "Usage: head"
      << " [-n MAX_LINES] [-q] [--help] [-c] [-m] [-w] [-l] [FILE1 FILE2 ...]"
      << std::endl;
  std::cerr << "Options:" << std::endl;
  std::cerr << "  -n MAX_LINES   Output at most MAX_LINES lines per file"
            << std::endl;
  std::cerr << "  -q             Quiet mode (suppress error messages)"
            << std::endl;
  std::cerr << "  --help         Display this usage message" << std::endl;
  std::cerr << "  -c             Display byte counts" << std::endl;
  std::cerr << "  -m             Display character counts" << std::endl;
  std::cerr << "  -w             Display word counts" << std::endl;
  std::cerr << "  -l             Display line counts" << std::endl;
  std::cerr << "Arguments:" << std::endl;
  std::cerr << "  FILE1 FILE2 ...   Input files to process" << std::endl;
}

int main(int argc, char *argv[]) {
  bool cflag = false;
  bool mflag = false;
  bool wflag = false;
  bool lflag = false;
  bool helpflag = false;
  std::vector<std::string> files;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--help") {
      helpflag = true;
    } else if (arg == "-c") {
      cflag = true;
    } else if (arg == "-m") {
      mflag = true;
    } else if (arg == "-w") {
      wflag = true;
    } else if (arg == "-l") {
      lflag = true;
    } else {
      files.push_back(arg);
    }
  }

  if (helpflag) {
    print_usage();
    return 0;
  }

  if (files.empty()) {
    FileStats stats = calculateFileStatsNoFile();
    printFileStats(stats, lflag, wflag, cflag, mflag);

  } else if (files.size() >= 1) {
    for (const auto &file : files) {
      FileStats stats = calculateFileStats(file);
      printFileStats(stats, lflag, wflag, cflag, mflag, file);
    }
  }

  return 0;
}
