#include <iostream>
#include <limits>
#include <cstddef>

namespace dortman {
  const int not_a_sequence = 1;
  const int invalid_data = 2;

  class EvenChainCounter {
  public:
    EvenChainCounter():
      current_even_(0),
      max_even_(0),
      overflow_even_(false)
    {}

    void nextN(const int value)
    {
      const size_t max_limit = std::numeric_limits< size_t >::max();

      if ((value & 1) == 0) {
        if (current_even_ == max_limit) {
          overflow_even_ = true;
        } else {
          ++current_even_;
          if (current_even_ > max_even_) {
            max_even_ = current_even_;
          }
        }
      } else {
        current_even_ = 0;
      }
    }

    bool print(std::ostream & out, std::ostream & err) const
    {
      if (overflow_even_) {
        err << "Переполнение счетчика четных элементов\n";
        return false;
      }

      out << max_even_ << "\n";
      return true;
    }

  private:
    size_t current_even_;
    size_t max_even_;
    bool overflow_even_;
  };

  class MaxCountCounter {
  public:
    MaxCountCounter():
      has_elements_(false),
      max_val_(0),
      max_count_(0),
      overflow_max_count_(false)
    {}

    void nextN(const int value)
    {
      const size_t max_limit = std::numeric_limits< size_t >::max();

      if (!has_elements_ || value > max_val_) {
        max_val_ = value;
        max_count_ = 1;
        overflow_max_count_ = false;
      } else if (value == max_val_) {
        if (max_count_ == max_limit) {
          overflow_max_count_ = true;
        } else {
          ++max_count_;
        }
      }

      has_elements_ = true;
    }

    bool print(std::ostream & out, std::ostream & err) const
    {
      if (!has_elements_) {
        err << "Последовательность слишком короткая\n";
        return false;
      }

      if (overflow_max_count_) {
        err << "Переполнение счетчика максимальных элементов\n";
        return false;
      }

      out << max_count_ << "\n";
      return true;
    }

  private:
    bool has_elements_;
    int max_val_;
    size_t max_count_;
    bool overflow_max_count_;
  };

  int process(std::istream & in, std::ostream & out, std::ostream & err)
  {
    EvenChainCounter even_counter;
    MaxCountCounter max_counter;
    int value = 0;

    while (in >> value && value != 0) {
      even_counter.nextN(value);
      max_counter.nextN(value);
    }

    if (!in) {
      err << "Не является последовательностью\n";
      return not_a_sequence;
    }

    const bool even_ok = even_counter.print(out, err);
    const bool max_ok = max_counter.print(out, err);

    if (!even_ok || !max_ok) {
      return invalid_data;
    }

    return 0;
  }
}

int main()
{
  return dortman::process(std::cin, std::cout, std::cerr);
}
