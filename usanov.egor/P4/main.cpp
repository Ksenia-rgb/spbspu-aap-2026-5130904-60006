#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>

namespace usanov
{
  std::size_t removeSpaces(const char * src, char * dst)
  {
    std::size_t len = 0;
    bool pending_space = false;
    for (const char * p = src; *p != '\0'; ++p)
    {
      if (std::isspace(static_cast< unsigned char >(*p)))
      {
        pending_space = true;
      }
      else
      {
        if (pending_space && len > 0)
        {
          dst[len++] = ' ';
        }
        pending_space = false;
        dst[len++] = *p;
      }
    }
    dst[len] = '\0';
    return len;
  }

  std::size_t toLower(const char * src, char * dst)
  {
    std::size_t len = 0;
    for (; src[len] != '\0'; ++len)
    {
      const unsigned char symbol = static_cast< unsigned char >(src[len]);
      dst[len] = std::isupper(symbol) ? static_cast< char >(std::tolower(symbol)) : src[len];
    }
    dst[len] = '\0';
    return len;
  }
  
  bool readLine(char *& line, std::size_t & length)
  {
    std::size_t capacity = 16;
    line = static_cast< char * >(std::malloc(capacity));
    if (line == nullptr)
    {
      return false;
    }
    length = 0;
    char symbol = 0;
    while (std::cin.get(symbol) && symbol != '\n')
    {
      if (length + 2 > capacity)
      {
        const std::size_t new_capacity = capacity * 2;
        char * const grown = static_cast< char * >(std::malloc(new_capacity));
        if (grown == nullptr)
        {
          std::free(line);
          line = nullptr;
          return false;
        }
        for (std::size_t i = 0; i < length; ++i)
        {
          grown[i] = line[i];
        }
        std::free(line);
        line = grown;
        capacity = new_capacity;
      }
      line[length++] = symbol;
    }
    line[length] = '\0';
    return true;
  }
}

int main()
{
  char * line = nullptr;
  std::size_t length = 0;
  if (!usanov::readLine(line, length))
  {
    std::cerr << "Not enough memory for input string\n";
    return 1;
  }

  char * const spaces_removed = static_cast< char * >(std::malloc(length + 1));
  char * const lowered = static_cast< char * >(std::malloc(length + 1));
  if (spaces_removed == nullptr || lowered == nullptr)
  {
    std::free(line);
    std::free(spaces_removed);
    std::free(lowered);
    std::cerr << "Not enough memory for result\n";
    return 1;
  }

  usanov::removeSpaces(line, spaces_removed);
  std::cout << spaces_removed << '\n';
  usanov::toLower(line, lowered);
  std::cout << lowered << '\n';

  std::free(line);
  std::free(spaces_removed);
  std::free(lowered);
  return 0;
}