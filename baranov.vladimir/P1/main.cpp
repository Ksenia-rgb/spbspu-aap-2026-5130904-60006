
#include <iostream>

namespace baranov {
int countEqual() {
  int number = 0;
  int previous = 0;
  int current_count = 0;
  int max_count = 0;

  while (true) {
    if (!(std::cin >> number)) {
      std::cerr << "Input error\n";
      return 1;
    }

    if (number == 0) {
      break;
    }

    if (current_count > 0 && number == previous) {
      current_count++;
    } else {
      current_count = 1;
    }

    if (current_count > max_count) {
      max_count = current_count;
    }

    previous = number;
  }

  std::cout << max_count << '\n';
  return 0;
}
} // namespace baranov
int main() { return baranov::countEqual(); }
