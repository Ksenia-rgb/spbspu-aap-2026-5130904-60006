#include <iostream>
#include <cstddef>
#include <exception>

namespace braterskaia
{
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
  try
  {
    std::size_t cap = 10;
    std::size_t n = 0;
    int* arr = new int[cap];
    int x = 0;
    while (std::cin >> x)
    {
      if (x == 0)
      {
        break;
      }

      if (n == cap)
      {
        cap *= 2;
        int* const tmp = new int[cap];
        for (std::size_t i = 0; i < n; ++i)
        {
          tmp[i] = arr[i];
        }
        delete[] arr;
        arr = tmp;
      }

      arr[n] = x;
      ++n;
    }

    if (!std::cin && !std::cin.eof())
    {
      delete[] arr;
      return 1;
    }

    if (n == 0)
    {
      delete[] arr;
      return 2;
    }

    const std::size_t mon = braterskaia::maxMonInc(arr, n);
    const std::size_t inc = braterskaia::countInc(arr, n);

    std::cout << mon << '\n';
    std::cout << inc << '\n';

    delete[] arr;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 2;
  }
  return 0;
}
