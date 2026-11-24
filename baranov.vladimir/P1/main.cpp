#include <cstddef>
#include <iostream>
#include <limits>

namespace baranov {
  const int input_error = 1;
  const int calculation_error = 2;
  const int even_divisor = 2;
}

int main()
{
  const std::size_t count_limit = std::numeric_limits< std::size_t >::max();
  int number = 0;
  int maximum = 0;
  std::size_t maximum_count = 0;
  std::size_t even_count = 0;
  std::size_t longest_even_count = 0;
  bool maximum_overflow = false;
  bool even_overflow = false;

  while ((std::cin >> number) && (number != 0)) {
    if ((maximum_count == 0) || (number > maximum)) {
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

    if (number % baranov::even_divisor == 0) {
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

  if (!std::cin || (number != 0)) {
    std::cerr << "Input error: expected integers ending with zero\n";
    return baranov::input_error;
  }

  int result = 0;
  if ((maximum_count == 0) || maximum_overflow) {
    std::cerr << "Cannot count maximum elements: empty sequence or overflow\n";
    result = baranov::calculation_error;
  } else {
    std::cout << maximum_count << '\n';
  }
  if (even_overflow) {
    std::cerr << "Cannot count even elements: overflow\n";
    result = baranov::calculation_error;
  } else {
    std::cout << longest_even_count << '\n';
  }
  return result;
}
