#include <clocale>
#include <cstddef>
#include <iostream>

int main() {
  setlocale(LC_ALL, "ru");
  int x = 0;
  bool term = false;
  int maxv = 0;
  int secondmax = 0;
  bool hmax = false;
  bool hsecondmax = false;
  size_t count = 0;
  size_t countmax = 0;

  while (std::cin >> x) {
    if (x == 0) {
      term = true;
      break;
    }

    if (!hmax) {
      maxv = x;
      hmax = true;
      countmax = 1;
    } else if (x > maxv) {
      secondmax = maxv;
      hsecondmax = true;
      maxv = x;
      countmax = 1;
    } else if (x == maxv) {
      ++countmax;
      secondmax = maxv;
      hsecondmax = true;
    } else if (!hsecondmax || x > secondmax) {
      secondmax = x;
      hsecondmax = true;
    }
    count++;
  }
  if (!term) {
    if (std::cin.eof()) {
      std::cerr << "error: The sequence is not terminated with a zero\n";
    } else {
      std::cerr << "ошибка: The input data is not a sequence of integers\n ";
    }
    return 1;
  }
  if (!hsecondmax) {
    std::cout << "LOG-MAX: 0" << '\n';
    std::cerr << "error: the sequence is too short\n";
    return 2;
  }

  std::cout << "SUB-MAX: " << secondmax << '\n'
            << "LOG-MAX: " << countmax << '\n';

  return 0;
}
