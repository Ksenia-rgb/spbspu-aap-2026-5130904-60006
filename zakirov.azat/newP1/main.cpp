#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace zakirov
{
  const int input_error = 1;
  const int calculation_error = 2;

  class CountMin
  {
  public:
    CountMin(): smallest_(0), count_(0), overflow_(false) {}

    void operator()(int number)
    {
      if (count_ == 0 || number < smallest_)
      {
        smallest_ = number;
        count_ = 1;
        overflow_ = false;
      }
      else if (number == smallest_)
      {
        if (count_ == std::numeric_limits< std::size_t >::max())
        {
          overflow_ = true;
        }
        else
        {
          ++count_;
        }
      }
    }

    std::size_t operator()() const
    {
      if (overflow_)
      {
        throw std::overflow_error("16: переполнение");
      }
      return count_;
    }

  private:
    int smallest_;
    std::size_t count_;
    bool overflow_;
  };

  class CountDiv
  {
  public:
    CountDiv(): last_(0), count_(0), first_(true), enough_(false), overflow_(false) {}

    void operator()(int number)
    {
      if (first_)
      {
        first_ = false;
      }
      else
      {
        enough_ = true;
        if (last_ == -1 || number % last_ == 0)
        {
          if (count_ == std::numeric_limits< std::size_t >::max())
          {
            overflow_ = true;
          }
          else
          {
            ++count_;
          }
        }
      }
      last_ = number;
    }

    std::size_t operator()() const
    {
      if (!enough_)
      {
        throw std::logic_error("11: мало чисел");
      }
      if (overflow_)
      {
        throw std::overflow_error("11: переполнение");
      }
      return count_;
    }

  private:
    int last_;
    std::size_t count_;
    bool first_;
    bool enough_;
    bool overflow_;
  };

  int process(std::istream &in, std::ostream &out, std::ostream &err)
  {
    CountMin minimums;
    CountDiv divs;
    int number = 0;
    while (in >> number && number != 0)
    {
      minimums(number);
      divs(number);
    }
    if (!in)
    {
      err << "Ошибка ввода\n";
      return input_error;
    }

    int result = 0;
    try
    {
      out << minimums() << '\n';
    }
    catch (const std::exception &error)
    {
      err << error.what() << '\n';
      result = calculation_error;
    }
    try
    {
      out << divs() << '\n';
    }
    catch (const std::exception &error)
    {
      err << error.what() << '\n';
      result = calculation_error;
    }
    return result;
  }
}

int main()
{
  return zakirov::process(std::cin, std::cout, std::cerr);
}
