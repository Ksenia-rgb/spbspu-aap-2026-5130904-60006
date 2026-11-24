#include <iostream>
#include <limits>
#include <cstddef>
namespace belova {
  constexpr int ERROR_CODE = 1;
  bool isPythagorean(int a, int b, int c)
  {
    const unsigned long long x = a < 0 ? -static_cast< long long >(a) : a;
    const unsigned long long y = b < 0 ? -static_cast< long long >(b) : b;
    const unsigned long long z = c < 0 ? -static_cast< long long >(c) : c;
    return x * x + y * y == z * z;
  }
}
int main()
{
  int previous = 0;
  int a = 0;
  int b = 0;
  int current = 0;
  int sign_changes = 0;
  int triples = 0;
  std::size_t count = 0;
  bool sign_changes_overflow = false;
  bool triples_overflow = false;
  bool terminated = false;
  while (std::cin >> current) {
    if (current == 0) {
      terminated = true;
      break;
    }
    if (count > 0 && ((previous < 0 && current > 0) || (previous > 0 && current < 0))) {
      if (sign_changes == std::numeric_limits< int >::max()) {
        sign_changes_overflow = true;
      } else {
        ++sign_changes;
      }
    }
    if (count == 0) {
      a = current;
    } else if (count == 1) {
      b = current;
    } else {
      if (belova::isPythagorean(a, b, current)) {
        if (triples == std::numeric_limits< int >::max()) {
          triples_overflow = true;
        } else {
          ++triples;
        }
      }
      a = b;
      b = current;
    }
    previous = current;
    ++count;
  }
  if (!std::cin.eof() && !terminated) {
    std::cerr << "Error: invalid input sequence\n";
    return belova::ERROR_CODE;
  }
  if (sign_changes_overflow) {
    std::cerr << "Error: sign changes counter overflow\n";
  }
  if (triples_overflow) {
    std::cerr << "Error: triples counter overflow\n";
  }
  if (sign_changes_overflow || triples_overflow) {
    return belova::ERROR_CODE;
  }
  std::cout << sign_changes << "\n";
  std::cout << triples << "\n";
  return 0;
}
