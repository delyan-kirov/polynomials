#include <cstddef>

static inline size_t
strlen(const char* str)
{
  size_t count = 0;
  for (const char* ptr = str; *ptr != '\0'; ++ptr) {
    if (*ptr != ' ') {
      ++count;
    }
  }
  return count;
}

bool
areAnagrams(const char* str1, const char* str2)
{
  static const unsigned int CHARSIZE = 256;

  size_t len1 = strlen(str1);
  size_t len2 = strlen(str2);

  if (len1 != len2) {
    return false;
  }

  int freq[CHARSIZE] = { 0 };

  // Count frequencies of characters ignoring spaces
  for (const char* ptr = str1; *ptr != '\0'; ++ptr) {
    if (*ptr != ' ') {
      freq[static_cast<unsigned char>(*ptr)]++;
    }
  }
  for (const char* ptr = str2; *ptr != '\0'; ++ptr) {
    if (*ptr != ' ') {
      freq[static_cast<unsigned char>(*ptr)]--;
    }
  }

  for (int i = 0; i < CHARSIZE; ++i) {
    if (freq[i] != 0) {
      return false;
    }
  }

  return true;
}
