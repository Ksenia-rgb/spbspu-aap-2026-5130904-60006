#include <iostream>
#include <string>
#include <cctype>

namespace nurmedov { 
}

int main() {
    std::cin >> std::ws;
    if (std::cin.peek() == EOF) {
        std::cerr << "Error: Empty input.\n";
        return 1;
    }
    char c = std::cin.peek();
    if (!(std::isdigit(c) || c == '-' || c == '+')) {
        std::cerr << "Error: Input is not a sequence of integers.\n";
        return 1;
    }

    bool first_elem = true;
    long long prev = 0;
    long long curr;
    
    int max_dec = 0;
    int cur_dec = 0;
    
    int max_even = 0;
    int cur_even = 0;
    
    bool has_zero = false;

    while (std::cin >> curr) {
        if (curr == 0) {
            has_zero = true;
            break;
        }
        
        if (first_elem) {
            cur_dec = 1;
            max_dec = 1;
        } else {
            if (curr <= prev) { 
                cur_dec++;
            } else {
                if (cur_dec > max_dec) max_dec = cur_dec;
                cur_dec = 1;
            }
            if (cur_dec > max_dec) max_dec = cur_dec;
        }

        if (curr % 2 == 0) {
            cur_even++;
            if (cur_even > max_even) max_even = cur_even;
        } else {
            cur_even = 0;
        }

        prev = curr;
        first_elem = false;
    }

    if (std::cin.fail() && !std::cin.eof()) {
        std::cerr << "Error: Input contains non-integer data.\n";
        return 1;
    }

    if (has_zero) {
        std::string dummy;
        if (std::cin >> dummy) {
            std::cerr << "Error: Input contains data after the terminating zero.\n";
            return 1;
        }
    } else {
        std::cerr << "Error: Sequence not terminated by zero.\n";
        return 1;
    }

    std::cout << max_dec << "\n";
    std::cout << max_even << "\n";

    return 0;
}
