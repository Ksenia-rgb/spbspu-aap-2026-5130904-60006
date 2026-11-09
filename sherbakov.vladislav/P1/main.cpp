#include <iostream>
#include <cstddef>
#include <limits>

const int ERR_INPUT = 1;
const int ERR_PARTIAL = 2;
const int ERR_OVERFLOW = 4;

class SequenceAnalyzer
{
public:
  void next_n(const int x)
  {
    if (overflow)
    {
      return;
    }

    if (!hmax)
    {
      maxv = x;
      hmax = true;
    }
    else if (x > maxv)
    {
      secondmax = maxv;
      hsecondmax = true;
      maxv = x;
    }
    else if (x == maxv)
    {
      secondmax = maxv;
      hsecondmax = true;
    }
    else if (!hsecondmax || x > secondmax)
    {
      secondmax = x;
      hsecondmax = true;
    }

    if (n >= 2 && prev1 > prev2 && prev1 > x)
    {
      if (count_loc_max == std::numeric_limits< std::size_t >::max())
      {
        overflow = true;
        return;
      }
      ++count_loc_max;
    }

    prev2 = prev1;
    prev1 = x;

    if (n == std::numeric_limits< std::size_t >::max())
    {
      overflow = true;
      return;
    }
    ++n;
  }

  int print(std::ostream &out, std::ostream &err) const
  {
    if (overflow)
    {
      err << "error: counter overflow\n";
      return ERR_OVERFLOW;
    }

    int retcode = 0;

    if (hsecondmax)
    {
      out << "SUB-MAX: " << secondmax << '\n';
    }
    else
    {
      err << "error: cannot calculate SUB-MAX: sequence is too short\n";
      retcode = ERR_PARTIAL;
    }

    if (n > 0)
    {
      out << "LOG-MAX: " << count_loc_max << '\n';
    }
    else
    {
      err << "error: cannot calculate LOG-MAX: sequence is too short\n";
      retcode = ERR_PARTIAL;
    }

    return retcode;
  }
private:
  int maxv = 0;
  int secondmax = 0;
  bool hmax = false;
  bool hsecondmax = false;

  std::size_t count_loc_max = 0;
  int prev2 = 0;
  int prev1 = 0;
  std::size_t n = 0;

  bool overflow = false;
};

int process(std::istream &in, std::ostream &out, std::ostream &err)
{
  SequenceAnalyzer analyzer;
  int x = 0;
  bool term = false;

  while (in >> x)
  {
    if (x == 0)
    {
      term = true;
      break;
    }
    analyzer.next_n(x);
  }

  if (!term)
  {
    if (in.eof())
    {
      err << "error: The sequence is not terminated with a zero\n";
    }
    else
    {
      err << "error The input data is not a sequence of integers\n";
    }
    return ERR_INPUT;
  }

  return analyzer.print(out, err);
}

int main()
{
  return process(std::cin, std::cout, std::cerr);
}
