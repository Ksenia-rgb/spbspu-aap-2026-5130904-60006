#include <iostream>

bool checkInput()
{
  if (std::cin.fail()) {
    std::cerr << "Input error";
    return false;
  }
  return true;
}

int main()
{
  int prev = 0;
  std::cin >> prev;
  if (!checkInput()) {
    std::cerr << "Input error";
    return 1;
  }
  if (prev == 0) {
    std::cout << "0\n";
    return 0;
  }

  int curr = 0;
  std::cin >> curr;
  if (!checkInput()) {
    std::cerr << "Input error";
    return 1;
  }
  if (curr == 0) {
    std::cout << "0\n";
    return 0;
  }

  int count = 0;
  int count_next_is_sum = 0;
  int next = 0;

  while ((std::cin >> next) && (next != 0)) {
    if ((prev > curr) && (curr > next)) {
      count++;
    }
    if (next == (prev + curr)) {
      count_next_is_sum++;
    }
    prev = curr;
    curr = next;
  }
  if (!std::cin && !std::cin.eof()) {
    std::cerr << "Error: Invalid character in input\n";
    return 1;
  }
  std::cout << count << "\n";
  std::cout << count_next_is_sum << "\n";
}
