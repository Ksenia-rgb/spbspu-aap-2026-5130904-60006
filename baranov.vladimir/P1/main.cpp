#include <cstddef>
#include <iostream>
#include <limits>

namespace baranov {
  constexpr int input_error = 1;
  constexpr int calculation_error = 2;

  int processSequence()
  {
    const std::size_t count_limit = std::numeric_limits< std::size_t >::max();
    int number = 0;
    int maximum = 0;
    std::size_t maximum_count = 0;
    std::size_t even_count = 0;
    std::size_t longest_even_count = 0;
    bool has_numbers = false;
    bool maximum_overflow = false;
    bool even_overflow = false;

    while (std::cin >> number) {
      if (number == 0) {
        break;
      }

      if (!has_numbers || number > maximum) {
        maximum = number;
        maximum_count = 1;
        maximum_overflow = false;
      } else if (number == maximum) {
        if (maximum_count == count_limit) {
          maximum_overflow = true;
        } else {
          ++maximum_count;
        }
      }
      has_numbers = true;

      if (number % 2 == 0) {
        if (even_count == count_limit) {
          even_overflow = true;
        } else {
          ++even_count;
        }
        if (even_count > longest_even_count) {
          longest_even_count = even_count;
        }
      } else {
        even_count = 0;
      }
    }

    if (!std::cin || number != 0) {
      std::cerr << "Input error: expected integers ending with zero\n";
      return input_error;
    }

    int result = 0;
    if (!has_numbers || maximum_overflow) {
      std::cerr << "CNT-MAX: empty sequence or counter overflow\n";
      result = calculation_error;
    } else {
      std::cout << maximum_count << '\n';
    }

    if (even_overflow) {
      std::cerr << "EVN-CNT: counter overflow\n";
      result = calculation_error;
    } else {
      std::cout << longest_even_count << '\n';
    }
    return result;
  }
}

int main()
{
  return baranov::processSequence();
}
