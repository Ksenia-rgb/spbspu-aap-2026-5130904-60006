#include <cctype>
#include <cstddef>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace batyushov
{
  const int allocError = 1;
  const std::size_t startCapacity = 16;
  const char * const allocErrorMessage = "Ошибка: не удалось разместить строку в динамической памяти\n";
  const char * const inputErrorMessage = "Ошибка: не удалось прочитать строку\n";

  std::size_t str_len(const char * src) noexcept
  {
    std::size_t len = 0;
    while (src[len] != '\0')
    {
      ++len;
    }
    return len;
  }

  char * remove_dec(char * dest, const char * src) noexcept
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

  char * upp_low(char * dest, const char * src) noexcept
  {
    std::size_t i = 0;
    for (; src[i] != '\0'; ++i)
    {
      const unsigned char symbol = static_cast< unsigned char >(src[i]);
      dest[i] = std::isupper(symbol) ? static_cast< char >(std::tolower(symbol)) : src[i];
    }
    dest[i] = '\0';
    return dest;
  }

  char * read_line()
  {
    std::size_t capacity = startCapacity;
    std::size_t size = 0;
    char * buf = new char[capacity];

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
        char * new_buf = nullptr;
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
    char * line = nullptr;
    char * result = nullptr;

    try
    {
      line = read_line();
      result = new char[str_len(line) + 1];
    }
    catch (const std::exception &)
    {
      delete[] line;
      delete[] result;
      std::cerr << allocErrorMessage;
      return batyushov::allocError;
    }

    if (std::cin.bad())
    {
      delete[] line;
      delete[] result;
      std::cerr << inputErrorMessage;
      return batyushov::allocError;
    }

    std::cout << remove_dec(result, line) << '\n';
    std::cout << upp_low(result, line) << '\n';

    delete[] result;
    delete[] line;
    return 0;
  }
}

int main()
{
  return batyushov::run();
}
