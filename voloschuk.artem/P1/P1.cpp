#include <iostream>
#include <limits>

int main()
{
  const unsigned max_u = std::numeric_limits< unsigned >::max();
  unsigned answer_1 = 0;
  unsigned answer_2 = 0;
  bool answer_1_overflow = false;
  bool answer_2_overflow = false;
  int last = 1;
  bool flag = true;
  int a = 0;
  std::cin >> a;
  if (std::cin.fail())
  {
    std::cerr << "invalid input";
    return 1;
  }
  else if (a == 0)
  {
    std::cout << 0 << std::endl;
    std::cerr << "too short";
    return 2;
  }
  int max = a;
  int pre_last = a;
  while (true)
  {
    std::cin >> a;
    if (std::cin.fail())
    {
      std::cerr << "invalid input";
      return 1;
    }
    else if (a == 0)
    {
      break;
    }
    else
    {
      if (max < a)
      {
        answer_2 = 0;
        max = a;
      }
      else
      {
        if (answer_2 == max_u)
        {
          answer_2_overflow = true;
        }
        else
        {
          answer_2++;
        }
      }
      if (flag)
      {
        flag = false;
        last = a;
      }
      else
      {
        if (pre_last > last && last > a)
        {
          if (answer_1 == max_u)
          {
            answer_1_overflow = true;
          }
          else
          {
            answer_1++;
          }
        }
        pre_last = last;
        last = a;
      }
    }
  }
  if (answer_1_overflow == true)
  {
    std::cerr << "overflow";
  }
  else
  {
    std::cout << answer_1 << "\n";
  }
  if (answer_2_overflow == true)
  {
    std::cerr << "overflow";
  }
  else
  {
    std::cout << answer_2 << "\n";
  }
  if (answer_1_overflow == true || answer_2_overflow == true)
  {
    return 2;
  }
  else
  {
    return 0;
  }
}
