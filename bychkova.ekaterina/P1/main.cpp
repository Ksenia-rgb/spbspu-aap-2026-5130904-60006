#include <iostream>

int main(){

  int one = 0;
  int two = 0;
  int cout = 0;
  int last_non_zero = 0;

  int dline_vos = 0;
  int max_len = 0;
  int sign_changes = 0;

  while (true) {
    std::cin >> one;

    if (std::cin.fail()) {
      std::cerr << "Error: Invalid input data." << std::endl;
      return 1;
    }

    if (one == 0) {
      break;
    }

    cout++;

    if (cout == 1) {
      dline_vos = 1;
      max_len = 1;
    }

    else {
      if (one >= two) {
        dline_vos++;
      } else {
        dline_vos = 1;
      }

      if (dline_vos > max_len) {
        max_len = dline_vos;
      }

      if (last_non_zero != 0) {
        if ((last_non_zero > 0 && one < 0) or (last_non_zero < 0 && one > 0)) {
          sign_changes++;
        }
      }
    }

    two = one;
    if (one != 0) {
      last_non_zero = one;
    }
  }

  if (cout == 0) {
    std::cerr << "Error: No characteristic can be calculated."
              << std::endl;
    return 2;
  }

  std::cout << max_len << std::endl;

  if (cout == 1) {
    std::cerr << "Error: The sign change characteristic cannot be calculated."
              << std::endl;
    return 2;
  }

  std::cout << sign_changes << std::endl;

  return 0;
}
