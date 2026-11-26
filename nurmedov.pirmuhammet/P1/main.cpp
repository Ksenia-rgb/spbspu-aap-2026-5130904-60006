#include <iostream>
#include <cstddef>

namespace nurmedov
{
  // [MON-DEC] Longest monotonically decreasing (non-increasing) fragment
  class MonDecCounter
  {
  public:
    MonDecCounter():
      current_(0),
      max_(0),
      prev_(0)
    {}

    void operator()(int value)
    {
      if (current_ != 0 && value <= prev_)
      {
        ++current_;
      }
      else
      {
        current_ = 1;
      }
      prev_ = value;
      if (current_ > max_)
      {
        max_ = current_;
      }
    }

    size_t operator()() const
    {
      return max_;
    }

  private:
    size_t current_;
    size_t max_;
    int prev_;
  };

  // [EVN-CNT] Maximum number of consecutive even elements
  class EvenCounter
  {
  public:
    EvenCounter():
      current_(0),
      max_(0)
    {}

    void operator()(int value)
    {
      if (value % 2 == 0)
      {
        ++current_;
        if (current_ > max_)
        {
          max_ = current_;
        }
      }
      else
      {
        current_ = 0;
      }
    }

    size_t operator()() const
    {
      return max_;
    }

  private:
    size_t current_;
    size_t max_;
  };
}

int main()
{
  nurmedov::MonDecCounter mon_dec;
  nurmedov::EvenCounter even_cnt;

  int value = 0;
  while (std::cin >> value && value != 0)
  {
    mon_dec(value);
    even_cnt(value);
  }

  if (!std::cin)
  {
    std::cerr << "Error: input is not a sequence\n";
    return 1;
  }

  std::cout << mon_dec() << '\n';
  std::cout << even_cnt() << '\n';
  return 0;
}
