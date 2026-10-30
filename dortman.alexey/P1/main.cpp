#include <iostream>
#include <limits>

namespace dortman
{
  const int err_args = 1;
  const int err_calc = 2;
  const int even_divisor = 2;

  struct CntMax
  {
    CntMax():
      count(0),
      max_value(0),
      is_empty(true),
      has_overflow(false)
    {}

    void operator()(int value)
    {
      if (is_empty)
      {
        max_value = value;
        count = 1;
        is_empty = false;
      }
      else if (value > max_value)
      {
        max_value = value;
        count = 1;
        has_overflow = false;
      }
      else if (value == max_value)
      {
        if (count == std::numeric_limits< size_t >::max())
        {
          has_overflow = true;
        }
        else
        {
          ++count;
        }
      }
    }

    bool hasError() const
    {
      return is_empty || has_overflow;
    }

    bool isOverflow() const
    {
      return has_overflow;
    }

    size_t getResult() const
    {
      return count;
    }

  private:
    size_t count;
    int max_value;
    bool is_empty;
    bool has_overflow;
  };

  struct EvnCnt
  {
    EvnCnt():
      max_count(0),
      current_count(0),
      has_overflow(false)
    {}

    void operator()(int value)
    {
      if (has_overflow)
      {
        return;
      }

      if (value % even_divisor == 0)
      {
        if (current_count == std::numeric_limits< size_t >::max())
        {
          has_overflow = true;
          return;
        }
        ++current_count;
        if (current_count > max_count)
        {
          max_count = current_count;
        }
      }
      else
      {
        current_count = 0;
      }
    }

    bool hasError() const
    {
      return has_overflow;
    }

    size_t getResult() const
    {
      return max_count;
    }

  private:
    size_t max_count;
    size_t current_count;
    bool has_overflow;
  };
}

int main()
{
  dortman::CntMax cnt_max;
  dortman::EvnCnt evn_cnt;

  int value = 0;
  while (std::cin >> value && value != 0)
  {
    cnt_max(value);
    evn_cnt(value);
  }

  if (!std::cin)
  {
    std::cerr << "Входные данные не являются последовательностью целых чисел\n";
    return dortman::err_args;
  }

  bool has_calc_error = false;

  if (cnt_max.hasError())
  {
    has_calc_error = true;
    if (cnt_max.isOverflow())
    {
      std::cerr << "Переполнение счетчика максимальных элементов\n";
    }
    else
    {
      std::cerr << "Последовательность слишком короткая\n";
    }
  }
  else
  {
    std::cout << cnt_max.getResult() << "\n";
  }

  if (evn_cnt.hasError())
  {
    has_calc_error = true;
    std::cerr << "Переполнение счетчика четных элементов\n";
  }
  else
  {
    std::cout << evn_cnt.getResult() << "\n";
  }

  if (has_calc_error)
  {
    return dortman::err_calc;
  }

  return 0;
}
