#include <iostream>
#include <limits>

namespace sergeev {
  const int success_code = 0;
  const int invalid_input_code = 1;
  const int calculation_error_code = 2;

  void processNumber(int value, int & previous, int & current, int & count_10, int & count_16, int & minimum,
      bool & has_previous, bool & has_current, bool & has_minimum, bool & overflow_10, bool & overflow_16);

  int printResults(int count_10, int count_16, bool overflow_10, bool overflow_16);

  int process();
}

void sergeev::processNumber(int value, int & previous, int & current, int & count_10, int & count_16, int & minimum,
    bool & has_previous, bool & has_current, bool & has_minimum, bool & overflow_10, bool & overflow_16)
{
  if (!has_previous) {
    previous = value;
    has_previous = true;
  } else if (!has_current) {
    current = value;
    has_current = true;
  } else {
    if (current < previous && current > value) {
      if (!overflow_10) {
        if (count_10 == std::numeric_limits< int >::max()) {
          overflow_10 = true;
        } else {
          ++count_10;
        }
      }
    }

    previous = current;
    current = value;
  }

  if (!has_minimum) {
    minimum = value;
    count_16 = 1;
    has_minimum = true;
  } else if (value < minimum) {
    minimum = value;
    count_16 = 1;
    overflow_16 = false;
  } else if (value == minimum) {
    if (!overflow_16) {
      if (count_16 == std::numeric_limits< int >::max()) {
        overflow_16 = true;
      } else {
        ++count_16;
      }
    }
  }
}

int sergeev::printResults(int count_10, int count_16, bool overflow_10, bool overflow_16)
{
  int result_code = success_code;

  if (overflow_10) {
    std::cerr << "error calculation 10\n";
    result_code = calculation_error_code;
  } else {
    std::cout << count_10 << '\n';
  }

  if (overflow_16) {
    std::cerr << "error calculation 16\n";
    result_code = calculation_error_code;
  } else {
    std::cout << count_16 << '\n';
  }

  return result_code;
}

int sergeev::process()
{
  int previous = 0;
  int current = 0;
  int value = 0;

  int count_10 = 0;
  int count_16 = 0;
  int minimum = 0;

  bool has_previous = false;
  bool has_current = false;
  bool has_minimum = false;

  bool overflow_10 = false;
  bool overflow_16 = false;

  while (std::cin >> value && value != 0) {
    sergeev::processNumber(value, previous, current, count_10, count_16, minimum, has_previous, has_current,
        has_minimum, overflow_10, overflow_16);
  }

  if (!std::cin) {
    std::cerr << "error import\n";
    return invalid_input_code;
  }

  return sergeev::printResults(count_10, count_16, overflow_10, overflow_16);
}

int main()
{
  return sergeev::process();
}
