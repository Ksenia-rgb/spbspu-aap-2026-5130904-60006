#include <iostream>
#include <limits>

namespace aleshin
{
  const int ok = 0;
  const int bad_input = 1;
  const int no_result = 2;
  const unsigned long long limit = std::numeric_limits< unsigned long long >::max();

  class CounterMax
  {
  public:
    void nextN(const int n) noexcept
    {
      if (empty_ || n > max_num_) {
        max_num_ = n;
        count_ = 1;
        overflow_ = false;
        empty_ = false;
      } else if (n == max_num_) {
        if (count_ == limit) {
          overflow_ = true;
        } else {
          ++count_;
        }
      }
    }

    bool print(std::ostream &out, std::ostream &err) const
    {
      if (empty_ || overflow_) {
        err << "Error: невозможно рассчитать CNT-MAX\n";
        return false;
      }
      out << count_ << '\n';
      return true;
    }

  private:
    bool empty_ = true;
    bool overflow_ = false;
    int max_num_ = 0;
    unsigned long long count_ = 0;
  };

  class CounterEqlSeq
  {
  public:
    void nextN(const int n) noexcept
    {
      if (!empty_ && n == prev_) {
        if (cur_run_ == limit) {
          overflow_ = true;
        } else {
          ++cur_run_;
        }
      } else {
        prev_ = n;
        cur_run_ = 1;
      }
      if (cur_run_ > best_run_) {
        best_run_ = cur_run_;
      }
      empty_ = false;
    }

    bool print(std::ostream &out, std::ostream &err) const
    {
      if (overflow_) {
        err << "Error: невозможно рассчитать EQL-SEQ\n";
        return false;
      }
      out << best_run_ << '\n';
      return true;
    }

  private:
    bool empty_ = true;
    bool overflow_ = false;
    int prev_ = 0;
    unsigned long long cur_run_ = 0;
    unsigned long long best_run_ = 0;
  };

  int process(std::istream &in, std::ostream &out, std::ostream &err)
  {
    CounterMax cnt_max;
    CounterEqlSeq eql_seq;

    int n = 0;
    bool got_zero = false;
    while (in >> n) {
      if (n == 0) {
        got_zero = true;
        break;
      }
      cnt_max.nextN(n);
      eql_seq.nextN(n);
    }
    if (!got_zero) {
      err << "Error: это не последовательность\n";
      return bad_input;
    }

    const bool r1 = cnt_max.print(out, err);
    const bool r2 = eql_seq.print(out, err);
    return (r1 && r2) ? ok : no_result;
  }
}

int main()
{
  return aleshin::process(std::cin, std::cout, std::cerr);
}
