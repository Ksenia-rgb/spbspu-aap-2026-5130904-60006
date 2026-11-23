#include <iostream>
#include <limits>

const int INVALID_INPUT_ERROR = 1;
const int OVERFLOW_ERROR = 2;
const int UNSUITABLE_DATA_ERROR = 2;

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
  if (!(std::cin >> a))
  {
    std::cerr << "invalid input" << std::endl;
    return INVALID_INPUT_ERROR;
  }
  else if (a == 0)
  {
    std::cout << 0 << std::endl;
    std::cerr << "too short" << std::endl;
    return UNSUITABLE_DATA_ERROR;
  }
  int max = a;
  int pre_last = a;
  while (std::cin >> a)
  {
    if (a == 0)
    {
      break;
    }
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
  if (!(std::cin))
  {
    std::cerr << "invalid input" << std::endl;
    return INVALID_INPUT_ERROR;
  }
  if (answer_1_overflow)
  {
    std::cerr << "overflow" << std::endl;
  }
  else
  {
    std::cout << answer_1 << std::endl;
  }
  if (answer_2_overflow)
  {
    std::cerr << "overflow" << std::endl;
  }
  else
  {
    std::cout << answer_2 << std::endl;
  }
  if (answer_1_overflow || answer_2_overflow)
  {
    return OVERFLOW_ERROR;
  }
  else
  {
    return 0;
  }
}
