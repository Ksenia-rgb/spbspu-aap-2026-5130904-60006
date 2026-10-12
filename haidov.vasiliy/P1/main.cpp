#include <iostream>

int sequence(){
    int element = 0;
    int len_m_d = 0;
    int len_max = 0;
    int last_el = 0;
    int max = 0;
    while(true){
        if(!(std::cin >> element)){
            std::cerr << "wrong element in sequence" << std::endl;
            return 1;
        }
        if(element == 0){
            std::cout << "Length of largest monotone-decreasing fragment: " << len_m_d << "\n";
            if(last_el == 0){
                std::cerr << "Amount of elements after maximal uncounted" << std::endl;
                return 2;
            }
            std::cout << "Amount of elements after maximal: " << len_max << std::endl;
            return 0;
        }
        if(last_el < element){
            len_m_d = 0;
        }
        if(max < element){
            len_max = -1;
            max = element;
        }
        last_el = element;
        len_m_d += 1;
        len_max += 1;
    }
    return 0;
}

int main(){
    sequence();
    return 0;
}
