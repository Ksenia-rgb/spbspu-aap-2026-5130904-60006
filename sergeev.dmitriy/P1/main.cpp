#include <iostream>

int main()
{
  int min = 0;
  int current = 0, previous = 0, next = 0;
  int count_10 = 0, count_16 = 1;

  int total_elements = 0;

  std::cin >> previous;

  min = previous;
  if (std::cin.fail())
  {
    std::cerr << "error import\n";
    return 1;
  }
  total_elements = 1;

  if (previous == 0)
  {
    std::cerr << 0 << "\n";
    std::cout << 0 << "\n";
    return 0;
  }

  std::cin >> current;
  if (std::cin.fail())
  {
    std::cerr << "error import\n";
    return 1;
  }

  total_elements = 2;

  if (current == 0)
  {
    std::cerr << "Error: Sequence too short for Variant 10\n";
    std::cout << count_16 << "\n";
    return 2;
  }

  if (current < previous)
  {
    min = current;
  }
  else if (current == min)
  {
    count_16++;
  }

  while (std::cin >> next)
  {
    if (next == 0)
    {
      break;
    }
    total_elements++;

    if (current < previous && current > next)
    {
      count_10++;
    }

    if (next < min)
    {
      min = next;
      count_16 = 1;
    } else if (next == min)
    {
      count_16++;
    }

    previous = current;
    current = next;
  }

  if (std::cin.fail())
  {
    std::cerr << "error import\n";
    return 1;
  }

  if (total_elements < 3)
  {
    std::cerr << "Error: Sequence too short for Variant 10\n";
    std::cout << count_16 << "\n";
    return 2;
  }

  std::cout << count_10 << "\n";
  std::cout << count_16 << "\n";
  return 0;
}
