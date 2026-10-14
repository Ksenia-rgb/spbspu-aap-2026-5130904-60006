#include <iostream>
#include <cstddef>
#include <stdexcept>

namespace podvalnyj
{
  bool proverka(int & number)
  {
    std::cin >> number;
    return !std::cin.fail();
  }

  bool proverkaPosleNulya()
  {
    char symbol = 0;
    std::cin >> symbol;
    return std::cin.eof();
  }

  bool localMax(int left, int middle, int right)
  {
    return middle > left && middle > right;
  }

  void updateAfterMax(int tekuchiy, int & maximum, std::size_t & after_max_count, bool first)
  {
    if (first || tekuchiy > maximum)
    {
      maximum = tekuchiy;
      after_max_count = 0;
    }
    else
    {
      ++after_max_count;
    }
  }

  bool process(std::size_t & count, std::size_t & local_max_count, std::size_t & after_max_count)
  {
    int tekuchiy = 0;
    int pred = 0;
    int before_pred = 0;
    int maximum = 0;

    while (proverka(tekuchiy) && tekuchiy != 0)
    {
      if (count >= 2 && localMax(before_pred, pred, tekuchiy))
      {
        ++local_max_count;
      }
      updateAfterMax(tekuchiy, maximum, after_max_count, count == 0);
      before_pred = pred;
      pred = tekuchiy;
      ++count;
    }
    if (std::cin.fail())
    {
      return false;
    }
    return proverkaPosleNulya();
  }

  std::size_t getResult(std::size_t count, std::size_t result)
  {
    if (count == 0)
    {
      throw std::logic_error("empty sequence");
    }
    return result;
  }

  int printResult(const char * name, std::size_t count, std::size_t result)
  {
    try
    {
      std::cout << getResult(count, result) << "\n";
    }
    catch (const std::logic_error & e)
    {
      std::cerr << name << " error: " << e.what() << "\n";
      return 2;
    }
    return 0;
  }
}

int main()
{
  std::size_t count = 0;
  std::size_t local_max_count = 0;
  std::size_t after_max_count = 0;

  if (!podvalnyj::process(count, local_max_count, after_max_count))
  {
    std::cerr << "Error: invalid sequence\n";
    return 1;
  }

  const int local_result = podvalnyj::printResult("LOC-MAX", count, local_max_count);
  const int after_result = podvalnyj::printResult("AFT-MAX", count, after_max_count);

  if (local_result != 0 || after_result != 0)
  {
    return 2;
  }
  return 0;
}
