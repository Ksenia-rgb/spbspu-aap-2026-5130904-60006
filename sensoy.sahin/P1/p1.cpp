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

int countLocalMinimums(const std::vector<int>& seq) {
    if (seq.size() < 3) {
        return 0;
    }
    int count = 0;
    for (size_t i = 1; i + 1 < seq.size(); ++i) {
        if (seq[i] < seq[i - 1] && seq[i] < seq[i + 1]) {
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

    if (sequence.empty()) {
        std::cerr << "[LOC-MIN] Error: Empty sequence\n";
        return 2;
    }

    int locMinResult = countLocalMinimums(sequence);
    std::cout << "[LOC-MIN] Output: " << locMinResult << "\n";

    return 0;
}
