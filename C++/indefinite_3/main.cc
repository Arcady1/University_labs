#include <math.h>
#include <iostream>
using namespace std;

class Ratio
{
private:
    int numer;                                                          // числитель дроби
    int denom;                                                          // знаменатель дроби
public:
    Ratio() { numer = denom = 1; };                                     // конструктор по умолчанию
    Ratio(int numer_, int denom_) : numer(numer_), denom(denom_) {};    // инициализация переменных списком
    void Div(int &);                                                    // метод реализует деление дроби на число; принимает делитель по ссылке
    void Evclid(void);                                                  // метод реализует алгоритм Евклида
    int getNumer() { return numer; };
    int getDenom() { return denom; };
};

void Ratio::Div(int &digit)
{
    this->denom *= digit;                                           // this указывает на то, что denom (слева от равно) принадлежит классу Ratio (указатель на текущий объект класса)
}

void Ratio::Evclid(void)
{
    int a, b, c;

    // ??? ПЕРЕГРУЗКА ОПЕРАТОРА ПРИСВАИВАНИЯ ???
    a = abs(this->numer);
    b = abs(this->denom);
    c = 1;

    while ( c != 0 )
    {
        // ??? ПЕРЕГРУЗКА ОПЕРАТОРА ПРИСВАИВАНИЯ ???
        c = a % b;
        a = b;
        b = c;
    }

    // ??? ПЕРЕГРУЗКА ОПЕРАТОРА ДЕЛЕНИЯ ???
    this->numer /= a;
    this->denom /= a;
}

int main(int argc, char const *argv[])
{
    int numer_;                                                     // числитель введенной дроби
    int denom_;                                                     // знаменатель введенной дроби
    int digit;                                                      // число, на которое делим дробь

    sscanf(argv[1], "%d/%d", &numer_, &denom_);
    sscanf(argv[2], "%d", &digit);

    Ratio drob(numer_, denom_);
    
    drob.Div(digit);
    // ВЫВОД ДРОБИ, РАЗДЕЛЕННОЙ НА ЧИСЛО (БЕЗ СОКРАЩЕНИЯ)
    cout << drob.getNumer() << "/" << drob.getDenom() << endl;

    drob.Evclid();
    // ВЫВОД СОКРАЩЕННОЙ ДРОБИ
    cout << drob.getNumer() << "/" << drob.getDenom() << endl;

    return 0;
}
