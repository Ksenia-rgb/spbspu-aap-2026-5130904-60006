#include <cctype>
#include <cstddef>
#include <exception>
#include <iostream>
#include <limits>

namespace zakirov {
  const int ERROR_MEMORY = 1;
  const int ERROR_IO = 2;
  const char OLD_CHAR = 'c';
  const char NEW_CHAR = 'b';

  int countLetters(const char *str);
  char *replaceChars(char *result, const char *str, char oldChar, char newChar);
  char *readLine();
}

int zakirov::countLetters(const char *str)
{
  int used['z' + 1] = {};
  int count = 0;
  for (std::size_t i = 0; str[i] != '\0'; ++i) {
    const unsigned char symbol = static_cast< unsigned char >(str[i]);
    if (std::isalpha(symbol) && (((symbol >= 'a') && (symbol <= 'z')) || ((symbol >= 'A') && (symbol <= 'Z')))) {
      if (used[symbol] == 0) {
        used[symbol] = 1;
        ++count;
      }
    }
  }
  return count;
}

char *zakirov::replaceChars(char *result, const char *str, const char oldChar, const char newChar)
{
  std::size_t i = 0;
  while (str[i] != '\0') {
    result[i] = str[i];
    if (str[i] == oldChar) {
      result[i] = newChar;
    }
    ++i;
  }
  result[i] = '\0';
  return result;
}

char *zakirov::readLine()
{
  std::size_t capacity = 10;
  std::size_t size = 0;
  char *str = nullptr;
  try {
    str = new char[capacity];
    char symbol = 0;
    while (std::cin.get(symbol) && (symbol != '\n')) {
      if (size == capacity - 1) {
        const std::size_t maxSize = std::numeric_limits< std::size_t >::max();
        if (capacity == maxSize) {
          delete[] str;
          return nullptr;
        }
        std::size_t newCapacity = maxSize;
        if (capacity <= maxSize / 2) {
          newCapacity = capacity * 2;
        }
        char * const newStr = new char[newCapacity];
        for (std::size_t i = 0; i < size; ++i) {
          newStr[i] = str[i];
        }
        delete[] str;
        str = newStr;
        capacity = newCapacity;
      }
      str[size] = symbol;
      ++size;
    }
  } catch (const std::exception &) {
    delete[] str;
    return nullptr;
  }
  str[size] = '\0';
  return str;
}

int main()
{
  char * const str = zakirov::readLine();
  if (str == nullptr) {
    std::cerr << "Not enough memory\n";
    return zakirov::ERROR_MEMORY;
  }
  if (std::cin.bad()) {
    delete[] str;
    std::cerr << "Input error\n";
    return zakirov::ERROR_IO;
  }
  std::size_t length = 0;
  while (str[length] != '\0') {
    ++length;
  }
  char *result = nullptr;
  try {
    result = new char[length + 1];
  } catch (const std::exception &) {
    delete[] str;
    std::cerr << "Not enough memory\n";
    return zakirov::ERROR_MEMORY;
  }
  zakirov::replaceChars(result, str, zakirov::OLD_CHAR, zakirov::NEW_CHAR);
  std::cout << zakirov::countLetters(str) << '\n' << result << std::endl;
  delete[] result;
  delete[] str;
  if (!std::cout) {
    std::cerr << "Output error\n";
    return zakirov::ERROR_IO;
  }
  return 0;
}
