
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
  std::free(line);
  line = nullptr;
  return 1;
}

int sergeev::interleave(const char* first, const char* second, char* result, size_t resultCapacity)
{
  size_t firstLength = 0;
  size_t secondLength = 0;

  while (first[firstLength] != '\0') {
    ++firstLength;
  }

  while (second[secondLength] != '\0') {
    ++secondLength;
  }

  const size_t maximumSize = std::numeric_limits<size_t>::max();

  if (secondLength == maximumSize || firstLength > maximumSize - secondLength - 1) {
    return 1;
  }

  const size_t requiredCapacity = firstLength + secondLength + 1;

  if (requiredCapacity > resultCapacity) {
    return 1;
  }

  size_t firstIndex = 0;
  size_t secondIndex = 0;
  size_t resultIndex = 0;

  while (firstIndex < firstLength && secondIndex < secondLength) {
    result[resultIndex] = first[firstIndex];
    ++resultIndex;
    ++firstIndex;

    result[resultIndex] = second[secondIndex];
    ++resultIndex;
    ++secondIndex;
  }

  while (firstIndex < firstLength) {
    result[resultIndex] = first[firstIndex];
    ++resultIndex;
    ++firstIndex;
  }

  while (secondIndex < secondLength) {
    result[resultIndex] = second[secondIndex];
    ++resultIndex;
    ++secondIndex;
  }

  result[resultIndex] = '\0';
  return 0;
}

int sergeev::replaceSymbol(const char* source, char* result, size_t resultCapacity)
{
  size_t length = 0;

  while (source[length] != '\0') {
    ++length;
  }

  if (length == std::numeric_limits<size_t>::max() || length + 1 > resultCapacity) {
    return 1;
  }

  for (size_t index = 0; index < length; ++index) {
    if (source[index] == oldSymbol) {
      result[index] = newSymbol;
    } else {
      result[index] = source[index];
    }
  }

  result[length] = '\0';
  return 0;
}


int main()
{

}
