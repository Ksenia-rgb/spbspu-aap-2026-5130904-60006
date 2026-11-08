
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace sergeev {
  const char lineTerminator = '\n';
  const size_t initialCapacity = 16;
  const char oldSymbol = 'c';
  const char newSymbol = 'b';

  const int successCode = 0;
  const int errorCode = 1;

  int readLine(char*& line);
  int interleave(const char* first, const char* second, char* result, size_t result_capacity);
  int replaceSymbol(const char* source, char* result, size_t result_capacity);
  int process();
}

int sergeev::readLine(char*& line)
{
  size_t capacity = initialCapacity;
  size_t length = 0;

  line = static_cast< char* >(std::malloc(capacity));

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
      if (capacity > std::numeric_limits< size_t >::max() / 2) {
        std::free(line);
        line = nullptr;
        return errorCode;
      }

      const size_t new_capacity = capacity * 2;
      char* const new_line = static_cast< char* >(std::malloc(new_capacity));

      if (new_line == nullptr) {
        std::free(line);
        line = nullptr;
        return errorCode;
      }

      for (size_t index = 0; index < length; ++index) {
        new_line[index] = line[index];
      }

      std::free(line);
      line = new_line;
      capacity = new_capacity;
    }

    line[length] = symbol;
    ++length;
  }

  std::free(line);
  line = nullptr;
  return errorCode;
}

int sergeev::interleave(const char* first, const char* second, char* result, size_t result_capacity)
{
  size_t first_length = 0;
  size_t second_length = 0;

  while (first[first_length] != '\0') {
    ++first_length;
  }

  while (second[second_length] != '\0') {
    ++second_length;
  }

  const size_t maximum_size = std::numeric_limits< size_t >::max();

  if (second_length == maximum_size || first_length > maximum_size - second_length - 1) {
    return errorCode;
  }

  const size_t required_capacity = first_length + second_length + 1;

  if (required_capacity > result_capacity) {
    return errorCode;
  }

  size_t first_index = 0;
  size_t second_index = 0;
  size_t result_index = 0;

  while (first_index < first_length && second_index < second_length) {
    result[result_index] = first[first_index];
    ++result_index;
    ++first_index;

    result[result_index] = second[second_index];
    ++result_index;
    ++second_index;
  }

  while (first_index < first_length) {
    result[result_index] = first[first_index];
    ++result_index;
    ++first_index;
  }

  while (second_index < second_length) {
    result[result_index] = second[second_index];
    ++result_index;
    ++second_index;
  }

  result[result_index] = '\0';
  return successCode;
}

int sergeev::replaceSymbol(const char* source, char* result, size_t result_capacity)
{
  size_t length = 0;

  while (source[length] != '\0') {
    ++length;
  }

  if (length == std::numeric_limits< size_t >::max() || length + 1 > result_capacity) {
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
  char* interleaved = nullptr;
  char* replaced = nullptr;

  const char second[] = "def_";

  if (sergeev::readLine(first) == errorCode) {
    std::cerr << "cannot read the first line\n";
    return errorCode;
  }

  size_t first_length = 0;
  size_t second_length = 0;

  while (first[first_length] != '\0') {
    ++first_length;
  }

  while (second[second_length] != '\0') {
    ++second_length;
  }

  int interleave_status = errorCode;
  int replace_status = errorCode;

  const size_t maximum_size = std::numeric_limits< size_t >::max();

  if (second_length != maximum_size && first_length <= maximum_size - second_length - 1) {
    const size_t interleaved_capacity = first_length + second_length + 1;

    interleaved = static_cast< char* >(std::malloc(interleaved_capacity));

    if (interleaved != nullptr) {
      interleave_status = sergeev::interleave(first, second, interleaved, interleaved_capacity);
    }
  }

  if (first_length != maximum_size) {
    const size_t replaced_capacity = first_length + 1;

    replaced = static_cast< char* >(std::malloc(replaced_capacity));

    if (replaced != nullptr) {
      replace_status = sergeev::replaceSymbol(first, replaced, replaced_capacity);
    }
  }

  if (interleave_status == successCode) {
    std::cout << interleaved << '\n';
  } else {
    std::cerr << "variant 12: calculation failed\n";
  }

  if (replace_status == successCode) {
    std::cout << replaced << '\n';
  } else {
    std::cerr << "variant 10: calculation failed\n";
  }

  int output_status = successCode;

  if (!std::cout) {
    output_status = errorCode;
  }

  std::free(first);
  std::free(interleaved);
  std::free(replaced);

  if (output_status == errorCode || interleave_status == errorCode || replace_status == errorCode) {
    return errorCode;
  }

  return successCode;
}

int main()
{
  return sergeev::process();
}
