#include <cstddef>

static size_t
strlen(const char* str)
{
  auto ptr = str;
  size_t count = 0;
  while (*ptr) {
    ++count;
    ++ptr;
  }
  return count;
}

bool
areAnagrams(const char* str1, const char* str2)
{
  static const unsigned int CHARSIZE = 256;
  if (strlen(str1) != strlen(str2)) {
    return false;
  }

  int freq1[CHARSIZE] = { 0 };
  int freq2[CHARSIZE] = { 0 };

  for (size_t i = 0; i < strlen(str1); ++i) {
    freq1[static_cast<unsigned char>(str1[i])]++;
    freq2[static_cast<unsigned char>(str2[i])]++;
  }

  for (int i = 0; i < CHARSIZE; ++i) {
    if (freq1[i] != freq2[i]) {
      return false;
    }
  }

  return true;
}
