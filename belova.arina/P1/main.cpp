#include <iostream>
#include <limits>
constexpr int ERROR_CODE = 1;
namespace belova {
  bool isPythagorean(int a, int b, int c)
  {
    const unsigned long long x = a < 0 ? -static_cast< long long >(a) : a;
    const unsigned long long y = b < 0 ? -static_cast< long long >(b) : b;
    const unsigned long long z = c < 0 ? -static_cast< long long >(c) : c;
    return x * x + y * y == z * z;
  }
}
    unsigned long long x = a < 0 ? -static_cast< long long >(a) : a;
    unsigned long long y = b < 0 ? -static_cast< long long >(b) : b;
    unsigned long long z = c < 0 ? -static_cast< long long >(c) : c;
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
  int count = 0;
  while (std::cin >> current) {
    if (current == 0) {
      std::cout << sign_changes << "\n";
      std::cout << triples << "\n";
      return 0;
    }
    if (count > 0 && ((previous < 0 && current > 0) || (previous > 0 && current < 0))) {
      ++sign_changes;
      if (signChanges == std::numeric_limits< int >::max()) {
        std::cerr << "Error: sign Changes counter overflow\n";
        return ERROR_CODE;
      }
      ++signChanges;
    }
    if (count == 0) {
      a = current;
    } else if (count == 1) {
      b = current;
    } else {
      if (belova::isPythagorean(a, b, current)) {
        if (triples == std::numeric_limits< int >::max()) {
          std::cerr << "Error: triples counter overflow\n";
          return ERROR_CODE;
        }
        ++triples;
      }
      a = b;
      b = current;
    }
    previous = current;
    ++count;
  }
  if (!std::cin.eof()) {
    std::cerr << "Error: invalid input sequence\n";
    return ERROR_CODE;
  }
  std::cout << sign_changes << "\n";
  std::cout << triples << "\n";
  return 0;
}
