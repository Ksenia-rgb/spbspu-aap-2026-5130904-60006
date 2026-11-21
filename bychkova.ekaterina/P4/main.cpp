#include <cstddef>
#include <cstdlib>
#include <iostream>

char* read_line(std::istream& in) {
    std::size_t capacity = 16;
    std::size_t length = 0;

    char* s = static_cast<char*>(std::malloc(capacity));
    if (s == nullptr) {
        return nullptr;
    }

    char c = 0;
    while (in.get(c) && c != '\n') {
        if (length + 1 == capacity) {
            capacity *= 2;
            char* bigger = static_cast<char*>(std::malloc(capacity));

            if (bigger == nullptr) {
                std::free(s);
                return nullptr;
            }

            for (std::size_t i = 0; i < length; i++) {
                bigger[i] = s[i];
            }

            std::free(s);
            s = bigger;
        }

        s[length] = c;
        length++;
    }

    s[length] = '\0';
    return s;
}

int has_seq_sym(const char* s) {
    for (std::size_t i = 0; s[i] != '\0' && s[i + 1] != '\0'; i++) {
        if (s[i] == s[i + 1]) {
            return 1;
        }
    }
    return 0;
}

char* missing_letters(const char* s) {
    char* result = static_cast<char*>(std::malloc(27));
    if (result == nullptr) {
        return nullptr;
    }

    std::size_t n = 0;
    for (char letter = 'a'; letter <= 'z'; letter++) {
        char big = static_cast<char>(letter - 32);
        bool found = false;

        for (std::size_t i = 0; s[i] != '\0'; i++) {
            if (s[i] == letter || s[i] == big) {
                found = true;
                break;
            }
        }

        if (!found) {
            result[n] = letter;
            n++;
        }
    }

    result[n] = '\0';
    return result;
}

int main() {
    char* s = read_line(std::cin);
    char* result = (s != nullptr) ? missing_letters(s) : nullptr;

    if (s == nullptr || result == nullptr) {
        std::cerr << "memory error" << std::endl;
        std::free(s);
        std::free(result);
        return 1;
    }

    std::cout << has_seq_sym(s) << std::endl;
    std::cout << result << std::endl;

    std::free(s);
    std::free(result);

    return 0;
}
