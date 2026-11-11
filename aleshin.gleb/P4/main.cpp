#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace aleshin
{
  const int ok = 0;
  const int no_memory = 1;
  const int no_input = 2;
  const std::size_t latin_count = 26;
  const std::size_t letters_total = 52;
  const unsigned char ascii_limit = 128;
  const std::size_t start_capacity = 16;

  std::size_t strLen(const char *s) noexcept
  {
    std::size_t n = 0;
    while (s[n] != '\0') {
      ++n;
    }
    return n;
  }

  std::size_t countDiffLat(const char *s) noexcept
  {
    unsigned char seen[letters_total] = {};
    std::size_t count = 0;
    for (; *s != '\0'; ++s) {
      const unsigned char c = static_cast< unsigned char >(*s);
      if (c >= ascii_limit || !std::isalpha(c)) {
        continue;
      }
      const std::size_t idx = (c >= 'a' && c <= 'z') ? static_cast< std::size_t >(c - 'a')
                                                     : static_cast< std::size_t >(c - 'A') + latin_count;
      if (!seen[idx]) {
        seen[idx] = 1;
        ++count;
      }
    }
    return count;
  }

  char *uniteTwo(const char *a, const char *b, char *out) noexcept
  {
    std::size_t i = 0;
    std::size_t k = 0;
    while (a[i] != '\0' && b[i] != '\0') {
      out[k++] = a[i];
      out[k++] = b[i];
      ++i;
    }
    for (const char *p = a + i; *p != '\0'; ++p) {
      out[k++] = *p;
    }
    for (const char *p = b + i; *p != '\0'; ++p) {
      out[k++] = *p;
    }
    out[k] = '\0';
    return out;
  }

  char *readLine(std::istream &in)
  {
    std::size_t cap = start_capacity;
    std::size_t len = 0;
    char *buf = static_cast< char * >(std::malloc(cap));
    if (!buf) {
      return nullptr;
    }
    char c = '\0';
    while (in.get(c) && c != '\n') {
      if (len + 1 == cap) {
        if (cap > std::numeric_limits< std::size_t >::max() / 2) {
          std::free(buf);
          return nullptr;
        }
        const std::size_t new_cap = cap * 2;
        char *const bigger = static_cast< char * >(std::malloc(new_cap));
        if (!bigger) {
          std::free(buf);
          return nullptr;
        }
        for (std::size_t i = 0; i < len; ++i) {
          bigger[i] = buf[i];
        }
        std::free(buf);
        buf = bigger;
        cap = new_cap;
      }
      buf[len++] = c;
    }
    buf[len] = '\0';
    return buf;
  }
}

int main()
{
  const char second[] = "def_";

  char *const input = aleshin::readLine(std::cin);
  if (!input) {
    std::cerr << "error: cannot allocate memory for input\n";
    return aleshin::no_memory;
  }
  if (std::cin.eof() && input[0] == '\0') {
    std::cerr << "error: empty input\n";
    std::free(input);
    return aleshin::no_input;
  }

  std::cout << aleshin::countDiffLat(input) << "\n";

  const std::size_t la = aleshin::strLen(input);
  const std::size_t lb = aleshin::strLen(second);
  if (la > std::numeric_limits< std::size_t >::max() - lb - 1) {
    std::cerr << "error: result is too long\n";
    std::free(input);
    return aleshin::no_memory;
  }
  char *const result = static_cast< char * >(std::malloc(la + lb + 1));
  if (!result) {
    std::cerr << "error: cannot allocate memory for result\n";
    std::free(input);
    return aleshin::no_memory;
  }
  std::cout << aleshin::uniteTwo(input, second, result) << "\n";

  std::free(result);
  std::free(input);
  return aleshin::ok;
}
