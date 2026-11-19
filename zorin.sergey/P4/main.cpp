#include <cctype>
#include <climits>
#include <cstddef>
#include <iostream>
#include <limits>

namespace zorin
{
  char * missingLetters(const char * src, char * out) noexcept
  {
    bool seen[26] = {};
    for (; *src; ++src)
    {
      const int ch = std::tolower(static_cast< unsigned char >(*src));
      if (ch >= 'a' && ch <= 'z')
      {
        seen[ch - 'a'] = true;
      }
    }
    char * pos = out;
    for (int i = 0; i < 26; ++i)
    {
      if (!seen[i])
      {
        *pos++ = static_cast< char >('a' + i);
      }
    }
    *pos = '\0';
    return out;
  }

  char * uncommon(const char * a, const char * b, char * out) noexcept
  {
    bool first[UCHAR_MAX + 1] = {};
    bool second[UCHAR_MAX + 1] = {};
    for (; *a; ++a)
    {
      first[static_cast< unsigned char >(*a)] = true;
    }
    for (; *b; ++b)
    {
      second[static_cast< unsigned char >(*b)] = true;
    }
    char * pos = out;
    for (unsigned int i = 1; i <= UCHAR_MAX; ++i)
    {
      if (first[i] != second[i])
      {
        *pos++ = static_cast< char >(i);
      }
    }
    *pos = '\0';
    return out;
  }

  char * readLine(std::istream & in)
  {
    std::size_t capacity = 32;
    std::size_t size = 0;
    char * line = new char[capacity];
    try
    {
      char ch = '\0';
      while (in.get(ch) && ch != '\n')
      {
        if (size == capacity - 1)
        {
          if (capacity > std::numeric_limits< std::size_t >::max() / 2)
          {
            delete[] line;
            return nullptr;
          }
          capacity *= 2;
          char * bigger = new char[capacity];
          for (std::size_t i = 0; i < size; ++i)
          {
            bigger[i] = line[i];
          }
          delete[] line;
          line = bigger;
        }
        line[size++] = ch;
      }
    }
    catch (...)
    {
      delete[] line;
      throw;
    }
    line[size] = '\0';
    return line;
  }
}

int main()
{
  char * line = nullptr;
  try
  {
    line = zorin::readLine(std::cin);
  }
  catch (...)
  {
    std::cerr << "Cannot allocate the input string\n";
    return 1;
  }
  if (!line || std::cin.bad())
  {
    delete[] line;
    std::cerr << "Cannot read the input string\n";
    return 1;
  }

  char missing[27];
  char unique[UCHAR_MAX + 1];
  std::cout << zorin::missingLetters(line, missing) << '\n';
  std::cout << zorin::uncommon(line, "abc ef", unique) << '\n';
  delete[] line;
}
