#include <cstddef>
#include <iostream>

class SequenceAnalyzer {
private:
    int prev_ = 0;
    std::size_t count_elements_ = 0;
    std::size_t inc_count_ = 0; 
    std::size_t div_count_ = 0; 

public:
    void next_n(const int n) noexcept {
        if (count_elements_ > 0) {
            if (n > prev_) {
                ++inc_count_;
            }

            if (prev_ != 0 && (n % prev_ == 0)) {
                ++div_count_;
            }
        }
        prev_ = n;
        ++count_elements_;
    }

    int print(std::ostream &out, std::ostream &err) const noexcept {
        out << "[INC-SEQ] Output: " << inc_count_ << '\n';

        if (count_elements_ < 2) {
            err << "[DIV-REM] Error: Sequence must contain at least 2 elements\n";
            return 2;
        }

        out << "[DIV-REM] Output: " << div_count_ << '\n';
        return 0;
    }
};

int process(std::istream &in, std::ostream &out, std::ostream &err) {
    SequenceAnalyzer analyzer;
    int n = 0;

    while (in >> n && n != 0) {
        analyzer.next_n(n);
    }

    if (!in) {
        err << "invalid input\n";
        return 1;
    }

    return analyzer.print(out, err);
}

int main() {
    return process(std::cin, std::cout, std::cerr);
}
