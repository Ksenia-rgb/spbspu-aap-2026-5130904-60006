#include <iostream>

int main()
{
  int value = 0;
  int total = 0;

  int max_val = 0;
  int max_count = 0;

  int current_even_count = 0;
  int max_even_count = 0;

  while (true)
  {
    if (!(std::cin >> value))
    {
      std::cerr << "Не является последовательностью\n";
      return 1;
    }

    if (value == 0)
    {
      break;
    }

    if (total == 0 || value > max_val)
    {
      max_val = value;
      max_count = 1;
    }
    else if (value == max_val)
    {
      max_count++;
    }

    if (value % 2 == 0)
    {
      current_even_count++;
      if (current_even_count > max_even_count)
      {
        max_even_count = current_even_count;
      }
    }
    else
    {
      current_even_count = 0;
    }

    total++;
  }

  std::cout << max_even_count << "\n";

  if (total == 0)
  {
    std::cerr << "Последовательность слишком короткая для варианта 3\n";
    return 2;
  }

  std::cout << max_count << "\n";
  return 0;
}
