#include <cctype>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace dortman {
  char * readLine(std::istream & in, std::size_t & outLength);
  char * excludeSecond(char * dest, const char * src1, const char * src2);
  char * convertUpperToLower(char * dest, const char * src);
}

char * dortman::readLine(std::istream & in, std::size_t & outLength)
{
  const std::size_t initialCapacity = 32;
  const std::size_t growthFactor = 2;
  const std::size_t maxCapacity = std::numeric_limits< std::size_t >::max();

  std::size_t capacity = initialCapacity;
  char * buffer = new char[capacity];
  std::size_t length = 0;

  const std::ios_base::fmtflags origFlags = in.flags();
  in >> std::noskipws;

  char currentChar = '\0';
  while ((in >> currentChar) && (currentChar != '\n')) {
    if (length + 1 >= capacity) {
      if (capacity == maxCapacity) {
        in.flags(origFlags);
        delete[] buffer;
        throw std::length_error("Превышен максимальный размер строки");
      }
      std::size_t newCapacity = 0;
      if (capacity > (maxCapacity / growthFactor)) {
        newCapacity = maxCapacity;
      } else {
        newCapacity = capacity * growthFactor;
      }

      char * newBuffer = nullptr;
      try {
        newBuffer = new char[newCapacity];
      } catch (...) {
        in.flags(origFlags);
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
    buffer[length] = currentChar;
    ++length;
  }

  in.flags(origFlags);

  if ((length == 0) && (!in)) {
    delete[] buffer;
    return nullptr;
  }

  buffer[length] = '\0';
  outLength = length;
  return buffer;
}

char * dortman::excludeSecond(char * dest, const char * src1, const char * src2)
{
  if ((dest == nullptr) || (src1 == nullptr) || (src2 == nullptr)) {
    return dest;
  }

  std::size_t destIndex = 0;
  for (std::size_t i = 0; src1[i] != '\0'; ++i) {
    int isFound = 0;
    for (std::size_t j = 0; src2[j] != '\0'; ++j) {
      if (src1[i] == src2[j]) {
        isFound = 1;
        break;
      }
    }
    if (isFound == 0) {
      dest[destIndex] = src1[i];
      ++destIndex;
    }
  }
  dest[destIndex] = '\0';
  return dest;
}

char * dortman::convertUpperToLower(char * dest, const char * src)
{
  if ((dest == nullptr) || (src == nullptr)) {
    return dest;
  }

  std::size_t i = 0;
  while (src[i] != '\0') {
    const unsigned char ch = static_cast< unsigned char >(src[i]);
    if (std::isupper(ch) != 0) {
      dest[i] = static_cast< char >(std::tolower(ch));
    } else {
      dest[i] = src[i];
    }
    ++i;
  }
  dest[i] = '\0';
  return dest;
}

int main()
{
  const int errorReturnCode = 1;
  const char * const secondLiteral = "abc";

  std::size_t length = 0;
  char * inputStr = nullptr;

  try {
    inputStr = dortman::readLine(std::cin, length);
  } catch (const std::exception & e) {
    std::cerr << "Ошибка выделения памяти при чтении строки: " << e.what() << "\n";
    return errorReturnCode;
  }

  if (inputStr == nullptr) {
    std::cerr << "Ошибка чтения потока или конец файла\n";
    return errorReturnCode;
  }

  if (length == 0) {
    delete[] inputStr;
    std::cerr << "Ошибка: введена пустая строка\n";
    return errorReturnCode;
  }

  char * resExcSnd = nullptr;
  char * resUppLow = nullptr;

  try {
    resExcSnd = new char[length + 1];
    resUppLow = new char[length + 1];
  } catch (const std::exception & e) {
    delete[] resExcSnd;
    delete[] inputStr;
    std::cerr << "Ошибка выделения памяти под результат: " << e.what() << "\n";
    return errorReturnCode;
  }

  dortman::excludeSecond(resExcSnd, inputStr, secondLiteral);
  dortman::convertUpperToLower(resUppLow, inputStr);

  std::cout << resExcSnd << "\n";
  std::cout << resUppLow << "\n";

  delete[] resUppLow;
  delete[] resExcSnd;
  delete[] inputStr;

  return 0;
}
