#include <iostream>
#include <limits>
#include <cstddef>

const int err_invalid_data = 1;
const int err_sequence_small = 2;

int main()
{
  int value = 0;
  size_t total_count = 0;
  size_t count_max = 0;
  size_t count_min = 0;
  int max = 0;
  int min = 0;
  while (std::cin >> value)
  {
    if (value == 0)
    {
      break;
    }
    if (total_count < 2)
    {
      total_count += 1;
    }

    if (total_count == 1 || value > max)
    {
      max = value;
      count_max = 1;
    }
    else if (value == max)
    {
      if (count_max == std::numeric_limits< size_t >::max())
      {
        std::cerr << "Overflow error!\n";
        return err_invalid_data;
      }
      count_max += 1;
    }

    if (total_count == 1 || value < min)
    {
      min = value;
      count_min = 1;
    }
    else if (value == min)
    {
      if (count_min == std::numeric_limits< size_t >::max())
      {
        std::cerr << "Overflow error!\n";
        return err_invalid_data;
      }
      count_min += 1;
    }
  }

  if (!std::cin)
  {
    std::cerr << "Invalid input!\n";
    return err_invalid_data;
  }

  if (total_count == 0)
  {
    std::cerr << "Sequence is small!\n";
    return err_sequence_small;
  }

  std::cout << count_max << '\n';
  std::cout << count_min << '\n';
  return 0;
}
