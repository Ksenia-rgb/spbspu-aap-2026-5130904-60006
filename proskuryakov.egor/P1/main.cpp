<<<<<<< HEAD
#include <cstddef>
#include <iostream>
#include <limits>

namespace proskuryakov {
  const int err_invalid_data = 1;
  const int err_sequence_small = 2;

  class CounterSequence {
  public:
    void nextN(const int n) noexcept
    {
      if (total_count_ < 2) {
        total_count_ += 1;
      }

      if (total_count_ == 1 || n > max_) {
        max_ = n;
        count_max_ = 1;
        overflow_max_ = false;
      } else if (n == max_) {
        if (count_max_ == std::numeric_limits< std::size_t >::max()) {
          overflow_max_ = true;
        }
        count_max_ += 1;
      }

      if (total_count_ == 1 || n < min_) {
        min_ = n;
        count_min_ = 1;
        overflow_min_ = false;
      } else if (n == min_) {
        if (count_min_ == std::numeric_limits< std::size_t >::max()) {
          overflow_min_ = true;
        }
        count_min_ += 1;
      }
    }

    int print(std::ostream& out, std::ostream& err) const noexcept
    {
      if (total_count_ == 0) {
        err << "Sequence is small!\n";
        return err_sequence_small;
      }

      int result = 0;

      if (overflow_max_) {
        err << "Overflow error!\n";
        result = err_invalid_data;
      } else {
        out << count_max_ << '\n';
      }

      if (overflow_min_) {
        err << "Overflow error!\n";
        result = err_invalid_data;
      } else {
        out << count_min_ << '\n';
      }
      return result;
    }

  private:
    std::size_t total_count_ = 0;
    std::size_t count_max_ = 0;
    std::size_t count_min_ = 0;
    bool overflow_max_ = false;
    bool overflow_min_ = false;
    int max_ = 0;
    int min_ = 0;
  };

  int process(std::istream& in, std::ostream& out, std::ostream& err)
  {
    CounterSequence counter;
    int n = 0;
    while (in >> n && n != 0) {
      counter.nextN(n);
    }

    if (!in) {
      err << "Invalid input!\n";
      return err_invalid_data;
    }
    return counter.print(out, err);
  }
=======
#include <iostream>
#include <limits>
#include <cstddef>

namespace proskuryakov
{
  const int err_invalid_data = 1;
  const int err_sequence_small = 2;
>>>>>>> master
}

int main()
{
<<<<<<< HEAD
  return proskuryakov::process(std::cin, std::cout, std::cerr);
=======
  int value = 0;
  size_t total_count = 0;
  size_t count_max = 0;
  size_t count_min = 0;
  bool overflow_max = false;
  bool overflow_min = false;
  int max = 0;
  int min = 0;
  while (std::cin >> value)
  {
    if (value == 0)
    {
      break;
    }
    if (total_count < 2)
    {
      total_count += 1;
    }

    if (total_count == 1 || value > max)
    {
      max = value;
      count_max = 1;
      overflow_max = false;
    }
    else if (value == max)
    {
      if (count_max == std::numeric_limits< size_t >::max())
      {
        overflow_max = true;
      }
      count_max += 1;
    }

    if (total_count == 1 || value < min)
    {
      min = value;
      count_min = 1;
      overflow_min = false;
    }
    else if (value == min)
    {
      if (count_min == std::numeric_limits< size_t >::max())
      {
        overflow_min = true;
      }
      count_min += 1;
    }
  }

  if (!std::cin)
  {
    std::cerr << "Invalid input!\n";
    return proskuryakov::err_invalid_data;
  }

  if (total_count == 0)
  {
    std::cerr << "Sequence is small!\n";
    return proskuryakov::err_sequence_small;
  }

  int result = 0;

  if (overflow_max)
  {
    std::cerr << "Overflow error!\n";
    result = proskuryakov::err_invalid_data;
  }
  else
  {
    std::cout << count_max << '\n';
  }

  if (overflow_min)
  {
    std::cerr << "Overflow error!\n";
    result = proskuryakov::err_invalid_data;
  }
  else
  {
    std::cout << count_min << '\n';
  }

  return result;
>>>>>>> master
}
