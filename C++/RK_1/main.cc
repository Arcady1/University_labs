// Гусаров Аркадий РК6-23Б 1 курс. Программа поиска точек заданного набора точек на плоскости, над которыми доминирует каждая последующая точка (т.е. поиск точек с меньшими значениями обеих координат)
// Пример ввода: ./a.out 2,5 7,5 -2,-6 6,9 0,0

#include <stdio.h>
#include <iostream>
using namespace std;

class Point
{
private:
    int x;                                                  // координаты точек
    int y;
public:
    Point(int x_, int y_) : x(x_), y(y_) {};                // конструктор инициализации списком
    int distance_x (Point*);                                // метод класса; принимает точку, возвращает расстояние между точками по OX
    friend int distance_y(const void*, const void*);        // дружественная ф-ия; принимает два указателя любого типа, возвращает расстояние между между точками по OY
    int getX() { return x; };
    int getY() { return y; };
};

inline int Point::distance_x(Point* p)
{
    return ( x - p->x );
}

int distance_y(const void* pp, const void* qq)
{
    Point** p = (Point**) pp;                                   // приводим переменную pp типа void к типу Point** и записываем значение в p (сравнимо с tab** - с. 28)
    Point** q = (Point**) qq;                                   // приводим переменную qq типа void к типу Point** и записываем значение в q

    return ( p[0]->y - q[0]->y );
}

int main(int argc, char const *argv[])
{
    Point** tab;                                                // указатель на первый указатель массива указателей
    int N;                                                      // кол-во введенных точек
    int X, Y;                                                   // координаты точек
    int i, j;                                                   // счетчики для циклов

    N = argc - 1;
    tab = new Point* [N];                                       // массив указателей размерностью N

    for ( i = 0; i < N; i++ )
    {
        sscanf(argv[i + 1], "%d%*c%d", &X, &Y);                 // считываем координаты

        tab[i] = new Point (X, Y);                              // записываем координаты в массив
    }

    qsort(tab, N, sizeof(Point), distance_y);

    printf("(%d; %d)", tab[0]->getX(), tab[0]->getY());         // вывод минимальной точки

    for ( i = 1; i < N; i++ )                                   // вывод доминирующих точек
    {
        printf("\n(%d; %d):", tab[i]->getX(), tab[i]->getY());

        for ( j = i - 1; j >= 0; j-- )
            if ( (tab[i]->getY()) > (tab[j]->getY()) )
                if ( tab[i]->distance_x(tab[j]) > 0 )
                    printf(" (%d; %d)", tab[j]->getX(), tab[j]->getY());
    }

    printf("\n");

    return 0;
}
