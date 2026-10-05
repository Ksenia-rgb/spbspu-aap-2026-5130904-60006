#include <cstddef>
#include <iostream>

int main()
{
  const int error_invalid_input = 1;
  const int error_logic = 2;

  int value = 0;
  int max_val = 0;
  size_t count = 0;
  size_t total = 0;

  while (true)
  {
    if (!(std::cin >> value))
    {
      std::cerr << "Не является последовательностью\n";
      return error_invalid_input;
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
    std::cerr << "Последовательность слишком коротка\n";
    return error_logic;
  }

  std::cout << count << "\n";
  return 0;
}
