/* Гусаров Аркадий РК6-33Б 2 курс.
Имеется 3 сосуда с известными ёмкостями: А(8)>B(5)>C(3) литров. 
Больший сосуд заполнен водой. Нужно отмерить заданное количество 
D(4)<B(5) литров, переливая воду между сосудами. Требуется определить 
последовательность переливания, которая позволит получить в одном из 
сосудов D(4) литров воды. Последовательность переливаний должна 
имитировать траектория движения бильярдного шара, который отражается 
от бортов стола в форме параллелограмма. При этом плоскость стола 
градуируется сеткой равносторонних треугольников с длиной стороны, 
равной 1. Длины сторон параллелограмма равны ёмкостям меньших сосудов B и C. 
Больший сосуд обозначает отрезок параллельный диагонали параллелограмма, 
на который проектируются деления его сторон треугольной сеткой. 
Деления сторон и диагонального отрезка обозначают наполнение 
соответствующих им сосудов. Движение шара происходит по линиям 
градуировочной сетки в соответствии с физическим законом отражения. 
При этом можно выделить следующие три разновидности движения шара:

− Горизонтальная, когда вода переливается между сосудами A и B при C=const
− Левосторонняя, когда вода переливается между сосудами A и C при В=const
− Правосторонняя, когда вода переливается между сосудами B и C при А=const

Движение по треугольной сетке стола начинается из точки с координатами A=8, B=C=0. Решение задачи соответствует достижению точки на стороне параллелограмма или отрезке (параллельно его диагонали) одна из координат которой равна D(4).

Пример ввода: 
*/

#include <iostream>
#include <stdio.h>
using namespace std;

class Liters
{
private:
    // Вместимость каждого сосуда
    int A_st, B_st, C_st;
    // Количество литров, которое надо отмерить
    int D;
    // Начальное количество жидкости в сосудах
    int A;
    int B = 0;
    int C = 0;
    // Количество операций
    int step = 0;
    // Начальные индексы в сетке
    int i = 0;
    int j = 0;
    // Функция совершает перемещения по сетке
    void Move();

public:
    Liters(int A_, int B_, int C_, int D_) : A_st(A_), B_st(B_), C_st(C_), D(D_) { A = A_st; };
    int Overflow();
};

int Liters::Overflow()
{
    while (true)
    {
        cout << "A "
             << "B "
             << "C " << endl;
        cout << A << " " << B << " " << C << " " << endl;

        if ((A == D) || (B == D) || (C == D))
            return 0;

        if ((i == 0) && (j == 0) && (step != 0))
            return 1;

        if (i == 0)
            i = B_st;

        else if ((i == B_st) || (j == 0))
        {
            while (i != 0)
            {
                if (j == C_st)
                    break;
                --i;
                ++j;
            }
        }

        else if (j == C_st)
            j = 0;

        ++step;
        this->Move();
        cout << "\n";
    }
}

void Liters::Move()
{
    B = i;
    C = j;
    A = A_st - B - C;
}

// Функция делает проверку на ошибки ввода
void Errors(int, int, int, int);

int main(int argc, char *argv[])
{
    int a, b, c, d;

    cout << "Input: A B C D" << endl;
    cout << "A B C - volume of vessels\nD - to measure" << endl;
    cin >> a >> b >> c >> d;
    cout << "\n";

    Errors(a, b, c, d);

    Liters Do(a, b, c, d);
    int res = Do.Overflow();

    if (res == 0)
    {
        cout << "\nSuccess" << endl;
        return 0;
    }

    else if (res == 1)
    {
        cout << "\nError" << endl;
        return 1;
    }
}

void Errors(int a, int b, int c, int d)
{
    int errStatus = 0;
    int max;

    // Поиск max элемента среди A B и C
    if ((a >= b) && (a >= c))
        max = a;
    else if ((b >= a) && (b >= c))
        max = b;
    else if ((c >= a) && (c >= b))
        max = c;

    if (d > max)
        errStatus = 1;

    else if (max != a)
        errStatus = 1;

    else if (d < 0)
        errStatus = 1;

    if (errStatus == 1)
    {
        cout << "Input error" << endl;
        exit(1);
    }
}