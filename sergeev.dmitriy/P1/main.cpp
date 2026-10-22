#include <iostream>
#include <limits>

int main()
{
  int const ERROR_INVALID_INPUT = 1;
  int const ERROR_CALCULATION = 2;

  int min = 0;
  int current = 0, previous = 0, next = 0;
  int count_10 = 0, count_16 = 1;

  std::cin >> previous;

  min = previous;
  if (std::cin.fail())
  {
    std::cerr << "error import\n";
    return ERROR_INVALID_INPUT;
  }

  if (previous == 0)
  {
    std::cout << "0" << "\n";
    std::cout << "0" << "\n";
    return 0;
  }

  std::cin >> current;
  if (std::cin.fail())
  {
    std::cerr << "error import\n";
    return ERROR_INVALID_INPUT;
  }

  if (current == 0)
  {
    std::cout << count_10 << "\n";
    std::cout << count_16 << "\n";
    return 0;
  }

  if (current < previous)
  {
    min = current;
  }
  else if (current == min)
  {
    if (count_16 > std::numeric_limits<int>::max() - 1)
    {
      return ERROR_CALCULATION;
    }
    count_16++;
  }

  while (std::cin >> next)
  {
    if (next == 0)
    {
      break;
    }

    if (current < previous && current > next)
    {
      if (count_10 > std::numeric_limits<int>::max() - 1)
      {
        return ERROR_CALCULATION;
      }
      count_10++;
    }

    if (next < min)
    {
      min = next;
      count_16 = 1;
    }
    else if (next == min)
    {
      if (count_16 > std::numeric_limits<int>::max() - 1)
      {
        return ERROR_CALCULATION;
      }
      count_16++;
    }

    previous = current;
    current = next;
  }

  if (std::cin.fail())
  {
    std::cerr << "error import\n";
    return ERROR_INVALID_INPUT;
  }

  std::cout << count_10 << "\n";
  std::cout << count_16 << "\n";
  return 0;
}
