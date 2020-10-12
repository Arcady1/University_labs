/* Гусаров Аркадий РК6-23Б 1 курс. Программа для ычисления суммы обыкновенных дробей, которые должны передаваться ей через два аргумента командной строки.
Пример ввода: ./a.out 1/5 2/8 */

#include <stdlib.h> // для функции atoi()
#include <string.h> // для функции strchr()
#include <math.h>   // для использования модуля
#include <stdio.h>  // для функции printf()
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
    bool negative = false;
    int numer;
    int denomer = this->denom;
    int gcd;

    if (this->num < 0)
    {
        numer = abs(this->num);
        negative = true;
    }
    else
        numer = this->num;

    if (denomer == 1)
    {
        if (negative)
            printf("Результат:\t-%d\n", numer);
        else
            printf("Результат:\t%d\n", numer);
    }

    else if (numer > denomer)
    {
        if (negative)
            printf("Результат:\t-%d ", numer / denomer);
        else
            printf("Результат:\t%d ", numer / denomer);

        this->num = numer % denomer;
        printf("%d/%d\n", this->num, this->denom);
    }
};

void Errors(int, Fraction, Fraction); // функция проверки на ошибки

int main(int argc, char *argv[])
{
    int gcd;

    Fraction first = argv[1];
    Fraction second = argv[2];

    Errors(argc, first, second);

    printf("Вы ввели:\t%d/%d\n", first.getNum(), first.getDenom());
    printf("\t\t%d/%d\n", second.getNum(), second.getDenom());

    Fraction sum = first + second;
    printf("Сумма:\t\t%d/%d\n", sum.getNum(), sum.getDenom());

    if (sum.getNum() == 0)
    {
        printf("Итог:\t\t%d\n", sum.getNum());
        return 1;
    }

    // поиск НОД
    gcd = sum.evclid();
    printf("НОД:\t\t%d\n", gcd);

    // сокращение дроби
    sum.reduce(gcd);
    printf("Итог:\t\t%d/%d\n", sum.getNum(), sum.getDenom());

    sum.output();

    return 0;
}

void Errors(int argc, Fraction first, Fraction second)
{
    if (argc != 3)
    {
        printf("Ошибка при вводе аргументов\n");
        exit(1);
    }
    
    if ((first.getDenom() == 0) || (second.getDenom() == 0))
    {
        printf("0 в знаменателе\n");
        exit(2);
    }
}