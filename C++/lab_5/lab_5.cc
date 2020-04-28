// Гусаров Аркадий РК6-23Б 1 курс. Программа ...
// Пример ввода: ./a.out ...

#include <stdio.h>
#include <iostream>
using namespace std;

class Line;

class Dot
{
private:
    float x;
    float y;

public:
    Dot(float xx = 0.0, float yy = 0.0) : x(xx), y(yy){};
    float getX() { return x; };
    float getY() { return y; };
    friend class Line;
    friend ostream& operator<<(ostream&, Dot&);
};

ostream& operator<<(ostream& output, Dot& p)
{
    output << p.getX() << ";" << p.getY();
    return output;
}

class Line
{
private:
    Dot A;
    Dot B;

public:
    Line(Dot a, Dot b) : A(a), B(b){};
    Dot clipX();                                    // точка пересечения с осью OX
    Dot clipY();                                    // точка пересечения с осью OY
};

Dot Line::clipX()
{
    float x_;

    x_ = (B.x - A.x) * (-A.y) / (B.y - A.y) + A.x;
    return Dot(x_, 0.0);
}

Dot Line::clipY()
{
    float y_;

    y_ = (B.y - A.y) * (-A.x) / (B.x - A.x) + A.y;
    return Dot(y_, 0.0);
}

int main(int argc, char *argv[])
{
    Dot A(1, 2);
    Dot B(3, -2);
    Line L(A, B);

    Dot OX = L.clipX();    
    cout << OX << endl;

    Dot OY = L.clipY();    
    cout << OY << endl;

    return 0;
}
