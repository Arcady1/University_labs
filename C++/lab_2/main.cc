// Гусаров Аркадий РК6-23Б 1 курс. Программа

#include <iostream>
using namespace std;

// создаю класс Magic - магический квадрат
class Magic
{
    private:
        int row;                // строка
        int col;                // столбец
        unsigned** p;           // указатель на начало двумерного массива
    public:
        
        ~Magic();               // деструктор
        void Print();           // метод вывода магического квадрата на экран
};

int main(int argc, char const *argv[])
{
    
    return 0;
}
