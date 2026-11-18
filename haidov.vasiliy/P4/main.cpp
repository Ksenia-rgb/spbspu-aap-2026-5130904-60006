#include <iostream>
#include <cstddef>
#include <limits>

namespace haidov {
  const int correct_result = 0;
  const int memory_error = 1;

  const char* second_string = "abc ef";
  const char to_replace = 'b';
  const char to_replace_with = 'c';

  void cmn_sym(const char* str1, const char* str2, char* result)
  {
    size_t i = 0;
    size_t r = 0;
    while (str1[i] != '\0') {
      size_t j = 0;
      while (str2[j] != '\0') {
        if (str1[i] == str2[j]) {
          result[r] = str1[i];
          r++;
        }
        j++;
      }
      i++;
    }
  }

  void rpl_sym(const char* str, char to_replace, char to_replace_with, char* result)
  {
    size_t i = 0;
    while (str[i] != '\0') {
      if (str[i] == to_replace) {
        result[i] = to_replace_with;
      } else {
        result[i] = str[i];
      }
      i++;
    }
  }

  int lab()
  {
    char* str = nullptr;
    char c = 0;
    size_t str_len = 0;
    while (std::cin.get(c) && c != '\n') {
      str_len++;
      char* new_str = nullptr;
      try {
        new_str = new char[str_len];
      } catch (...) {
        std::cerr << "Memory allocation error";
        return memory_error;
      }
      for (size_t i = 0; i < str_len - 1; ++i) {
        new_str[i] = str[i];
      }
      new_str[str_len - 1] = c;
      delete[] str;
      str = new_str;
    }
    str[str_len] = '\0';
    char* result = nullptr;
    try {
      result = new char[str_len + 1];
    } catch (...) {
      std::cerr << "Memory allocation error";
      return memory_error;
    }
    rpl_sym(str, to_replace, to_replace_with, result);
    std::cout << result << '\n';
    delete[] result;
    try {
      result = new char[str_len + 1];
    } catch (...) {
      std::cerr << "Memory allocation error";
      return memory_error;
    }
    size_t i = 0;
    while (result[i] != '\0') {
      result[i] = 0;
      i++;
    }
    cmn_sym(str, second_string, result);
    std::cout << result;
    delete[] result;
    delete[] str;
    return correct_result;
  }
}

int main()
{
  return haidov::lab();
}
