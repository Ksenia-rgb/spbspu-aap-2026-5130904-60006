#include <cctype>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace dortman {
  char * readLine(std::istream & in, std::size_t & out_length);
  char * excludeSecond(char * dest, const char * src1, const char * src2);
  char * convertUpperToLower(char * dest, const char * src);
}

char * dortman::readLine(std::istream & in, std::size_t & out_length)
{
  const std::size_t initialCapacity = 32;
  const std::size_t growthFactor = 2;
  const std::size_t maxCapacity = std::numeric_limits< std::size_t >::max();

  std::size_t capacity = initialCapacity;
  char * buffer = new char[capacity];
  std::size_t length = 0;

  const std::ios_base::fmtflags origFlags = in.flags();
  in >> std::noskipws;

  char current_char = '\0';
  while ((in >> current_char) && (current_char != '\n')) {
    if (length + 1 >= capacity) {
      if (capacity == maxCapacity) {
        in.flags(origFlags);
        delete[] buffer;
        throw std::length_error("Превышен максимальный размер строки");
      }
      std::size_t new_capacity = 0;
      if (capacity > (maxCapacity / growthFactor)) {
        new_capacity = maxCapacity;
      } else {
        new_capacity = capacity * growthFactor;
      }

      char * new_buffer = nullptr;
      try {
        new_buffer = new char[new_capacity];
      } catch (...) {
        in.flags(origFlags);
        delete[] buffer;
        throw;
      }

      for (std::size_t i = 0; i < length; ++i) {
        new_buffer[i] = buffer[i];
      }
      delete[] buffer;
      buffer = new_buffer;
      capacity = new_capacity;
    }
    buffer[length] = current_char;
    ++length;
  }

  in.flags(origFlags);

  if ((length == 0) && (!in)) {
    delete[] buffer;
    return nullptr;
  }

  buffer[length] = '\0';
  out_length = length;
  return buffer;
}

char * dortman::excludeSecond(char * dest, const char * src1, const char * src2)
{
  if ((dest == nullptr) || (src1 == nullptr) || (src2 == nullptr)) {
    return dest;
  }

  std::size_t dest_index = 0;
  for (std::size_t i = 0; src1[i] != '\0'; ++i) {
    int is_found = 0;
    for (std::size_t j = 0; src2[j] != '\0'; ++j) {
      if (src1[i] == src2[j]) {
        is_found = 1;
        break;
      }
    }
    if (is_found == 0) {
      dest[dest_index] = src1[i];
      ++dest_index;
    }
  }
  dest[dest_index] = '\0';
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
  char * input_str = nullptr;

  try {
    input_str = dortman::readLine(std::cin, length);
  } catch (const std::exception & e) {
    std::cerr << "Ошибка выделения памяти при чтении строки: " << e.what() << "\n";
    return errorReturnCode;
  }

  if (input_str == nullptr) {
    std::cerr << "Ошибка чтения потока или конец файла\n";
    return errorReturnCode;
  }

  if (length == 0) {
    delete[] input_str;
    std::cerr << "Ошибка: введена пустая строка\n";
    return errorReturnCode;
  }

  char * res_exc_snd = nullptr;
  char * res_upp_low = nullptr;

  try {
    res_exc_snd = new char[length + 1];
    res_upp_low = new char[length + 1];
  } catch (const std::exception & e) {
    delete[] res_exc_snd;
    delete[] input_str;
    std::cerr << "Ошибка выделения памяти под результат: " << e.what() << "\n";
    return errorReturnCode;
  }

  dortman::excludeSecond(res_exc_snd, input_str, secondLiteral);
  dortman::convertUpperToLower(res_upp_low, input_str);

  std::cout << res_exc_snd << "\n";
  std::cout << res_upp_low << "\n";

  delete[] res_upp_low;
  delete[] res_exc_snd;
  delete[] input_str;

  return 0;
}
