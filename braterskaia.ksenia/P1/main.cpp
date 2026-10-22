#include <iostream>
#include <cstddef>
#include <limits>

const int ERR_INPUT = 1;

int main()
{
  std::size_t inc_cnt = 0;
  std::size_t max_inc = 1;
  std::size_t cur_inc = 1;

  int prev = 0;
  int curr = 0;
  bool is_first = true;

  while (std::cin >> curr)
  {
    if (curr == 0)
    {
      break;
    }

    if (is_first)
    {
      prev = curr;
      is_first = false;
      continue;
    }

    if (curr > prev)
    {
      if (inc_cnt ==
          std::numeric_limits<std::size_t>::max())
      {
        return ERR_INPUT;
      }

      if (cur_inc ==
          std::numeric_limits<std::size_t>::max())
      {
        return ERR_INPUT;
      }

      ++inc_cnt;
      ++cur_inc;

      if (cur_inc > max_inc)
      {
        max_inc = cur_inc;
      }
    }
    else
    {
      cur_inc = 1;
    }

    prev = curr;
  }

  if (!std::cin && !std::cin.eof())
  {
    return ERR_INPUT;
  }

  if (is_first)
  {
    return ERR_INPUT;
  }

  std::cout << max_inc << '\n';
  std::cout << inc_cnt << '\n';

  return 0;
}
