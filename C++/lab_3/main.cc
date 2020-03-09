#include <stdio.h>
#include <iostream>
using namespace std;

class Point
{
private:
    int x;                                          // координаты точек
    int y;
public:
    Point( int x_, int y_ ) : x(x_), y(y_) {};      // конструктор инициализации списком
    //friend int distance_x(void);                    // дружественная ф-ия; принимает ..., возвращает расстояние между парами точек
    //void distance_y (void);                         // метод класса; принимает ..., возвращает ...
    int getX() { return x; };
    int getY() { return y; };
};

// int distance_x(void)
// {

//     return 1;
// }

int main(int argc, char const *argv[])
{
    Point** tab;                                    // указатель на первый указатель массива указателей
    int N;                                          // кол-во введенных точек
    int X, Y;                                       // координаты точек

    N = argc - 1;
    tab = new Point* [N];                           // массив указателей размерностью N

    for ( int i = 0; i < N; i++ )
    {
        sscanf(argv[i + 1], "%d%*c%d", &X, &Y);     // считываем координаты

        tab[i] = new Point (X, Y);                  // записываем координаты в массив
    }

    // вывод координат точек на экран
    for ( int i = 0; i < N; i++ )
    {
        printf("%d: (%d; %d)\n", i + 1, tab[i]->getX(), tab[i]->getY());
    }

    return 0;
}
