// Гусаров Аркадий РК6-23Б 1 курс. Программа поиска точки любого заданного набора точек на плоскости, которая наиболее удалена от начала координат
// Пример ввода: ./a.out 4,6 5,9

#include <iostream>
#include <math.h>
using namespace std;

class Point
{
private:
    int x;
    int y;

public:
    // конструктор по умолчанию
    Point() { x = y = 0; }

    Point(int valueX, int valueY)
    {
        x = valueX;
        y = valueY;
    }

    // геттеры - для получения координат x, y
    int GetX() { return x; };
    int GetY() { return y; };

    double distance()
    {
        return sqrt(x*x + y*y);
    }
};

int main(int argc, char const *argv[])
{
    int i = 0;
    int j = 0;
    int X, Y;
    double R = 0.0;
    double current_distance;
    Point *current_point;                               // указатель на текущие координаты
    Point **p;                                          // указателей на первый указатель массива указателей


    // проверка, что введены координаты хотя бы одной точки
    if ( argc < 2 ) { return -1; }

    p = new Point *[argc];                              // массив указателей размером argc

    while (++i < argc)
    {
        sscanf(argv[i], "%d%*c%d", &X, &Y);

        p[j] = new Point(X, Y);
        j++;
    }

    p[j] = NULL;                                        // инициализация последенй ячейки массива указателей

    for ( i = 0; p[i] != NULL; i++ )
    {
        current_point = p[i];                           // указатель на i-ые координаты (чтобы посмотреть значение X: 'cout << current_point->GetX() << endl;')
        current_distance = current_point->distance();

        if ( current_distance > R )
        {
            X = current_point->GetX();
            Y = current_point->GetY();
            R = current_distance;
        }
    }

    cout << X << "\t";
    cout << Y << "\t";
    cout << R << endl;

    // удаление указателей в массиве
    for ( i = 0; p[i] != NULL; i++ )
        delete p[i];
    
    // удаление самого массива
    delete[] p;

    return 0;
}