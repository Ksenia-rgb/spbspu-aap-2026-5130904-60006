
#include <iostream>
#include <limits>
 
namespace batyushov
{
  const int inputError = 1;
  const int shortError = 2;
  const int overflowError = 3;
 
  int run()
  {
    int number = 0;
    int prev = 0;
    int prev_prev = 0;
    int count = 0;
 
    long long cur_dec = 0;
    long long max_dec = 0;
    long long loc_max = 0;
 
    const long long max_ll = std::numeric_limits< long long >::max();
 
    while (std::cin >> number && number != 0)
    {
      if (count > 0 && number <= prev)
      {
        if (cur_dec == max_ll)
        {
          std::cerr << "Ошибка: переполнение счётчика убывающей подпоследовательности\n";
          return batyushov::overflowError;
        }
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
        if (loc_max == max_ll)
        {
          std::cerr << "Ошибка: переполнение счётчика локальных максимумов\n";
          return batyushov::overflowError;
        }
        loc_max++;
      }
 
      prev_prev = prev;
      prev = number;
      if (count < 2)
      {
        count++;
      }
    }
 
    if (!std::cin)
    {
      std::cerr << "Ошибка: ввод не является последовательностью целых чисел\n";
      return batyushov::inputError;
    }
 
    std::cout << max_dec << '\n';
 
    if (count == 0)
    {
      std::cerr << "Ошибка: последовательность слишком короткая\n";
      return batyushov::shortError;
    }
 
    std::cout << loc_max << '\n';
    return 0;
  }
}
 
int main()
{
  return batyushov::run();
}
 