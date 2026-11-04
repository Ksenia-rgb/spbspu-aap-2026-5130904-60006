#include <iostream>
#include <limits>
constexpr int inputErrorCode = 1;
constexpr int errorSum = 2;
int main()
{
  int prev = 0;
  std::cin >> prev;
  if (!(std::cin >> prev)) {
    std::cerr << "Input error";
    return inputErrorCode;
  }
  if (prev == 0) {
    std::cout << "0\n";
    return 0;
  }

  int curr = 0;
  std::cin >> curr;
  if (!(std::cin >> curr)) {
    std::cerr << "Input error";
    return inputErrorCode;
  }
  if (curr == 0) {
    std::cout << "0\n";
    return 0;
  }

  int count = 0;
  int count_next_is_sum = 0;
  int next = 0;
  bool flag = false;
  while ((std::cin >> next) && (next != 0)) {
    flag = true;
    if ((prev > curr) && (curr > next)) {
      if (count == std::numeric_limits< int >::max()) {
        std::cerr << "Overflow\n";
        return errorSum;
      }
      count++;
    }
    if (next == (prev + curr)) {
      if (count_next_is_sum == std::numeric_limits< int >::max()) {
        std::cerr << "Overflow\n";
        return errorSum;
      }
      count_next_is_sum++;
    }
    prev = curr;
    curr = next;
  }
  if (!std::cin && !std::cin.eof()) {
    std::cerr << "Error: Invalid character in input\n";
    return inputErrorCode;
  }
  std::cout << count << "\n";
  if (!flag) {
    return errorSum;
  }
  std::cout << count_next_is_sum << "\n";
}
