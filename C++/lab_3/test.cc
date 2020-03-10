#include <iostream>
using namespace std;

class Ratio
{
private:
    int numer;                                                          // числитель дроби
    int denom;                                                          // знаменатель дроби
public:
    Ratio() { numer = denom = 1; }                                      // конструктор по умолчанию
    Ratio(int numer_, int denom_) : numer(numer_), denom(denom_) {};    // инициализация переменных списком
    int getNumer() { return numer; };
    int getDenom() { return denom; };
};

int main(int argc, char const *argv[])
{
    int numer_;                                                     // числитель введенной дроби
    int denom_;                                                     // знаменатель введенной дроби
    int digit;                                                      // число, на которое делим дробь

    sscanf(argv[1], "%d%*c%d", &numer_, &denom_);
    sscanf(argv[2], "%d", &digit);

    Ratio drob(numer_, denom_);
    
    cout << drob.getNumer() << "/" << drob.getDenom() << endl;
    cout << digit << endl;

    return 0;
}
