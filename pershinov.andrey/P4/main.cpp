#include <iostream>
#include <cstddef>
#include <cctype>

namespace pershinov {
  char * readLine()
  {
    size_t capacity = 10;
    size_t size = 0;
    char * buffer = nullptr;
    try {
      buffer = new char[capacity];
    } catch (...) {
      return nullptr;
    }
    char c = 0;
    try {
      while (std::cin.get(c) && c != '\n') {
        if (size + 1 == capacity) {
          const size_t bigger = capacity * 2;
          char * const new_buffer = new char[bigger];
          for (size_t i = 0; i < size; ++i) {
            new_buffer[i] = buffer[i];
          }
          delete[] buffer;
          buffer = new_buffer;
          capacity = bigger;
        }
        buffer[size] = c;
        ++size;
      }
    } catch (...) {
      delete[] buffer;
      return nullptr;
    }
    if (size == 0 && std::cin.eof()) {
      delete[] buffer;
      return nullptr;
    }
    buffer[size] = '\0';
    return buffer;
  }
  char * removeDigits(const char * source, char * result) noexcept
  {
    size_t count = 0;
    for (size_t i = 0; source[i] != '\0'; ++i) {
      if (!std::isdigit(static_cast< unsigned char >(source[i]))) {
        result[count] = source[i];
        ++count;
      }
    }
    result[count] = '\0';
    return result;
  }
  size_t stringLength(const char * string) noexcept
  {
    size_t length = 0;
    for (size_t i = 0; string[i] != '\0'; ++i) {
      ++length;
    }
    return length;
  }
  char * mergeLatin(const char * str1, const char * str2, char * result) noexcept
  {
    const size_t alphabet_size = 26;
    int marks[alphabet_size] = {};
    size_t count = 0;
    for (size_t i = 0; str1[i] != '\0'; ++i) {
      const int low = std::tolower(static_cast< unsigned char >(str1[i]));
      if (low >= 'a' && low <= 'z') {
        marks[low - 'a'] = 1;
      }
    }
    for (size_t i = 0; str2[i] != '\0'; ++i) {
      const int low = std::tolower(static_cast< unsigned char >(str2[i]));
      if (low >= 'a' && low <= 'z') {
        marks[low - 'a'] = 1;
      }
    }
    for (size_t k = 0; k < alphabet_size; ++k) {
      if (marks[k] == 1) {
        result[count] = static_cast< char >('a' + k);
        ++count;
      }
    }
    result[count] = '\0';
    return result;
  }
}

int main()
{
  const int memory_error = 1;
  const int input_error = 2;
  char * const line = pershinov::readLine();
  if (line == nullptr) {
    if (std::cin.eof()) {
      std::cerr << "Error: empty input\n";
      return input_error;
    }
    std::cerr << "Error: not enough memory\n";
    return memory_error;
  }
  const size_t length = pershinov::stringLength(line);
  char * result = nullptr;
  try {
    result = new char[length + 1];
  } catch (...) {
    delete[] line;
    std::cerr << "Error: not enough memory\n";
    return memory_error;
  }
  pershinov::removeDigits(line, result);
  std::cout << result << "\n";
  delete[] result;
  const char * const str2 = "leetCode";
  const size_t letter_size = 27;
  char * letters = nullptr;
  try {
    letters = new char[letter_size];
  } catch (...) {
    delete[] line;
    std::cerr << "Error: not enough memory\n";
    return memory_error;
  }
  pershinov::mergeLatin(line, str2, letters);
  std::cout << letters << "\n";
  delete[] line;
  delete[] letters;
}


