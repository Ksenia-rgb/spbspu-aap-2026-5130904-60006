#include <iostream>

namespace chizhova {

int combined() {
    long long x;

    if (!(std::cin >> x)) {
        std::cerr << "Error: input is not a sequence\n";
        return 1;
    }

    if (x == 0) {
        std::cin >> std::ws;
        if (std::cin.peek() != EOF) {
            std::cerr << "Error: extra tokens after 0\n";
            return 1;
        }
        std::cout << 0 << '\n' << 0 << '\n';
        return 0;
    }

    long long prev = x;
    long long cur_len = 1;
    long long max_len = 1;
    long long count = 0;

    if (!(std::cin >> x)) {
        std::cerr << "Error: input is not a sequence\n";
        return 1;
    }

    if (x == 0) {
        std::cin >> std::ws;
        if (std::cin.peek() != EOF) {
            std::cerr << "Error: extra tokens after 0\n";
            return 1;
        }
        std::cout << count << '\n' << max_len << '\n';
        return 0;
    }

    long long curr = x;

    if (curr >= prev) {
        ++cur_len;
    } else {
        cur_len = 1;
    }
    if (cur_len > max_len) max_len = cur_len;

    while (true) {
        if (!(std::cin >> x)) {
            std::cerr << "Error: input is not a sequence\n";
            return 1;
        }
        if (x == 0) {
            break;
        }

        if (prev > curr && curr > x) {
            ++count;
        }

        if (x >= curr) {
            ++cur_len;
        } else {
            cur_len = 1;
        }
        if (cur_len > max_len) max_len = cur_len;

        prev = curr;
        curr = x;
    }

    std::cin >> std::ws;
    if (std::cin.peek() != EOF) {
        std::cerr << "Error: extra tokens after 0\n";
        return 1;
    }

    std::cout << count << '\n' << max_len << '\n';
    return 0;
}

}

int main() {
    return chizhova::combined();
} 
      
