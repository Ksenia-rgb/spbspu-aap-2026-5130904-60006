#include <iostream>
#include <limits>

const int INVALID_DATA = 1;
const int INVALID_ARGUMENTS = 2;

const unsigned long long ull = std::numeric_limits< unsigned long long >::max();

void problem_a(int &n, int &max, unsigned long long &a_count, bool &isOverFlowA) {
  if (n > max) {
    max = n;
    a_count = 0;
  } else {
    if (a_count == ull) {
      isOverFlowA = true;
      return;
    }
    a_count++;
  }
}

void problem_b(unsigned long long &count, int &cur, int &n, unsigned long long &b_count, int &b_max,
               bool &isOverFlowB) {
  if (count == 0) {
    cur = n;
    b_count = b_max = 1;
  } else {
    if (n >= cur) {
      if (b_count == ull) {
        isOverFlowB = true;
        return;
      }
      b_count++;
    } else {
      b_count = 1;
    }
    b_max = b_max < b_count ? b_count : b_max;
    cur = n;
  }
}

int main()
{
  int max = std::numeric_limits< int >::min();

  unsigned long long count = 0, a_count = 0, b_count = 0;
  int b_max = 0, n = 0, cur = 0;
  bool isOverFlowA = false, isOverFlowB = false, isOverFlow = false;

  while (std::cin >> n) {
    if (n == 0) {
      break;
    }
    if (count == ull) {
      isOverFlow = true;
      break;
    }
    count++;

    problem_b(count, cur, n, b_count, b_max, isOverFlowB);

    problem_a(n, max, a_count, isOverFlowA);
    
    if (isOverFlowA == true || isOverFlowB == true) {
      break;
    }
  }

  if (std::cin.fail()) {
    std::cerr << "Expects error output (return code 1)";
    return INVALID_DATA;
  }

  if (isOverFlow || isOverFlowA && isOverFlowB) {
    std::cerr << "Expects error output (return code 2)";
    return INVALID_ARGUMENTS;
  }

  if (n == 0) {
    if (count == 0) {
      std::cout << a_count << "\n";
      std::cerr << "Expects error output (return code 2)";
      return INVALID_ARGUMENTS;
    }
    if (isOverFlowA) {
      std::cout << b_max << "\n";
      std::cerr << "Expects error output (return code 2)";
      return 2;
    }
    if (isOverFlowB) {
      std::cout << a_count << "\n";
      std::cerr << "Expects error output (return code 2)";
      return 2;
    }
    std::cout << a_count << "\n";
    std::cout << b_max << "\n";
    return 0;
  }
}
