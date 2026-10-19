#include <iostream>

namespace chizhova {
    int solve() {
        int val = 0;
        int count_read = 0;
        int x = 0, y = 0, z = 0;
        int max_len = 0;
        int curr_len = 0;
        int count_grt_lss = 0;
        while (true) {
            if (!(std::cin >> val)) {
                std::cerr << "Error: Invalid input or missing terminating 0\n";
                return 1;
            }
            if (val == 0) {
                break;
            }
            count_read++;
            if (count_read == 1) {
                x = val;
                curr_len = 1;
                max_len = 1;
            } else if (count_read == 2) {
                y = val;
                if (y >= x) {
                    curr_len++;
                } else {
                    curr_len = 1;
                }
                if (curr_len > max_len) {
                    max_len = curr_len;
                }
            } else {
                z = val;
                if (z >= y) {
                    curr_len++;
                } else {
                    curr_len = 1;
                }
                if (curr_len > max_len) {
                    max_len = curr_len;
                }
                if (x > y && y > z) {
                    count_grt_lss++;
                }
                x = y;
                y = z;
            }
        }
        std::cout << max_len << "\n";
        std::cout << count_grt_lss << "\n";
        return 0;
    }
} 
int main() {
    return chizhova::solve();
}
