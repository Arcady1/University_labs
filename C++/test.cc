// Гусаров Аркадий РК6-23Б 1 курс. Программа построения магического квадрата любого нечетного порядка из последовательных натуральных чисел по методу Москопула.

#include <iostream>
#include <stdio.h>
using namespace std;

class Magic                                                 // создаю класс Magic - магический квадрат
{
    private:
        int row;                                            // строка
        int col;                                            // столбец
        int N;                                              // размерность массива
        unsigned** tab;                                     // указатель на первый указатель массива указателей (** - говорит, что будет двумерный массив)
    public:
        Magic(int dim) : N(dim) {};                         // конструктор инициализации размерности массива
        //~Magic();                                           // деструктор
        void Create();                                      // метод создания N - мерного массива и заполнения нулями
        void Fill_in();                                     // метод заполнения магического квадрата
        void Check_for_free(unsigned, int, int);            // в методе реализован алгоритм размещения числа в матрице, в зависимости от условия: клетка пустая / непустая
        void Print();                                       // метод вывода магического квадрата на экран
};

void Magic::Create()
{
    tab = new unsigned* [N];                                // tab присваиваем указатель на первый указатель массива указателей

    for (row = 0; row < N; row++)                           // создаем N строк
        tab[row] = new unsigned [N];
        
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)                       // создаем N столбоц
            tab[row][col] = 0;                              // инициализируем матрицу нулями
}

void Magic::Fill_in()
{
    unsigned current_digit;                                 // текущее число
    unsigned max_digit;                                     // максимально возможное число
    unsigned n;                                             // счетчик (позволяет не выходить за границы матрицы)
    int i, j;                                               // координаты 'current_digit'

    current_digit = 1;
    max_digit = N * N;
    n = N - 1;
    i = n;
    j = n/2;
    tab[i][j] = current_digit;                              // расположение единицы в матрице (низ, центр)

    for (current_digit = 2; current_digit != max_digit; current_digit++)
    {
        i -= 2;
        j -= 1;

        if ( ((i >=0) & (i <= n)) & ((j >=0) & (j <= n)) )
            Check_for_free(current_digit, i, j);
        else
        {
            if ( i >= 0 )
            {
                j += N;
                Check_for_free(current_digit, i, j);
            }
            else if ( j >= 0 )
            {
                i += N;
                Check_for_free(current_digit, i, j);
            }
            else
            {
                i += N;
                j += N;
                Check_for_free(current_digit, i, j);
            }
        }
    }    
}

void Magic::Check_for_free(unsigned cur_digit, int i, int j)
{
    Print();
    printf("\ni = %d; j = %d; digit = %d\n", i, j, cur_digit);

    if ( tab[i][j] == 0 )
        tab[i][j] = cur_digit;
    else
    {
        printf("@");
        if ( i <= 4 )
        {
            i += N - 4;
            tab[i][j] = cur_digit;
        }                    
        else
        {
            i -= 4;
            tab[i][j] = cur_digit;
        }                    
    }
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

    N = atoi(argv[1]);                      // задаем размернность массива через аргумент командной строки

    Magic magic(N);                         // создаем объект класса Magic
    magic.Create();
    magic.Fill_in();
    magic.Print();

    return 0;
}