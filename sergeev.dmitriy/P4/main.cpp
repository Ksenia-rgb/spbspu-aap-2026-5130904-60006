
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace sergeev{
  const char lineTerminator = '\n';
  const char oldSymbol = 'c';
  const char newSymbol = 'b';

  int readLine(char*& line);
  int interleave(const char* first, const char* second, char* result, size_t resultCapacity);
  int replaceSymbol(const char* source, char* result, size_t resultCapacity);
  int process();
}

int sergeev::readLine(char*& line)
{
  size_t capacity = 16;
  size_t length = 0;

  line = static_cast<char*>(std::malloc(capacity));

  if (line == nullptr) {
    return 1;
  }

  char symbol = '\0';

  while (std::cin.get(symbol)) {
    if (symbol == lineTerminator) {
      line[length] = '\0';
      return 0;
    }

    if (length + 1 >= capacity) {
      if (capacity > std::numeric_limits<size_t>::max() / 2) {
        std::free(line);
        return 1;
      }

      const size_t newCapacity = capacity * 2;
      char* newLine = static_cast<char*>(std::malloc(newCapacity));

      if (newLine == nullptr) {
        std::free(line);
        return 1;
      }

      for (size_t index = 0; index < length; ++index) {
        newLine[index] = line[index];
      }

      std::free(line);
      line = newLine;
      capacity = newCapacity;
    }

    line[length] = symbol;
    ++length;
  }

  if (std::cin.bad() || std::cin.eof()) {
    std::free(line);
    return 1;
  }
  std::free(line);
  line = nullptr;
  return 1;
}



int main()
{

}
