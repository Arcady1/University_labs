/* Разработать объектно-ориентированную программу для вычисления суммы обыкновенных дробей, 
которые должны передаваться ей через два аргумента командной строки. Результат суммирования 
должен отображаться строкой стандартного вывода в формате обыкновенной дроби. Во всех случаях 
для записи обыкновенных дроби должен применяться символьный формат, где ее числитель и 
знаменатель разделены знаком '/'. 
Программная реализация вычислений суммы должна быть основана на разработке 
класса обыкновенных дробей с приватными полями 
данных для целочисленных значений числителя и знаменателя, а также компонентным методом 
перегрузки оператора '+'. Конструкторы класса должны выполнять преобразования обоих 
операндов в указанный числовой формат обыкновенных дробей. Для приведения исходных и 
результирующей обыкновенных дробей к несократимому виду следует предусмотреть компонентный 
метод, реализующий алгоритм Евклида, и перегрузку оператора присваивания.
*/

#include <stdlib.h> // для функции atoi()
#include <stdio.h>
#include <iostream>
using namespace std;

class Fraction
{
private:
    int num;   // числитель дроби
    int denom; // знаменатель дроби
public:
    Fraction(){};                                                // констрктор по умолчанию
    Fraction(int num_, int denom_) : num(num_), denom(denom_){}; // констрктор со списком инициализации
    Fraction(char *);                                            // конструктор инициализации строки
    Fraction operator+(Fraction &);                              // перегрузка оператора '+' для сложения дробей
    Fraction operator=(Fraction &);                              // перегрузка оператора '='
    Fraction evclid(Fraction);                                   // метод, реализующий алгоритм Евклида
    int getNum() { return num; };
    int getDenom() { return denom; };
};

Fraction::Fraction(char *frac)
{
    int count = 0;
    num = 0;
    denom = 0;

    while (*frac)
    {
        count++;

        if (*frac != '/') // инициализация введенной дроби
        {
            if (count == 1)
                num = atoi(frac);
            else
                denom = atoi(frac);
        }

        frac++;
    }
};

Fraction Fraction::operator+(Fraction &second){};

Fraction Fraction::operator=(Fraction &obj){};

Fraction Fraction::evclid(Fraction sum){};

int main(int argc, char *argv[])
{
    Fraction first = argv[1];
    Fraction second = argv[2];
    Fraction sum = first + second;

    printf("Вы ввели: %d/%d\n", first.getNum(), first.getDenom());
    printf("Вы ввели: %d/%d\n", second.getNum(), second.getDenom());

    return 0;
}
