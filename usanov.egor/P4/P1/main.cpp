#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace usanov
{
  using Counter = unsigned long long;

  Counter increment(Counter value)
  {
    if (value == std::numeric_limits< Counter >::max())
    {
      throw std::overflow_error("Counter overflow");
    }
    return value + 1;
  }

  Counter absValue(int value)
  {
    const Counter v = static_cast< Counter >(value);
    return value < 0 ? 0ULL - v : v;
  }

  class CounterGrtLss
  {
  public:
    void next_n(int n)
    {
      if (elements_ >= 2 && previous1_ < previous2_ && previous1_ > n)
      {
        count_ = increment(count_);
      }
      previous2_ = previous1_;
      previous1_ = n;
      if (elements_ < 2)
      {
        ++elements_;
      }
    }

    Counter result() const noexcept
    {
      return count_;
    }

  private:
    int previous2_ = 0;
    int previous1_ = 0;
    std::size_t elements_ = 0;
    Counter count_ = 0;
  };

  class CounterPthTrp
  {
  public:
    void next_n(int n)
    {
      if (elements_ >= 2)
      {
        const Counter a = absValue(previous2_);
        const Counter b = absValue(previous1_);
        const Counter c = absValue(n);
        if (a * a + b * b == c * c)
        {
          count_ = increment(count_);
        }
      }
      previous2_ = previous1_;
      previous1_ = n;
      if (elements_ < 2)
      {
        ++elements_;
      }
    }

    Counter result() const noexcept
    {
      return count_;
    }

  private:
    int previous2_ = 0;
    int previous1_ = 0;
    std::size_t elements_ = 0;
    Counter count_ = 0;
  };

  class SequenceStats
  {
  public:
    void next_n(int n)
    {
      grt_.next_n(n);
      pth_.next_n(n);
    }

    void print(std::ostream & out) const
    {
      out << grt_.result() << '\n' << pth_.result() << '\n';
    }

  private:
    CounterGrtLss grt_;
    CounterPthTrp pth_;
  };

  int process(std::istream & in, std::ostream & out, std::ostream & err)
  {
    SequenceStats stats;
    int n = 0;
    try
    {
      while (in >> n && n != 0)
      {
        stats.next_n(n);
      }
    }
    catch (const std::overflow_error & e)
    {
      err << e.what() << "\n";
      return 2;
    }

    if (!in)
    {
      err << "invalid input\n";
      return 1;
    }
    in >> std::ws;
    if (!in.eof())
    {
      err << "invalid input after zero\n";
      return 1;
    }

    stats.print(out);
    return 0;
  }
}

int main()
{
  return usanov::process(std::cin, std::cout, std::cerr);
}