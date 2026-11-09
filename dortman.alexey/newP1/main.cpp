#include <iostream>
#include <limits>
#include <cstddef>

namespace dortman {
  const int not_a_sequence = 1;
  const int invalid_data = 2;

  class SequenceCounter {
  public:
    SequenceCounter():
      has_elements_(false),
      max_val_(0),
      max_count_(0),
      overflow_max_count_(false),
      current_even_(0),
      max_even_(0),
      overflow_even_(false)
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

      has_elements_ = true;
    }

    int print(std::ostream & out, std::ostream & err) const
    {
      bool has_error = false;

      if (overflow_even_) {
        has_error = true;
        err << "Переполнение счетчика четных элементов\n";
      } else {
        out << max_even_ << "\n";
      }

      if (!has_elements_) {
        has_error = true;
        err << "Последовательность слишком короткая\n";
      } else if (overflow_max_count_) {
        has_error = true;
        err << "Переполнение счетчика максимальных элементов\n";
      } else {
        out << max_count_ << "\n";
      }

      if (has_error) {
        return invalid_data;
      }

      return 0;
    }

  private:
    bool has_elements_;
    int max_val_;
    size_t max_count_;
    bool overflow_max_count_;
    size_t current_even_;
    size_t max_even_;
    bool overflow_even_;
  };

  int process(std::istream & in, std::ostream & out, std::ostream & err)
  {
    SequenceCounter counter;
    int value = 0;

    while (in >> value && value != 0) {
      counter.nextN(value);
    }

    if (!in) {
      err << "Не является последовательностью\n";
      return not_a_sequence;
    }

    return counter.print(out, err);
  }
}

int main()
{
  return dortman::process(std::cin, std::cout, std::cerr);
}
