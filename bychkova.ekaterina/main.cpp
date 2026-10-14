#include <iostream>
#include <ios>

int main() {
    
    int one = 0;
    int two = 0;
    int cout = 0;

    int dline_vos = 0;
    int max_len = 0;
    int sign_changes = 0;

    while (true) {
        std::cin >> one;
        
        if (std::cin.fail()) {
            std::cerr << "Error: Invalid input data." << std::endl;
            return 1;
        }
    
        if (one == 0) {
            break;
        }
        
        cout++;
        
        if (cout == 1) {
            dline_vos = 1;
            max_len = 1;
        }
        
        else {
            if (one >= two) {
                dline_vos++;
            } else {
                dline_vos = 1;
            }
            
            if (dline_vos > max_len) {
                max_len = dline_vos;
            }

            if ((two > 0 && one < 0) or (two < 0 && one > 0)) {
                sign_changes++;
            }
        }

        two = one;
    }

    if (cout == 0) {
        std::cerr << "Error: нельзя рассчитать ни одну характеристику." << std::endl;
        return 2;
    }
    
    std::cout << max_len << std::endl;

    if (cout == 1) {
        std::cerr << "Error: нельзя рассчитать характеристику смены знака, нужно хотя бы 2 элемента." << std::endl;
        return 2;
    }

    std::cout << sign_changes << std::endl;
    
    return 0;
}


