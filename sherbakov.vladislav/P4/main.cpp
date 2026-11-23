#include <cctype>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace sherbakov {
  char * readLine(std::istream & in, std::size_t & outLen);
  std::size_t difLat(const char * str);
  int repDgt(const char * str);
}

char * sherbakov::readLine(std::istream & in, std::size_t & outLen)
{
  const std::size_t initCap = 32;
  const std::size_t growth = 2;
  const std::size_t maxCap = std::numeric_limits< std::size_t >::max();

  std::size_t cap = initCap;
  char * buf = new char[cap];
  std::size_t len = 0;

  const std::ios_base::fmtflags savedFlags = in.flags();
  in >> std::noskipws;

  char ch = '\0';
  while ((in >> ch) && (ch != '\n')) {
    if (len + 1 >= cap) {
      if (cap == maxCap) {
        in.flags(savedFlags);
        delete[] buf;
        throw std::length_error("Maximum string size exceeded");
      }

      std::size_t newCap = 0;
      if (cap > (maxCap / growth)) {
        newCap = maxCap;
      } else {
        newCap = cap * growth;
      }

      char * newBuf = nullptr;
      try {
        newBuf = new char[newCap];
      } catch (...) {
        in.flags(savedFlags);
        delete[] buf;
        throw;
      }

      for (std::size_t i = 0; i < len; ++i) {
        newBuf[i] = buf[i];
      }
      delete[] buf;
      buf = newBuf;
      cap = newCap;
    }

    buf[len] = ch;
    ++len;
  }

  in.flags(savedFlags);

  if ((len == 0) && (!in)) {
    delete[] buf;
    return nullptr;
  }

  buf[len] = '\0';
  outLen = len;
  return buf;
}

std::size_t sherbakov::difLat(const char * str)
{
  if (str == nullptr) {
    throw std::invalid_argument("Null pointer passed to difLat");
  }

  bool seen[26] = {false};
  std::size_t count = 0;

  for (std::size_t i = 0; str[i] != '\0'; ++i) {
    const unsigned char c = static_cast< unsigned char >(str[i]);

    std::size_t idx = 26;
    if ((c >= 'a') && (c <= 'z')) {
      idx = static_cast< std::size_t >(c - 'a');
    } else if ((c >= 'A') && (c <= 'Z')) {
      idx = static_cast< std::size_t >(c - 'A');
    }

    if ((idx < 26) && (seen[idx] == false)) {
      seen[idx] = true;
      ++count;
    }
  }

  return count;
}

int sherbakov::repDgt(const char * str)
{
  if (str == nullptr) {
    throw std::invalid_argument("Null pointer passed to repDgt");
  }

  bool seen[10] = {false};
  int repeats = 0;

  for (std::size_t i = 0; str[i] != '\0'; ++i) {
    const unsigned char c = static_cast< unsigned char >(str[i]);
    if (std::isdigit(c) != 0) {
      const std::size_t idx = static_cast< std::size_t >(c - '0');
      if (seen[idx]) {
        ++repeats;
      } else {
        seen[idx] = true;
      }
    }
  }

  if (repeats > 0) {
    return 1;
  }
  return 0;
}

int main()
{
  const int errCode = 1;

  std::size_t len = 0;
  char * line = nullptr;

  try {
    line = sherbakov::readLine(std::cin, len);
  } catch (const std::exception & e) {
    std::cerr << "Memory allocation error while reading string: " << e.what() << "\n";
    return errCode;
  }

  if (line == nullptr) {
    std::cerr << "Stream read error or end of file\n";
    return errCode;
  }

  std::size_t distinct = 0;
  int repeats = 0;

  try {
    distinct = sherbakov::difLat(line);
    repeats = sherbakov::repDgt(line);
  } catch (const std::exception & e) {
    delete[] line;
    std::cerr << "Computation error: " << e.what() << "\n";
    return errCode;
  }

  std::cout << distinct << "\n";
  std::cout << repeats << "\n";

  delete[] line;
  return 0;
}

