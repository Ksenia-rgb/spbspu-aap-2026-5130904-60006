#include <cctype>
#include <climits>
#include <iostream>

namespace zakirov {
  const int calculation_error = 2;
  int run()
  {
    int number = 0;
    int prev = 0;
    int min = 0;
    long long min_count = 0;
    long long div_count = 0;

    bool has_previous = false;
    bool has_pair = false;
    bool min_overflow = false;
    bool div_overflow = false;

    std::cout << "Введите целые числа через пробел (0 — конец ввода):\n";

    while (true) {
      if (!(std::cin >> number)) {
        std::cerr << "Ошибка: нужны целые числа в диапазоне int и 0 в конце ввода.\n";
        return 1;
      }

      const int next = std::cin.peek();
      if (!std::cin.eof() && !std::isspace(next)) {
        std::cerr << "Ошибка: ввод содержит нецелое число или посторонние символы.\n";
        return 1;
      }

      if (number == 0) {
        break;
      }

      if (!has_previous || number < min) {
        min = number;
        min_count = 1;
        min_overflow = false;
      } else if (number == min) {
        if (min_count == LLONG_MAX) {
          min_overflow = true;
        } else {
          min_count++;
        }
      }
      if (has_previous) {
        has_pair = true;
        if (prev == -1 || number % prev == 0) {
          if (div_count == LLONG_MAX) {
            div_overflow = true;
          } else {
            div_count++;
          }
        }
      }

      prev = number;
      has_previous = true;
    }

    int result = 0;

    if (min_overflow) {
      std::cerr << "Ошибка в пункте 16: количество превышает диапазон long long.\n";
      result = calculation_error;
    } else {
      std::cout << "Пункт 16. Количество минимальных элементов: " << min_count << '\n';
    }

    if (!has_pair) {
      std::cerr << "Ошибка в пункте 11: нужно хотя бы два числа до нуля.\n";
      result = calculation_error;
    } else if (div_overflow) {
      std::cerr << "Ошибка в пункте 11: количество превышает диапазон long long.\n";
      result = calculation_error;
    } else {
      std::cout << "Пункт 11. Количество элементов, делящихся на предыдущий без "
                   "остатка: "
                << div_count << '\n';
    }

    return result;
  }
}

int main()
{
  return zakirov::run();
}
