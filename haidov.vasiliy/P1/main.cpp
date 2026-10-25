#include <iostream>
#include <limits>

const int correct_result = 0;
const int invalid_input = 1;
const int calculation_error = 2;

namespace haidov {
  int sequence()
  {
    int element = 0;
    size_t len_m_d = 0;
    size_t len_max = 0;
    int last_el = 0;
    int max = 0;
    while (std::cin >> element) {
      if (std::cin.bad() || std::cin.eof() || std::cin.fail()) {
        std::cerr << "wrong element in sequence" << std::endl;
        return invalid_input;
      }
      if (element == 0) {
        std::cout << len_m_d << "\n";
        if (last_el == 0) {
          std::cerr << "Amount of elements after maximal uncounted" << std::endl;
          return calculation_error;
        }
        std::cout << len_max << std::endl;
        return correct_result;
      }
      if (last_el < element) {
        len_m_d = 0;
      }
      if (max < element) {
        len_max = 0;
        max = element;
      } else {
        len_max += 1;
      }
      last_el = element;
      if (len_m_d > std::numeric_limits< size_t >::max() - 1) {
        return calculation_error;
      }
      if (len_max > std::numeric_limits< size_t >::max() - 1) {
        return calculation_error;
      }
      len_m_d += 1;
    }
    return correct_result;
  }
}

int main()
{
  haidov::sequence();
  return 0;
}
