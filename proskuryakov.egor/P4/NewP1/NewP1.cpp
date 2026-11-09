#include <cstddef>
#include <iostream>
#include <limits>

namespace proskuryakov {
  const int err_invalid_data = 1;
  const int err_sequence_small = 2;

  class CounterSequence {
  public:
    void NextN(const int n) noexcept
    {
      if (total_count < 2) {
        total_count += 1;
      }

      if (total_count == 1 || n > max) {
        max = n;
        count_max = 1;
        overflow_max = false;
      } else if (n == max) {
        if (count_max == std::numeric_limits< std::size_t >::max()) {
          overflow_max = true;
        }
        count_max += 1;
      }

      if (total_count == 1 || n < min) {
        min = n;
        count_min = 1;
        overflow_min = false;
      } else if (n == min) {
        if (count_min == std::numeric_limits< std::size_t >::max()) {
          overflow_min = true;
        }
        count_min += 1;
      }
    }

    int Print(std::ostream& out, std::ostream& err) const noexcept
    {
      if (total_count == 0) {
        err << "Sequence is small!\n";
        return err_sequence_small;
      }

      int result = 0;

      if (overflow_max) {
        err << "Overflow error!\n";
        result = err_invalid_data;
      } else {
        out << count_max << '\n';
      }

      if (overflow_min) {
        err << "Overflow error!\n";
        result = err_invalid_data;
      } else {
        out << count_min << '\n';
      }
      return result;
    }

  private:
    std::size_t total_count = 0;
    std::size_t count_max = 0;
    std::size_t count_min = 0;
    bool overflow_max = false;
    bool overflow_min = false;
    int max = 0;
    int min = 0;
  };

  int process(std::istream& in, std::ostream& out, std::ostream& err)
  {
    CounterSequence counter;
    int n = 0;
    while (in >> n && n != 0) {
      counter.NextN(n);
    }

    if (!in) {
      err << "Invalid input!\n";
      return err_invalid_data;
    }
    return counter.Print(out, err);
  }
}

int main()
{
  return proskuryakov::process(std::cin, std::cout, std::cerr);
}
