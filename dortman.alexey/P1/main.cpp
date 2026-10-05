//3 вариант
#include <iostream>

int main()
{
  int value = 0;
  int max_val = 0;
  int count = 0;
  int total = 0;

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
      count = 1;
    }
    else if (value == max_val)
    {
      count++;
    }

    total++;
  }

  if (total == 0)
  {
    std::cerr << "Последовательность слишком короткая\n";
    return 2;
  }

  std::cout << count << "\n";
  return 0;
}
