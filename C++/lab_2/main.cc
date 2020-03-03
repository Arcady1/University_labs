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
        ~Magic();                                           // деструктор
        void Create();                                      // метод создания N - мерного массива и заполнения нулями
        void Fill_in();                                     // метод заполнения магического квадрата
        void Check_for_free(unsigned);                      // в методе реализован алгоритм размещения числа в матрице, в зависимости от условия: клетка пустая / непустая
        void Print();                                       // метод вывода магического квадрата на экран
};

Magic::~Magic()
{
    for ( row = 0; row < N; row++ )
        delete[] tab[row];
        
    delete[] tab;
}

void Magic::Create()
{
    tab = new unsigned* [N];                                // tab присваиваем указатель на первый указатель массива указателей

    for (row = 0; row < N; row++)                           // создаем N строк
        tab[row] = new unsigned [N];
        
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)                       // создаем N столбцов
            tab[row][col] = 0;                              // заполняем матрицу нулями
}

void Magic::Fill_in()
{
    unsigned current_digit;                                 // текущее число
    unsigned max_digit;                                     // максимально возможное число
    unsigned n;                                             // счетчик (позволяет не выходить за границы массива)

    current_digit = 1;
    max_digit = N * N;
    n = N - 1;
    row = n;
    col = n/2;
    tab[row][col] = current_digit;                          // расположение единицы в матрице (низ, центр)

    for (current_digit = 2; current_digit <= max_digit; current_digit++)
    {
        row -= 2;
        col -= 1;

        if ( ((row >=0) & (row <= n)) & ((col >=0) & (col <= n)) )
            Check_for_free(current_digit);
        else
        {
            if ( row >= 0 )
            {
                col += N;
                Check_for_free(current_digit);
            }
            else if ( col >= 0 )
            {
                row += N;
                Check_for_free(current_digit);
            }
            else
            {
                row += N;
                col += N;
                Check_for_free(current_digit);
            }
        }
    }    
}

void Magic::Check_for_free(unsigned cur_digit)
{
    int old_row, old_col;                           // координаты предыдущей точки

    if ( tab[row][col] == 0 )
    {
        tab[row][col] = cur_digit;
        old_row = row;
        old_col = col;
    }
    else
    {
        row = old_row;
        col = old_col;

        if ( row < 4 )
        {
            row += N - 4;
            tab[row][col] = cur_digit;
        }                    
        else
        {
            row -= 4;
            tab[row][col] = cur_digit;
        }
    }
}

void Magic::Print()
{
    unsigned len;                                   // в переменной хранится разрядности max числа
    unsigned N_2;
    int i;
    int j;

    len = 0;
    N_2 = N * N;

    while ( N_2 > 0 )                               // подсчет max разрядности числа
    {
        N_2 /= 10;
        len++;
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%0*d  ", len, tab[i][j]);
        }
        printf("\n");
    }
}

// предопределение функций для Main
int Check_for_Errors (int, int);                    // ф-ия проверки на ошибки при передаче аргументов; принимает кол-во аргументов и введенное число; возвращает введенное число

int main(int argc, char const *argv[])
{
    int N;

    N = Check_for_Errors(argc, atoi(argv[1]));      // задаем размерность массива через аргумент командной строки

    Magic magic(N);                                 // создаем объект класса Magic
    magic.Create();
    magic.Fill_in();
    magic.Print();

    return 0;
}

int Check_for_Errors(int argc_, int N)
{
    if ( argc_ == 1 )                               // проверка, что число передано
    {
        cout << "No digit" << endl;

        exit (1);
    }

    if ( argc_ > 2 )                                // проверка, что аргументов не больше двух
    {
        cout << "Too many arguments" << endl;

        exit (2);
    }

    if ( N < 1 )                                    // проверка, что число >= 1
    {
        cout << "The number < 1" << endl;

        exit (3);        
    }
    
    if ( (N % 2) == 0 )                             // проверка, что число нечетное
    {
        cout << "The number is even" << endl;

        exit (4);
    }

    return N;
}