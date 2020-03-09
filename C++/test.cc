#include <iostream>
using namespace std;

class Point
{
private:
    int x;                                          // координаты точек
    int y;
public:
    Point( int x_, int y_ ) : x(x_), y(y_) {};      // конструктор инициализации списком
    friend int distance_x(void);                    // дружественная ф-ия; принимает ..., возвращает расстояние между парами точек
    void distance_y (void);                         // метод класса; принимает ..., возвращает ...
    int getX() { return x; };
    int getY() { return y; };
};

int main(int argc, char const *argv[])
{
    int N;                                          // кол-во введенных точек

    N = argc - 1;

    return 0;
}
