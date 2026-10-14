#include <iostream>

int main()
{
  int previous2 = 0;
  int previous1 = 0;
  int current = 0;
  int elements = 0;

  int count_grt = 0;
  int count_pth = 0;
  bool after_zero = false;

  while (std::cin >> current) {
    if (after_zero) {
      continue;
    }

    if (current == 0) {
      after_zero = true;
      continue;
    }

    if (elements >= 2) {
      if (previous1 < previous2 && previous1 > current) {
        ++count_grt;
      }

      const long long a = previous2;
      const long long b = previous1;
      const long long c = current;
      if (a * a + b * b == c * c) {
        ++count_pth;
      }
    }

    previous2 = previous1;
    previous1 = current;
    ++elements;
  }

  if (!after_zero) {
    if (std::cin.eof()) {
      std::cerr << "Error: missing terminating zero\n";
    } else {
      std::cerr << "Error: invalid input\n";
    }
    return 1;
  }

  if (!std::cin.eof()) {
    std::cerr << "Error: invalid input after zero\n";
    return 1;
  }

  std::cout << count_grt << '\n' << count_pth << '\n';
  return 0;
}
