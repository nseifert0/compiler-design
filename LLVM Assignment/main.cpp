#include <iostream>

extern "C" int string_len(int x);
//extern "C" int string_cmp(const char* str1, const char* str2);
//extern "C" const char* string_chr(const char* str, char c);
//extern "C" char* string_cpy(char* dest, const char* src);

int main() {
  int bunga = string_len(10);
  std::cout << bunga << "\n";
}