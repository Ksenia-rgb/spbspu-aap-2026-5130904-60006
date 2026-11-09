#include <iostream>

int main()
{
  int current_value = 0;
  int previous_value = 0;
  int value_count = 0;
  int last_non_zero = 0;

  int current_run_length = 0;
  int max_run_length = 0;
  int sign_changes = 0;

  while (true) {
    std::cin >> current_value;

    if (std::cin.fail()) {
      std::cerr << "Error: Invalid input data." << std::endl;
      return 1;
    }

    if (current_value == 0) {
      break;
    }

    value_count++;

    if (value_count == 1) {
      current_run_length = 1;
      max_run_length = 1;
    } else {
      if (current_value >= previous_value) {
        current_run_length++;
      } else {
        current_run_length = 1;
      }

      if (current_run_length > max_run_length) {
        max_run_length = current_run_length;
      }

      if (last_non_zero != 0) {
        if ((last_non_zero > 0 && current_value < 0) or (last_non_zero < 0 && current_value > 0)) {
          sign_changes++;
        }
      }
    }

    previous_value = current_value;
    if (current_value != 0) {
      last_non_zero = current_value;
    }
  }

  if (value_count == 0) {
    std::cerr << "Error: No characteristic can be calculated." << std::endl;
    return 2;
  }

  std::cout << max_run_length << std::endl;

  if (value_count == 1) {
    std::cerr << "Error: The sign change characteristic cannot be calculated." << std::endl;
    return 2;
  }

  std::cout << sign_changes << std::endl;

  return 0;
}
