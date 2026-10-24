#include <iostream>
#include <limits>
#include <cstddef>

namespace dortman
{
  const int not_a_sequence = 1;
  const int invalid_data = 2;
}

int main()
{
  int value = 0;
  bool has_elements = false;

  int max_val = 0;
  size_t max_count = 0;

  size_t current_even = 0;
  size_t max_even = 0;

  const size_t max_limit = std::numeric_limits< size_t >::max();

  while (std::cin >> value && value != 0)
  {
    if (!has_elements || value > max_val)
    {
      max_val = value;
      max_count = 1;
    }
    else if (value == max_val)
    {
      if (max_count == max_limit)
      {
        std::cerr << "Переполнение счетчика максимальных элементов\n";
        return dortman::invalid_data;
      }
      max_count++;
    }

    if ((value & 1) == 0)
    {
      if (current_even == max_limit)
      {
        std::cerr << "Переполнение счетчика четных элементов\n";
        return dortman::invalid_data;
      }
      current_even++;
      if (current_even > max_even)
      {
        max_even = current_even;
      }
    }
    else
    {
      current_even = 0;
    }

    has_elements = true;
  }

  if (!std::cin)
  {
    std::cerr << "Не является последовательностью\n";
    return dortman::not_a_sequence;
  }

  std::cout << max_even << "\n";

  if (!has_elements)
  {
    std::cerr << "Последовательность слишком короткая\n";
    return dortman::invalid_data;
  }

  std::cout << max_count << "\n";
  return 0;
}
