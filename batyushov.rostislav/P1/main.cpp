#include <cctype>
#include <iostream>

namespace batyushov
{
  int run()
  {
    int number = 0;
    int prev = 0;
    int prev_prev = 0;
    long long count = 0;

    long long cur_dec = 0;
    long long max_dec = 0;
    long long loc_max = 0;

    while (true)
    {
      if (!(std::cin >> number))
      {
        std::cerr << "Ошибка: ввод не является последовательностью целых чисел\n";
        return 1;
      }

      const int next = std::cin.peek();
      if (!std::cin.eof() && !std::isspace(next))
      {
        std::cerr << "Ошибка: ввод содержит нецелое число или другие символы\n";
        return 1;
      }

      if (number == 0)
      {
        break;
      }

      if (count > 0 && number <= prev)
      {
        cur_dec++;
      }
      else
      {
        cur_dec = 1;
      }
      if (cur_dec > max_dec)
      {
        max_dec = cur_dec;
      }

      if (count >= 2 && prev > prev_prev && prev > number)
      {
        loc_max++;
      }

      prev_prev = prev;
      prev = number;
      count++;
    }

    int result = 0;

    std::cout << max_dec << '\n';

    if (count == 0)
    {
      std::cerr << "Ошибка: последовательность слишком короткая\n";
      result = 2;
    }
    else
    {
      std::cout << loc_max << '\n';
    }

    return result;
  }
}

int main()
{
  return batyushov::run();
}