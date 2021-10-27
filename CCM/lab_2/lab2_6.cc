/*
Перечислить все перестановки первых 5-ти натуральных чисел, 
используя факториальный алгоритм левого дополнения c инкрементом.

Компиляция: g++ lab2_6.cc 
Запуск: ./a.out
*/

#include <iostream>
#include <vector>

template <class T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &input)
{
    for (auto &i : input)
    {
        out << i << " ";
    }
    return out;
}

void FactorialRightAddition(std::vector<int> &array, int &globalCounter, int maxNumber)
{
    int mPosition = array.size();
    array.push_back(0);
    std::vector<int> arrayCopy = array;
    int m = 1;
    for (; m != array.size() + 1; m++)
    {
        array = arrayCopy;
        array[mPosition] = m;
        array[array.size() - 1] = m;
        for (int j = 0; j != mPosition; j++)
        {
            if (array[j] >= m)
            {
                array[j]++;
            }
        }
        if (array.size() == maxNumber)
        {
            std::cout << globalCounter++ << ") " << array << std::endl;
        }
        else if (m != array.size() + 1)
        {
            FactorialRightAddition(array, globalCounter, maxNumber);
        }
        else
        {
            return;
        }
    }
}

int main(int argc, char const *argv[])
{
    int globalCounter = 1;
    int arrayLength = 5;
    std::vector<int> array;
    array.push_back(1);

    FactorialRightAddition(array, globalCounter, arrayLength);

    return 0;
}