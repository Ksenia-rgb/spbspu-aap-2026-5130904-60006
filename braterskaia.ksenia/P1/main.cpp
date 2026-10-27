#include <iostream>
#include <cstddef>

namespace braterskaia
{
  const int ERR_INPUT = 1;
  const std::size_t MAX_SZ = std::size_t(-1);

  std::size_t countInc(const int* arr, const std::size_t n)
  {
    std::size_t cnt = 0;
    for (std::size_t i = 1; i < n; ++i)
    {
      if (arr[i] > arr[i - 1])
      {
        ++cnt;
      }
    }
    return cnt;
  }

  std::size_t maxMonInc(const int* arr, const std::size_t n)
  {
    if (n == 0)
    {
      return 0;
    }

    std::size_t best = 1;
    std::size_t cur = 1;

    for (std::size_t i = 1; i < n; ++i)
    {
      if (arr[i] > arr[i - 1])
      {
        ++cur;
        if (cur > best)
        {
          best = cur;
        }
      }
      else
      {
        cur = 1;
      }
    }
    return best;
  }
}

int main()
{
  std::size_t inc_cnt = 0;
  std::size_t max_inc = 1;
  std::size_t cur_inc = 1;

  int prev = 0;
  int curr = 0;
  bool is_first = true;
  bool has_error = false;

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
      if (inc_cnt == braterskaia::MAX_SZ || cur_inc == braterskaia::MAX_SZ)
      {
        std::cerr << "Error: overflow detected\n";
        has_error = true;
      }
      else
      {
        ++inc_cnt;
        ++cur_inc;

        if (cur_inc > max_inc)
        {
          max_inc = cur_inc;
        }
      }
    }
    else
    {
      cur_inc = 1;
    }

    prev = curr;
  }

  if (!std::cin)
  {
    std::cerr << "Error: invalid input\n";
    return braterskaia::ERR_INPUT;
  }

  if (is_first)
  {
    std::cerr << "Error: empty sequence\n";
    return braterskaia::ERR_INPUT;
  }

  std::cout << max_inc << '\n';
  std::cout << inc_cnt << '\n';

  if (has_error)
  {
    return braterskaia::ERR_INPUT;
  }

  return 0;
}
