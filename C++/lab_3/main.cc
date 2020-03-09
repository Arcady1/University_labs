#include <stdio.h>
#include <iostream>
using namespace std;

class Point
{
private:
    int x;                                                  // координаты точек
    int y;
public:
    Point(int x_, int y_) : x(x_), y(y_) {};              // конструктор инициализации списком
    friend int distance_y(const void*, const void*);        // дружественная ф-ия; принимает ..., возвращает расстояние между парами точек
    //void distance_x (void);                               // метод класса; принимает ..., возвращает ...
    int getX() { return x; };
    int getY() { return y; };
};

int distance_y(const void* pp, const void* qq)
{
    Point** p = (Point**) pp;
    Point** q = (Point**) qq;

    return ( p[0]->y - q[0]->y );
}

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

    qsort(tab, N, sizeof(Point), distance_y);

    // вывод координат точек на экран
    for ( int i = 0; i < N; i++ )
    {
        printf("%d: (%d; %d)\n", i + 1, tab[i]->getX(), tab[i]->getY());
    }

    return 0;
}
