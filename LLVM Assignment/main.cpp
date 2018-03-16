#include <iostream>
#include <cstring>

extern "C" int string_len(const char* str);
extern "C" int string_cmp(const char* str1, const char* str2);
extern "C" const char* string_chr(const char* str, char c);
extern "C" char* string_cpy(char* dest, const char* src);

int main() {
  const char s1[] = "Chunga";
  const char s2[] = "Chunga";
  std::cout << std::strcmp(s1, s2) << "\n";
  std::cout << string_cmp(s1, s2) << "\n";
  std::cout << std::strchr(s1, 'g') << "\n";
  std::cout << string_chr(s1, 'g') << "\n";
}