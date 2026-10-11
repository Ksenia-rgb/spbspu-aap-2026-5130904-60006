
#include <iostream>

namespace baranov {
  int countEqual() {
    int number = 0;
    int previous = 0;
    int currentCount = 0;
    int maxCount = 0;

    while (true) {
      if (!(std::cin >> number)) {
        std::cerr << "Input error\n";
        return 1;
      }

      if (number == 0) {
        break;
      }

      if (currentCount > 0 && number == previous) {
        currentCount++;
      } else {
        currentCount = 1;
      }

      if (currentCount > maxCount) {
        maxCount = currentCount;
      }

      previous = number;
    }

    std::cout << maxCount << '\n';
    return 0;
  }
}

int main() {
  return baranov::countEqual();
}
