#include <iostream>
#include <limits>

int main()
{
  int max = std::numeric_limits< int >::min();
  int count = 0;
  int a_count = 0;
  int b_count = 0;
  int b_max = 0;
  int n = 0;
  int cur = 0;
  while (true) {
    if (!(std::cin >> n)) {
      std::cerr << "Expects error output (return code 1)";
      return 1;
    }

    if (n > max) {
      max = n;
      a_count = 0;
    } else {
      a_count++;
    }

    if (count == 0) {
      cur = n;
      b_count = 1;
    } else {
      b_max = b_max < b_count ? b_count : b_max;
      if (n >= cur) {
        b_count++;
      } else {
        b_count = 1;
      }
      cur = n;
    }

    count++;

    if (n == 0) {
      if (count < 2) {
        if (count == 1) {
          std::cout << b_max << " 1st\n";
        }
        std::cerr << "Expects error output (return code 2)";
        return 2;
      }
      std::cout << b_max << " 1st\n";
      std::cout << a_count - 1 << " 2nd\n";
      break;
    }
  }
}
