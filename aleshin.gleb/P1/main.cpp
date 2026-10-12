#include <iostream>
#include <limits>

namespace aleshin {
const unsigned long long limit = std::numeric_limits<unsigned long long>::max();
int Run() {
  bool empty = true;
  bool got_zero = false;
  int max_num = 0;
  unsigned long long max_count = 0;
  bool count_overflow = false;
  int prev = 0;
  unsigned long long run = 0;
  unsigned long long best_run = 0;
  bool run_overflow = false;
  int num = 0;
  while (std::cin >> num) {
    if (num == 0) {
      got_zero = true;
      break;
    }
    if (empty || num > max_num) {
      max_num = num;
      max_count = 1;
      count_overflow = false;
    } else if (num == max_num) {
      if (max_count == limit) {
        count_overflow = true;
      } else {
        ++max_count;
      }
    }
    if (!empty && num == prev) {
      if (run == limit) {
        run_overflow = true;
      } else {
        ++run;
      }
    } else {
      prev = num;
      run = 1;
    }
    if (run > best_run) {
      best_run = run;
    }
    empty = false;
  }
  if (!got_zero) {
    std::cerr << "Error: введенные данные не являются"
              << "последовательностью целых чисел, завершающихя нулем\n";
    return 1;
  }
  int code = 0;
  if (empty || count_overflow) {
    std::cerr << "Error: невозможно расчитать CNT-MAX: "
              << "последовательност слишком короткая или длинная\n";
    code = 2;
  } else {
    std::cout << max_count << '\n';
  }
  if (run_overflow) {
    std::cerr << "Error: невозможно расчитать EQL-SEQ: "
              << "последовательност слишком длинная\n";
    code = 2;
  } else {
    std::cout << best_run << '\n';
  }
  return code;
}
}
int main() { return aleshin::Run(); }
