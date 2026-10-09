#include <iostream>

int main ()
{
  int min = 0;
  int current = 0, previous = 0, next = 0;
  int count_10 = 0, count_16 = 1;
  
  std::cin >> previous;
  
  min = previous;
  if (std::cin.fail())
  {
    std::cerr << "error import\n";
    return 1;
  }

  if (previous == 0)
  {
    std::cout << " 0\n10.[GRT-LSS]  " << count_10;
    std::cout << " - элементов последовательности меньше предыдущего элемента, но больше следующего\n";
    std::cout << " 0\n16. [CNT-MIN]  " << count_16;
    std::cout << " - количество элементов последовательности равныx минимальному элементу\n";
    return 0;
  }
  
  std::cin >> current;
  if (std::cin.fail())
  {
    std::cerr << "error import\n";
    return 1;
  }
  
  if (current == 0)
  {
    std::cout << " 0\n10.[GRT-LSS]  " << count_10;
    std::cout << " - элементов последовательности меньше предыдущего элемента, но больше следующего\n";
    std::cout << " 0\n16. [CNT-MIN]  " << count_16;
    std::cout << " - количество элементов последовательности равныx минимальному элементу\n";
    return 0;
  }
  
  if (current < previous)
  {
    min = current;
  } else if (current == min) {
    count_16++;
  }

  while (std::cin >> next)
  {
    if (next == 0)
    {
      std::cout << " 0\n10.[GRT-LSS]  " << count_10;
      std::cout << " - элементов последовательности меньше предыдущего элемента, но больше следующего\n";
      std::cout << " 0\n16. [CNT-MIN]  " << count_16;
      std::cout << " - количество элементов последовательности равныx минимальному элементу\n";
      return 0;
    }
    
    if (current < previous && current > next)
    {
      count_10++;
    }

    if (next < min) 
    {
      min = next;
      count_16 = 0;
    }
    if (next == min)
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


}