#include <cctype>
#include <cstddef>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace batyushov
{
  const int allocError = 1;
  const int inputError = 2;
  const std::size_t startCapacity = 16;
  const char *const allocErrorMessage = "Error: memory allocation failed\n";
  const char *const inputErrorMessage = "Error: failed to read input\n";

  std::size_t strLen(const char *src) noexcept
  {
    std::size_t len = 0;
    while (src[len] != '\0')
    {
      ++len;
    }
    return len;
  }

  char *removeDec(char *dest, const char *src) noexcept
  {
    std::size_t j = 0;
    for (std::size_t i = 0; src[i] != '\0'; ++i)
    {
      if (!std::isdigit(static_cast< unsigned char >(src[i])))
      {
        dest[j++] = src[i];
      }
    }
    dest[j] = '\0';
    return dest;
  }

  char *uppLow(char *dest, const char *src) noexcept
  {
    std::size_t i = 0;
    for (; src[i] != '\0'; ++i)
    {
      const unsigned char symbol = static_cast< unsigned char >(src[i]);
      if (std::isupper(symbol))
      {
        dest[i] = static_cast< char >(std::tolower(symbol));
      }
      else
      {
        dest[i] = src[i];
      }
    }
    dest[i] = '\0';
    return dest;
  }

  char *readLine()
  {
    std::size_t capacity = startCapacity;
    std::size_t size = 0;
    char *buf = new char[capacity];

    char symbol = 0;
    while (std::cin.get(symbol) && symbol != '\n')
    {
      if (size + 1 == capacity)
      {
        if (capacity > std::numeric_limits< std::size_t >::max() / 2)
        {
          delete[] buf;
          throw std::length_error("string is too long");
        }
        const std::size_t new_capacity = capacity * 2;
        char *new_buf = nullptr;
        try
        {
          new_buf = new char[new_capacity];
        }
        catch (...)
        {
          delete[] buf;
          throw;
        }
        for (std::size_t i = 0; i < size; ++i)
        {
          new_buf[i] = buf[i];
        }
        delete[] buf;
        buf = new_buf;
        capacity = new_capacity;
      }
      buf[size++] = symbol;
    }
    buf[size] = '\0';
    return buf;
  }

  int run()
  {
    char *line = nullptr;
    char *result = nullptr;

    try
    {
      line = readLine();
      result = new char[strLen(line) + 1];
    }
    catch (const std::exception &)
    {
      delete[] line;
      delete[] result;
      std::cerr << allocErrorMessage;
      return allocError;
    }

    if (std::cin.bad() || line[0] == '\0')
    {
      delete[] line;
      delete[] result;
      std::cerr << inputErrorMessage;
      return inputError;
    }

    std::cout << removeDec(result, line) << '\n';
    std::cout << uppLow(result, line) << '\n';

    delete[] result;
    delete[] line;
    return 0;
  }
}

int main()
{
  return batyushov::run();
}
