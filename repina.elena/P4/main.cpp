#include <iostream>
#include <cstring>
#include <cstdlib>

namespace repina {
  constexpr std::size_t inputerror = 1;

  void getUncommonSymbols(const char* str1, const char* str2, char* dest)
  {
    const char* p = str1;
    const char* p2 = str2;
    std::size_t len_dest = 0;

    while (*p != '\0') {
      int found = 0;
      for (std::size_t i = 0; i < strlen(str2); ++i) {
        if (*p == str2[i]) {
          found = 1;
          break;
        }
      }
      if (!found) {
        dest[len_dest] = *p;
        len_dest++;
      }
      p++;
    }
    while (*p2 != '\0') {
      int found1 = 0;
      for (std::size_t i = 0; i < strlen(str1); ++i) {
        if (*p2 == str1[i]) {
          found1 = 1;
          break;
        }
      }
      if (!found1) {
        dest[len_dest] = *p2;
        len_dest++;
      }
      p2++;
    }
    dest[len_dest] = '\0';
  }

  void letterSymbols(const char* str1, char num, char repl, char* res)
  {
    std::size_t len_res = 0;
    const std::size_t len = strlen(str1);
    for (std::size_t i = 0; i < len; ++i) {
      if (str1[i] == num) {
        res[i] = repl;
        len_res++;
      } else {
        res[i] = str1[i];
        len_res++;
      }
    }
    res[len_res] = '\0';
  }
}

int main()
{
  const char* const str1 = "abc_ef";
  const std::size_t size_1 = std::strlen(str1) + 1;

  std::size_t size = 10;
  char* str2 = static_cast< char* >(malloc(size * sizeof(char)));
  if (str2 == nullptr) {
    std::cerr << "Memory allocation error\n";
    return repina::inputerror;
  }

  char c = 0;
  std::size_t str2_len = 0;
  while (std::cin.get(c) && c != '\n') {
    if (str2_len >= size - 1) {
      size += 10;
      char* const new_str = static_cast< char* >(malloc(size * sizeof(char)));

      if (new_str == nullptr) {
        std::cerr << "Memory allocation error\n";
        free(str2);
        return repina::inputerror;
      }
      for (std::size_t i = 0; i < str2_len; ++i) {
        new_str[i] = str2[i];
      }
      std::free(str2);
      str2 = new_str;
    }
    str2[str2_len++] = c;
  }
  str2[str2_len] = '\0';
  if (str2_len == 0) {
    std::cerr << "Input error\n";
    std::free(str2);
    return repina::inputerror;
  }
  char* const dest = static_cast< char* >(malloc((size + size_1) * sizeof(char)));
  if (dest == nullptr) {
    std::cerr << "Memory allocation error\n";
    std::free(str2);
    return repina::inputerror;
  }

  repina::getUncommonSymbols(str1, str2, dest);
  std::cout << dest << "\n";
  std::free(dest);

  char* const res = static_cast< char* >(malloc(size * sizeof(char)));
  if (res == nullptr) {
    std::cerr << "Memory allocation error\n";
    std::free(str2);
    return repina::inputerror;
  }
  const char num = 'a';
  const char repl = 'c';
  repina::letterSymbols(str2, num, repl, res);
  std::cout << res << "\n";

  std::free(str2);
  std::free(res);
  return 0;
}

