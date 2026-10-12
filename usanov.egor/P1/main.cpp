#include <iostream>

int main() {
    int previous2 = 0;
    int previous1 = 0;
    int current = 0;
    int elements = 0;

    int countGRT = 0;
    int countPTH = 0;
    bool afterZero = false;

    while (std::cin >> current) {
        if (afterZero) {
            continue;
        }

        if (current == 0) {
            afterZero = true;
            continue;
        }

        if (elements >= 2) {
            if (previous1 < previous2 && previous1 > current) {
                ++countGRT;
            }

            long long a = previous2;
            long long b = previous1;
            long long c = current;
            if (a * a + b * b == c * c) {
                ++countPTH;
            }
        }

        previous2 = previous1;
        previous1 = current;
        ++elements;
    }

    if (!afterZero) {
        if (std::cin.eof()) {
            std::cerr << "Error";
        } else {
            std::cerr << "Error\n";
        }
        return 1;
    }

    if (!std::cin.eof()) {
        std::cerr << "Error";
        return 1;
    }

    std::cout << countGRT << '\n' << countPTH << '\n';
    return 0;
}