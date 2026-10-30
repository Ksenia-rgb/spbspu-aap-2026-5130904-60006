#include <iostream>
namespace belova {
bool isPythagorean(int a, int b, int c) {
  unsigned long long x = a < 0 ? -static_cast<long long>(a) : a;
  unsigned long long y = b < 0 ? -static_cast<long long>(b) : b;
  unsigned long long z = c < 0 ? -static_cast<long long>(c) : c;
  return x * x + y * y == z * z;
}
} // namespace belova
int main() {
  int previous = 0;
  int a = 0;
  int b = 0;
  int current = 0;
  int signChanges = 0;
  int triples = 0;
  int count = 0;
  while (std::cin >> current) {
    if (current == 0) {
      std::cout << signChanges << "\n";
      std::cout << triples << "\n";
      return 0;
    }
    if (count > 0 &&
        ((previous < 0 && current > 0) || (previous > 0 && current < 0))) {
      ++signChanges;
    }
    if (count == 0) {
      a = current;
    } else if (count == 1) {
      b = current;
    } else {
      if (belova::isPythagorean(a, b, current)) {
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
    return 1;
  }
  std::cout << signChanges << "\n";
  std::cout << triples << "\n";
  return 0;
}
