
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace sergeev{
  const char lineTerminator = '\n';
  const char oldSymbol = 'c';
  const char newSymbol = 'b';

  const int successCode = 0;
  const int errorCode = 1;

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
    return errorCode;
  }

  char symbol = '\0';

  while (std::cin.get(symbol)) {
    if (symbol == lineTerminator) {
      line[length] = '\0';
      return successCode;
    }

    if (length + 1 >= capacity) {
      if (capacity > std::numeric_limits<size_t>::max() / 2) {
        std::free(line);
        return errorCode;
      }

      const size_t newCapacity = capacity * 2;
      char* newLine = static_cast<char*>(std::malloc(newCapacity));

      if (newLine == nullptr) {
        std::free(line);
        return errorCode;
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
  return errorCode;
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
    return errorCode;
  }

  const size_t requiredCapacity = firstLength + secondLength + 1;

  if (requiredCapacity > resultCapacity) {
    return errorCode;
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
  return successCode;
}

int sergeev::replaceSymbol(const char* source, char* result, size_t resultCapacity)
{
  size_t length = 0;

  while (source[length] != '\0') {
    ++length;
  }

  if (length == std::numeric_limits<size_t>::max() || length + 1 > resultCapacity) {
    return errorCode;
  }

  for (size_t index = 0; index < length; ++index) {
    if (source[index] == oldSymbol) {
      result[index] = newSymbol;
    } else {
      result[index] = source[index];
    }
  }

  result[length] = '\0';
  return successCode;
}

int sergeev::process()
{
  char* first = nullptr;
  char* second = nullptr;
  char* interleaved = nullptr;
  char* replaced = nullptr;

  if (sergeev::readLine(first) == errorCode) {
    std::cerr << "cannot read the first line\n";
    return errorCode;
  }

  const int secondReadStatus = sergeev::readLine(second);

  int interleaveStatus = errorCode;
  int replaceStatus = errorCode;

  size_t firstLength = 0;

  while (first[firstLength] != '\0') {
    ++firstLength;
  }

  if (secondReadStatus == successCode) {
    size_t secondLength = 0;

    while (second[secondLength] != '\0') {
      ++secondLength;
    }

    const size_t maximumSize = std::numeric_limits<size_t>::max();

    if (secondLength != maximumSize && firstLength <= maximumSize - secondLength - 1) {
      const size_t interleavedCapacity = firstLength + secondLength + 1;

      interleaved = static_cast<char*>(std::malloc(interleavedCapacity));

      if (interleaved != nullptr) {
        interleaveStatus = sergeev::interleave(first, second, interleaved, interleavedCapacity);
      }
    }
  }

  if (firstLength != std::numeric_limits<size_t>::max()) {
    const size_t replacedCapacity = firstLength + 1;

    replaced = static_cast<char*>(std::malloc(replacedCapacity));

    if (replaced != nullptr) {
      replaceStatus = sergeev::replaceSymbol(first, replaced, replacedCapacity);
    }
  }

  if (interleaveStatus == successCode) {
    std::cout << interleaved << '\n';
  } else {
    std::cerr << "variant 12: calculation failed\n";
  }

  if (replaceStatus == successCode) {
    std::cout << replaced << '\n';
  } else {
    std::cerr << "variant 10: calculation failed\n";
  }

  int outputStatus = successCode;

  if (!std::cout) {
    outputStatus = errorCode;
  }

  std::free(first);
  std::free(second);
  std::free(interleaved);
  std::free(replaced);

  if (outputStatus == errorCode || interleaveStatus == errorCode || replaceStatus == errorCode) {
    return errorCode;
  }

  return successCode;
}

int main()
{
  sergeev::process();
}
