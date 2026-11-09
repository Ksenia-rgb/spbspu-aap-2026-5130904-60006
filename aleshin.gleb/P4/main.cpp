#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace aleshin {

  const int ok = 0;
  const int no_memory = 1;

  std::size_t str_len(const char *s) noexcept
  {
    std::size_t n = 0;
    while (s[n] != '\0') {
      ++n;
    }
    return n;
  }

  std::size_t count_diff_lat(const char *s) noexcept
  {
    unsigned char seen[52] = {};
    std::size_t count = 0;
    for (; *s != '\0'; ++s) {
      const unsigned char c = static_cast< unsigned char >(*s);
      if (c >= 128 || !std::isalpha(c)) {
        continue;
      }
      const std::size_t idx = (c >= 'a' && c <= 'z') ? (c - 'a') : (c - 'A' + 26);
      if (!seen[idx]) {
        seen[idx] = 1;
        ++count;
      }
    }
    return count;
  }

  char *unite_two(const char *a, const char *b, char *out) noexcept
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

  char *read_line(std::istream &in)
  {
    std::size_t cap = 16;
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
        char *bigger = static_cast< char * >(std::malloc(new_cap));
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

  char *input = aleshin::read_line(std::cin);
  if (!input) {
    std::cerr << "error: cannot allocate memory for input\n";
    return aleshin::no_memory;
  }

  std::cout << aleshin::count_diff_lat(input) << "\n";

  const std::size_t la = aleshin::str_len(input);
  const std::size_t lb = aleshin::str_len(second);
  if (la > std::numeric_limits< std::size_t >::max() - lb - 1) {
    std::cerr << "error: result is too long\n";
    std::free(input);
    return aleshin::no_memory;
  }
  char *result = static_cast< char * >(std::malloc(la + lb + 1));
  if (!result) {
    std::cerr << "error: cannot allocate memory for result\n";
    std::free(input);
    return aleshin::no_memory;
  }
  std::cout << aleshin::unite_two(input, second, result) << "\n";

  std::free(result);
  std::free(input);
  return aleshin::ok;
}
