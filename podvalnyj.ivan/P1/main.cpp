#include <cstddef>
#include <iostream>
#include <limits>

namespace podvalnyj {
  const int ERROR_SEQUENCE = 1;
  const int ERROR_CHARACTERISTIC = 2;

  void increment(std::size_t & counter, bool & overflow)
  {
    if (counter == std::numeric_limits< std::size_t >::max()) {
      overflow = true;
    } else {
      ++counter;
    }
  }

  class LocMax {
  public:
    void next(int number)
    {
      if (count_ == 2 && current_ > previous_ && current_ > number) {
        increment(result_, overflow_);
      }
      previous_ = current_;
      current_ = number;
      if (count_ < 2) {
        ++count_;
      }
    }

    int print(std::ostream & output, std::ostream & error) const
    {
      if (count_ == 0) {
        error << "LOC-MAX error: empty sequence\n";
        return ERROR_CHARACTERISTIC;
      }
      if (overflow_) {
        error << "LOC-MAX error: too many elements\n";
        return ERROR_CHARACTERISTIC;
      }
      output << result_ << "\n";
      return 0;
    }

  private:
    std::size_t count_ = 0;
    std::size_t result_ = 0;
    int previous_ = 0;
    int current_ = 0;
    bool overflow_ = false;
  };

  class AftMax {
  public:
    void next(int number)
    {
      if (empty_ || number > maximum_) {
        empty_ = false;
        maximum_ = number;
        result_ = 0;
        overflow_ = false;
      } else {
        increment(result_, overflow_);
      }
    }

    int print(std::ostream & output, std::ostream & error) const
    {
      if (empty_) {
        error << "AFT-MAX error: empty sequence\n";
        return ERROR_CHARACTERISTIC;
      }
      if (overflow_) {
        error << "AFT-MAX error: too many elements\n";
        return ERROR_CHARACTERISTIC;
      }
      output << result_ << "\n";
      return 0;
    }

  private:
    std::size_t result_ = 0;
    int maximum_ = 0;
    bool empty_ = true;
    bool overflow_ = false;
  };

  int process(std::istream & input, std::ostream & output, std::ostream & error)
  {
    LocMax loc_max;
    AftMax aft_max;
    int number = 0;
    input >> number;
    while (!input.fail() && number != 0) {
      loc_max.next(number);
      aft_max.next(number);
      input >> number;
    }
    if (input.fail()) {
      error << "Error: invalid sequence\n";
      return ERROR_SEQUENCE;
    }
    char symbol = 0;
    input >> symbol;
    if (!input.eof()) {
      error << "Error: invalid sequence\n";
      return ERROR_SEQUENCE;
    }
    const int loc_result = loc_max.print(output, error);
    const int aft_result = aft_max.print(output, error);
    if (loc_result != 0 || aft_result != 0) {
      return ERROR_CHARACTERISTIC;
    }
    return 0;
  }
}

int main()
{
  return podvalnyj::process(std::cin, std::cout, std::cerr);
}
