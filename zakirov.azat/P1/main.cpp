#include <iostream>
#include <cctype>
#include <climits>

namespace zakirov
{
    int run()
    {
        int number = 0;
        int prev = 0;
        int min = 0;
        long long minCount = 0;
        long long divCount = 0;

        bool hasPrevious = false;
        bool hasPair = false;
        bool minOverflow = false;
        bool divOverflow = false;

        std::cout << "Введите целые числа через пробел (0 — конец ввода):\n";

        while (true)
        {
            if (!(std::cin >> number))
            {
                std::cerr << "Ошибка: нужны целые числа в диапазоне int и 0 в конце ввода.\n";
                return 1;
            }

            int next = std::cin.peek();
            if (!std::cin.eof() && !std::isspace(next))
            {
                std::cerr << "Ошибка: ввод содержит нецелое число или посторонние символы.\n";
                return 1;
            }

            if (number == 0)
            {
                break;
            }

            if (!hasPrevious || number < min)
            {
                min = number;
                minCount = 1;
                minOverflow = false;
            }
            else if (number == min)
            {
                if (minCount == LLONG_MAX)
                {
                    minOverflow = true;
                }
                else
                {
                    minCount++;
                }
            }
            if (hasPrevious)
            {
                hasPair = true;
                if (prev == -1 || number % prev == 0)
                {
                    if (divCount == LLONG_MAX)
                    {
                        divOverflow = true;
                    }
                    else
                    {
                        divCount++;
                    }
                }
            }

            prev = number;
            hasPrevious = true;
        }

        int result = 0;

        if (minOverflow)
        {
            std::cerr << "Ошибка в пункте 16: количество превышает диапазон long long.\n";
            result = 2;
        }
        else
        {
            std::cout << "Пункт 16. Количество минимальных элементов: " << minCount << '\n';
        }

        if (!hasPair)
        {
            std::cerr << "Ошибка в пункте 11: нужно хотя бы два числа до нуля.\n";
            result = 2;
        }
        else if (divOverflow)
        {
            std::cerr << "Ошибка в пункте 11: количество превышает диапазон long long.\n";
            result = 2;
        }
        else
        {
            std::cout << "Пункт 11. Количество элементов, делящихся на предыдущий без остатка: "
                      << divCount << '\n';
        }

        return result;
    }
}

int main()
{
    return zakirov::run();
}
