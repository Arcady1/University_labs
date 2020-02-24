#include <iostream>
#include <math.h>
using namespace std;

class Point
{
    private:
        int x;
        int y;
        Point(int _x, int _y) : x(_x), y(_y) { };
    public:
        int getx() { return x; };
        int gety() { return y; };
        Point() { x=y=0.0; };

        float distance (int, int);
};

float Point::distance (int X, int Y)
{
    float r = sqrt(X*X + Y*Y);

    return r;
}

int main(int argc, char const *argv[])
{
    int *x, *y;

    sscanf(argv[1], "(%d)", &x);

    //cout << x.getx() << endl;

    return 0;
}