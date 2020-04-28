// Гусаров Аркадий РК6-23Б 1 курс. Программа для вычисления значений следа прямых линий на осях координат.

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
    friend istream &operator>>(istream &, Dot &);
    friend ostream& operator<<(ostream&, Dot&);
    friend class Line;
};

istream &operator>>(istream &input, Dot &p)         // перегрузка ввода
{
    char semicolon;                                 // точка с запятой
    input >> p.x >> semicolon >> p.y;
    return input;
}

ostream& operator<<(ostream& output, Dot& p)        // перегрузка вывода
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
    Dot clipX();                                    // координата точки пересечения с осью OX
    Dot clipY();                                    // координата точки пересечения с осью OY
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
    return Dot(0.0, y_);
}

int main(int argc, char *argv[])
{
    Dot A, B;

    cout << "Input Ax;Ay or EXIT" << endl;

    while (cin >> A >> B)                           // пока данные вводятся корректно
    {
        Line L(A, B);

        Dot OX = L.clipX();    
        cout << OX << " ";

        Dot OY = L.clipY();    
        cout << OY << endl;

        cout << "Input Ax;Ay or EXIT" << endl;
    }    

    return 0;
}
