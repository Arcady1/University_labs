// Гусаров Аркадий РК6-23Б 1 курс. Программа построения магического квадрата любого нечетного порядка из последовательных натуральных чисел по методу Москопула.

#include <iostream>
#include <stdio.h>
using namespace std;

// создаю класс Magic - магический квадрат
class Magic
{
    private:
        int row;                            // строка
        int col;                            // столбец
        int N;                              // размерность массива
        unsigned** tab;                     // указатель на первый указатель массива указателей (** - говорит, что будет двумерный массив)
    public:
        Magic(int dim) : N(dim) {};         // конструктор инициализации размерности массива
        //~Magic();                           // деструктор
        void Create();
        void Fill_in();                     // метод заполнения магического квадрата
        void Print();                       // метод вывода магического квадрата на экран
};

void Magic::Create()
{
    tab = new unsigned* [N];                // tab присваиваем указатель на первый указатель массива указателей

    for (row = 0; row < N; row++)           // создаем N строк
        tab[row] = new unsigned [N];
        
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)       // создаем N столбоц
            tab[row][col] = 0;              // инициализируем матрицу нулями
}

void Magic::Fill_in()
{

}

void Magic::Print()
{
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            printf("%d\t", tab[row][col]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    int N;

    N = atoi(argv[1]);              // задаем размернность массива через аргумент командной строки

    Magic magic(N);                 // создаем объект класса Magic
    magic.Create();
    magic.Fill_in();
    magic.Print();

    return 0;
}