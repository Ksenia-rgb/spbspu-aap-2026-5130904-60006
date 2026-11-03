#include <iostream>
#include <cstddef>

namespace chizhova
{
  int run()
  {
    std::size_t maxLen = 0;
    std::size_t currLen = 0;
    bool isFirst = true;
    int prev = 0;
    std::size_t countGrtLss = 0;
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int state = 0;
    int x = 0;

    while (std::cin >> x)
    {
      if (x == 0)
      {
        break;
      }

      if (isFirst)
      {
        prev = x;
        currLen = 1;
        maxLen = 1;
        isFirst = false;
      }
      else
      {
        if (x >= prev)
        {
          ++currLen;
        }
        else
        {
          currLen = 1;
        }
        if (currLen > maxLen)
        {
          maxLen = currLen;
        }
        prev = x;
      }

      if (state == 0)
      {
        p1 = x;
        state = 1;
      }
      else if (state == 1)
      {
        p2 = x;
        state = 2;
      }
      else
      {
        p3 = x;
        if (p1 > p2 && p2 > p3)
        {
          ++countGrtLss;
        }
        p1 = p2;
        p2 = p3;
      }
    }

    if (std::cin.bad() || (std::cin.fail() && !std::cin.eof()))
    {
      std::cerr << "Unexpected input\n";
      return 1;
    }

    std::cout << maxLen << "\n";
    std::cout << countGrtLss << "\n";
    return 0;
  }
}

int main()
{
  return chizhova::run();
}
