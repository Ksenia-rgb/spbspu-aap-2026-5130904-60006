#include <iostream>
#include <cstddef>

namespace snosnakee {

int main() {
    size_t max_len = 0;
    size_t curr_len = 0;
    bool is_first = true;
    int prev = 0;

    size_t count_grt_lss = 0;
    int p1 = 0, p2 = 0, p3 = 0;
    int state = 0;

    int x = 0;
    while (std::cin >> x) {
        if (x == 0) break;

        if (is_first) {
            prev = x;
            curr_len = 1;
            max_len = 1;
            is_first = false;
        } else {
            if (x >= prev) {
                ++curr_len;
            } else {
                curr_len = 1;
            }
            if (curr_len > max_len) max_len = curr_len;
            prev = x;
        }

        if (state == 0) {
            p1 = x;
            state = 1;
        } else if (state == 1) {
            p2 = x;
            state = 2;
        } else {
            p3 = x;
            if (p1 > p2 && p2 > p3) {
                ++count_grt_lss;
            }
            p1 = p2;
            p2 = p3;
        }
    }

    if (std::cin.bad() || std::cin.fail() || std::cin.eof()) {
        std::cerr << "Unexpected input\n";
        return 1;
    }

    std::cout << max_len << "\n";
    std::cout << count_grt_lss << "\n";
    return 0;
}

}

int main() {
    return snosnakee::main();
}
