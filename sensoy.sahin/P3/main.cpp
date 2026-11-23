#include <iostream>
#include <vector>

int countIncreasingElements(const std::vector<int>& seq) {
    if (seq.size() < 2) {
        return 0;
    }
    int count = 0;
    for (size_t i = 1; i < seq.size(); ++i) {
        if (seq[i] > seq[i - 1]) {
            ++count;
        }
    }
    return count;
}

int countDivisibleByPrevious(const std::vector<int>& seq) {
    int count = 0;
    for (size_t i = 1; i < seq.size(); ++i) {
        if (seq[i - 1] != 0 && seq[i] % seq[i - 1] == 0) {
            ++count;
        }
    }
    return count;
}

int main() {
    std::vector<int> sequence;
    int value = 0;

    while (std::cin >> value && value != 0) {
        sequence.push_back(value);
    }

    if (std::cin.fail()) {
        std::cerr << "Error: Invalid input\n";
        return 1;
    }

    int incResult = countIncreasingElements(sequence);
    std::cout << "[INC-SEQ] Output: " << incResult << "\n";

    if (sequence.size() < 2) {
        std::cerr << "[DIV-REM] Error: Sequence must contain at least 2 elements\n";
        return 2;
    }

    int divResult = countDivisibleByPrevious(sequence);
    std::cout << "[DIV-REM] Output: " << divResult << "\n";

    return 0;
}
