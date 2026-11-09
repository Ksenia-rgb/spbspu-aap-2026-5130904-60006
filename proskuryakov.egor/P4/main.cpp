#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace proskuryakov {
  const int errorReturnCode = 1;
  const std::size_t tableSize = std::numeric_limits< unsigned char >::max() + 1;

  char * readLine(std::istream & in, std::size_t & out_length);
  char * commonSymbols(char * dest, const char * src1, const char * src2) noexcept;
  int hasRepeats(const char * src) noexcept;
}

char * proskuryakov::readLine(std::istream & in, std::size_t & out_length)
{
  const std::size_t initialCapacity = 32;
  const std::size_t growthFactor = 2;
  const std::size_t maxCapacity = std::numeric_limits< std::size_t >::max();

  std::size_t capacity = initialCapacity;
  char * buffer = new char[capacity];
  std::size_t length = 0;

  char current = '\0';
  while (in.get(current) && (current != '\n')) {
    if (length + 1 >= capacity) {
      if (capacity == maxCapacity) {
        delete[] buffer;
        throw std::length_error("Превышен максимальный размер строки");
      }

      std::size_t newCapacity = maxCapacity;
      if (capacity <= (maxCapacity / growthFactor)) {
        newCapacity = capacity * growthFactor;
      }

      char * newBuffer = nullptr;
      try {
        newBuffer = new char[newCapacity];
      } catch (...) {
        delete[] buffer;
        throw;
      }

      for (std::size_t i = 0; i < length; ++i) {
        newBuffer[i] = buffer[i];
      }
      delete[] buffer;
      buffer = newBuffer;
      capacity = newCapacity;
    }
    buffer[length] = current;
    ++length;
  }

  if ((length == 0) && (!in)) {
    delete[] buffer;
    return nullptr;
  }

  buffer[length] = '\0';
  out_length = length;
  return buffer;
}

char * proskuryakov::commonSymbols(char * dest, const char * src1, const char * src2) noexcept
{
  if ((dest == nullptr) || (src1 == nullptr) || (src2 == nullptr)) {
    return dest;
  }

  int inSecond[tableSize] = {};
  int alreadyAdded[tableSize] = {};

  for (std::size_t i = 0; src2[i] != '\0'; ++i) {
    inSecond[static_cast< unsigned char >(src2[i])] = 1;
  }

  std::size_t destIndex = 0;
  for (std::size_t i = 0; src1[i] != '\0'; ++i) {
    const unsigned char ch = static_cast< unsigned char >(src1[i]);
    if ((inSecond[ch] == 1) && (alreadyAdded[ch] == 0)) {
      alreadyAdded[ch] = 1;
      dest[destIndex] = src1[i];
      ++destIndex;
    }
  }
  dest[destIndex] = '\0';
  return dest;
}

int proskuryakov::hasRepeats(const char * src) noexcept
{
  if (src == nullptr) {
    return 0;
  }

  int seen[tableSize] = {};

  for (std::size_t i = 0; src[i] != '\0'; ++i) {
    const unsigned char ch = static_cast< unsigned char >(src[i]);
    if (seen[ch] == 1) {
      return 1;
    }
    seen[ch] = 1;
  }
  return 0;
}

int main()
{
  const char * const secondLiteral = "abc_ef";

  std::size_t length = 0;
  char * inputStr = nullptr;

  try {
    inputStr = proskuryakov::readLine(std::cin, length);
  } catch (const std::exception & e) {
    std::cerr << "Ошибка выделения памяти при чтении строки: " << e.what() << "\n";
    return proskuryakov::errorReturnCode;
  }

  if (inputStr == nullptr) {
    std::cerr << "Ошибка чтения потока или конец файла\n";
    return proskuryakov::errorReturnCode;
  }

  if (length == 0) {
    delete[] inputStr;
    std::cerr << "Ошибка: введена пустая строка\n";
    return proskuryakov::errorReturnCode;
  }

  char * commonResult = nullptr;
  try {
    commonResult = new char[length + 1];
  } catch (const std::exception & e) {
    delete[] inputStr;
    std::cerr << "Ошибка выделения памяти под результат: " << e.what() << "\n";
    return proskuryakov::errorReturnCode;
  }

  proskuryakov::commonSymbols(commonResult, inputStr, secondLiteral);
  const int repeatsResult = proskuryakov::hasRepeats(inputStr);

  std::cout << commonResult << "\n";
  std::cout << repeatsResult << "\n";

  delete[] commonResult;
  delete[] inputStr;

  return 0;
}
