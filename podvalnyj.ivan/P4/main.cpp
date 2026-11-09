#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace podvalnyj {
  const int ERROR_MEMORY = 1;
  const int ERROR_EMPTY = 1;
  const std::size_t START_SIZE = 16;
  const char * const SECOND_UNI_TWO = "def ";
  const char * const SECOND_UNC_SYM = "abc ef";

  std::size_t length(const char * str)
  {
    std::size_t len = 0;
    while (str[len] != '\0') {
      ++len;
    }
    return len;
  }

  int hasChar(const char * str, char symbol)
  {
    for (std::size_t i = 0; str[i] != '\0'; ++i) {
      if (str[i] == symbol) {
        return 1;
      }
    }
    return 0;
  }

  char * readLine(std::istream & input)
  {
    std::size_t capacity = START_SIZE;
    std::size_t size = 0;
    char * str = static_cast< char * >(std::malloc(capacity));
    if (str == nullptr) {
      return nullptr;
    }
    char symbol = 0;
    while (input.get(symbol) && symbol != '\n') {
      if (size + 1 == capacity) {
        if (capacity > std::numeric_limits< std::size_t >::max() / 2) {
          std::free(str);
          return nullptr;
        }
        char * const bigger = static_cast< char * >(std::malloc(capacity * 2));
        if (bigger == nullptr) {
          std::free(str);
          return nullptr;
        }
        for (std::size_t i = 0; i < size; ++i) {
          bigger[i] = str[i];
        }
        std::free(str);
        str = bigger;
        capacity = capacity * 2;
      }
      str[size] = symbol;
      ++size;
    }
    if (size == 0 && input.eof()) {
      std::free(str);
      return nullptr;
    }
    str[size] = '\0';
    return str;
  }

  char * uniTwo(char * result, const char * first, const char * second)
  {
    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t k = 0;
    while (first[i] != '\0' || second[j] != '\0') {
      if (first[i] != '\0') {
        result[k] = first[i];
        ++i;
        ++k;
      }
      if (second[j] != '\0') {
        result[k] = second[j];
        ++j;
        ++k;
      }
    }
    result[k] = '\0';
    return result;
  }

  char * uncSym(char * result, const char * first, const char * second)
  {
    std::size_t k = 0;
    for (int code = 1; code <= std::numeric_limits< unsigned char >::max(); ++code) {
      const char symbol = static_cast< char >(code);
      if (hasChar(first, symbol) != hasChar(second, symbol)) {
        result[k] = symbol;
        ++k;
      }
    }
    result[k] = '\0';
    return result;
  }

  int printResults(const char * str)
  {
    const std::size_t len = length(str);
    char * const uni = static_cast< char * >(std::malloc(len + length(SECOND_UNI_TWO) + 1));
    if (uni == nullptr) {
      return ERROR_MEMORY;
    }
    std::cout << uniTwo(uni, str, SECOND_UNI_TWO) << "\n";
    std::free(uni);

    char * const unc = static_cast< char * >(std::malloc(len + length(SECOND_UNC_SYM) + 1));
    if (unc == nullptr) {
      return ERROR_MEMORY;
    }
    std::cout << uncSym(unc, str, SECOND_UNC_SYM) << "\n";
    std::free(unc);
    return 0;
  }
}

int main()
{
  char * const str = podvalnyj::readLine(std::cin);
  if (str == nullptr) {
    if (std::cin.eof()) {
      std::cerr << "Error: empty input\n";
      return podvalnyj::ERROR_EMPTY;
    }
    std::cerr << "Error: not enough memory\n";
    return podvalnyj::ERROR_MEMORY;
  }
  const int result = podvalnyj::printResults(str);
  std::free(str);
  if (result != 0) {
    std::cerr << "Error: not enough memory\n";
  }
  return result;
}
