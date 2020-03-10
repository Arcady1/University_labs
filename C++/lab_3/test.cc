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
    void Div(int);                                                      // метод реализует деление дроби на число; принимает делитель
    int getNumer() { return numer; };
    int getDenom() { return denom; };
};

void Ratio::Div(int denom)
{
    this->denom *= denom;                                           // this указывает на то, что denom (слева от равно) принадлежит классу Ratio
}

int main(int argc, char const *argv[])
{
    int numer_;                                                     // числитель введенной дроби
    int denom_;                                                     // знаменатель введенной дроби
    int digit;                                                      // число, на которое делим дробь

    sscanf(argv[1], "%d%*c%d", &numer_, &denom_);
    sscanf(argv[2], "%d", &digit);

    Ratio drob(numer_, denom_);
    
    // ВЫВОД ДРОБИ И ЧИСЛА, НА КОТОРОЕ ДЕЛИМ
    cout << drob.getNumer() << "/" << drob.getDenom() << "; " << digit << endl;

    drob.Div(digit);

    // ВЫВОД ДРОБИ, РАЗДЕЛЕННОЙ НА ЧИСЛО (БЕЗ СОКРАЩЕНИЯ)
    cout << drob.getNumer() << "/" << drob.getDenom() << endl;

    return 0;
}
