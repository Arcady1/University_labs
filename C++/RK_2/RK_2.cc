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
#include <string.h> // для функции strchr()
#include <math.h>   // для использования модуля
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
    void reduce(int &);                                          // метод сокращения дроби
    int evclid();                                                // метод, реализующий алгоритм Евклида
    void output();                                               // метод вывода ответа
    int getNum() { return num; };
    int getDenom() { return denom; };
};

Fraction::Fraction(char *s)
{
    char *p = strchr(s, '/'); // указатель p указывает на черту

    if (p != NULL) // если наклонная черта найдена
    {
        *p = '\0';       // заменяем черту на нулевой байт, являющийся признаком конца строки
        p++;             // сдвигаем указатель p на следующий байт, указывающий на начало строки знаменателя
        denom = atoi(p); // присваиваем значение знаменателю
    }

    num = atoi(s); // присваиваем значение строки s числителю
};

Fraction Fraction::operator+(Fraction &second)
{
    Fraction result;
    // сохраняю знаменатель первой дроби, чтобы корректно домножать вторую
    int firstDen = this->denom;

    if (this->denom == second.denom)
    {
        result.num = this->num + second.num;
        result.denom = this->denom;

        return result;
    }

    // приведение дробей к общему знаменателю
    this->num *= second.denom;
    this->denom *= second.denom;
    second.num *= firstDen;
    second.denom *= firstDen;

    result.num = this->num + second.num;
    result.denom = this->denom;

    printf("Преобразование: %d/%d\n", this->num, this->denom);
    printf("\t\t%d/%d\n", second.num, second.denom);

    return result;
};

Fraction Fraction::operator=(Fraction &result)
{
    printf("@\n");
    // int sumNum, sumDenom;
    // sumNum = this->num * second.denom;

    // sumDenom =
    // this->num =
};

int Fraction::evclid()
{
    int a, b, t;
    a = abs(this->num);
    b = abs(this->denom);

    while (b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
};

void Fraction::reduce(int &gcd)
{
    this->num /= gcd;
    this->denom /= gcd;
};

void Fraction::output()
{
    int numer = this->num;
    int denomer = this->denom;
    int gcd;

    if (denomer == 1)
    {
        printf("Итог:\t\t%d\n", numer);
    }

    else if (numer > denomer)
    {
        printf("Итог:\t\t%d ", numer / denomer);

        this->num = numer % denomer;
        gcd = this->evclid();
        this->reduce(gcd);

        printf("%d/%d\n", this->num, this->denom);
    }
};

int main(int argc, char *argv[])
{
    int gcd;
    Fraction first = argv[1];
    Fraction second = argv[2];

    printf("Вы ввели:\t%d/%d\n", first.getNum(), first.getDenom());
    printf("\t\t%d/%d\n", second.getNum(), second.getDenom());

    Fraction sum = first + second;
    printf("Сумма:\t\t%d/%d\n", sum.getNum(), sum.getDenom());

    // поиск НОД
    gcd = sum.evclid();
    printf("НОД:\t\t%d\n", gcd);

    // сокращение дроби
    sum.reduce(gcd);
    printf("Итог:\t\t%d/%d\n", sum.getNum(), sum.getDenom());

    sum.output();

    return 0;
}
