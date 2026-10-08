#include <iostream>

int main()
{
  const int divisor = 2;
  const int err_short = 2;

  int value = 0;
  int total = 0;

  int max_val = 0;
  int max_count = 0;

  int current_even = 0;
  int max_even = 0;

  while (std::cin >> value && value != 0)
  {
    if (total == 0 || value > max_val)
    {
      max_val = value;
      max_count = 1;
    }
    else if (value == max_val)
    {
      max_count++;
    }

    if (value % divisor == 0)
    {
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

    total++;
  }

  if (!std::cin)
  {
    std::cerr << "Не является последовательностью\n";
    return 1;
  }

  std::cout << max_even << "\n";

  if (total == 0)
  {
    std::cerr << "Последовательность слишком короткая\n";
    return err_short;
  }

  std::cout << max_count << "\n";
  return 0;
}
