#include <iostream>
#include <cctype>

namespace batyushov
{
    int run()
    {
        int number = 0;
        int prev = 0;
        int prevPrev = 0;
        long long count = 0;

        long long curDec = 0;
        long long maxDec = 0;
        long long locMax = 0;

        while (true)
        {
            if (!(std::cin >> number))
            {
                std::cerr << "Ошибка: ввод не является последовательностью целых чисел\n";
                return 1;
            }

            int next = std::cin.peek();
            if (!std::cin.eof() && !std::isspace(next))
            {
                std::cerr << "Ошибка: ввод содержит нецелое число или другие символы \n";
                return 1;
            }

            if (number == 0)
            {
                break;
            }

            if (count > 0 && number <= prev)
            {
                curDec++;
            }
            else
            {
                curDec = 1;
            }
            if (curDec > maxDec)
            {
                maxDec = curDec;
            }

            if (count >= 2 && prev > prevPrev && prev > number)
            {
                locMax++;
            }

            prevPrev = prev;
            prev = number;
            count++;
        }

        int result = 0;

        std::cout << maxDec << '\n';

        if (count == 0)
        {
            std::cerr << "Ошибка: последовательность слишком короткая\n";
            result = 2;
        }
        else
        {
            std::cout << locMax << '\n';
        }

        return result;
    }
}

int main()
{
    return batyushov::run();
}
