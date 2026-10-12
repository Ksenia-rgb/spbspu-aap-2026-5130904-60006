#include <iostream>

namespace zorin
{
  constexpr int min_size_for_grt_lss = 2;
  constexpr int min_size_for_div_rem = 2;
  constexpr int err_invalid_input = 1;
  constexpr int err_too_short = 2;

  bool isDivisible(int a, int b)
  {
    return a % b == 0;
  }
}

int main()
{
  int prev_prev = 0;
  int prev = 0;
  int count = 0;
  int grt_lss_count = 0;
  int div_rem_count = 0;
  bool finished = false;
  int value = 0;

  while (std::cin >> value)
  {
    if (value == 0)
    {
      finished = true;
      break;
    }

    if (count >= zorin::min_size_for_grt_lss && prev_prev > prev && prev > value)
    {
      ++grt_lss_count;
    }

    if (count >= 1 && zorin::isDivisible(value, prev))
    {
      ++div_rem_count;
    }

    prev_prev = prev;
    prev = value;
    ++count;
  }

  if (!finished)
  {
    std::cerr << "Error: invalid sequence\n";
    return zorin::err_invalid_input;
  }

  std::cout << grt_lss_count << "\n";

  if (count < zorin::min_size_for_div_rem)
  {
    std::cerr << "Error: too short for DIV-REM\n";
    return zorin::err_too_short;
  }

  std::cout << div_rem_count << "\n";
  return 0;
}
