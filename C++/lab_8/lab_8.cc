// Гусаров Аркадий РК6-23Б 1 курс. Программа

#include <string.h>    // для работы со строками
#include <sstream>     // i(o)stringsteam, str
#include <sys/ioctl.h> // winsize, (tty_)ioctl
#include <iostream>
using namespace std;
// консольное пространство имен
namespace con
{
    // ширина терминала
    int wmax()
    {
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        return (w.ws_col);
    }
    // высота терминала
    int hmax()
    {
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        return (w.ws_row);
    }
    // манипуляторы EW, ES - для очистки терминала
    ostream &EW(ostream &s)
    {
        return s << string("\033[2J"); // '\033[' - ESCAPE последовательность; 2 - очистка всей строки, J - очистка всего окна
    }
    ostream &ES(ostream &s)
    {
        return s << string("\033[2K"); // 2K - очистка всей строки
    }
    // класс escape - потока
    class estream
    {
    private:
        string escape;

    public:
        estream(string e) : escape(e){};                // функция контроля консольного ввода
        friend ostream &operator<<(ostream &, estream); // перегрузка оператора вывода
    };

    ostream &operator<<(ostream &s, estream e)
    {
        // манипулятор flush передает в поток содержи­мое буфера
        s << e.escape << flush;
        return s;
    };

    // манипулятор CUP - для управления курсором
    estream CUP(int y, int x) // y, x - номер строки и столба
    {
        /* объект класса ostringstream. Это переменная выходного строкового потока, 
        в которой будет формироваться ESCAPE - последовательность */
        ostringstream sout;
        sout << "\033[" << y << ";" << x << "H";
        return estream(sout.str());
    }
    // манипулятор SGR - для закрашивания области; принмает код цвета
    estream SGR(int code)
    {
        ostringstream sout;
        sout << "\033[" << code << "m ";
        return estream(sout.str());
    }

} // namespace con

using con::CUP;
using con::ES;
using con::EW;
using con::hmax;
using con::SGR;
using con::wmax;

int main(int argc, char *argv[])
{
    int wterm = wmax();         // ширина терминала
    int hterm = hmax();         // высота терминала
    int code_color = 40;        // цвет фона (код: 40 - 47)
    int x, y, x_mirror, center; // координаты

    center = wterm / 2;
    x = center;
    x_mirror = x - 1;
    y = 0;

    cout << EW; // очистка окна

    // TODO увеличить ширину полоски в 2 раза
    while (true)
    {
        cout << CUP(y, x) << SGR(code_color) << flush;        // точка справа
        cout << CUP(y, x_mirror) << SGR(code_color) << flush; // точка слева
        y++;

        if (y > hterm)
        {
            y = 0;
            x++;
            x_mirror = center - (x - center);
            code_color++;

            if (code_color > 47)
            {
                code_color = 40;
            }
        }
        if (x == wterm)
        {
            x = center;
            x_mirror = x - 1;
            y = 0;
        }
    }

    // TODO при остановке программы полная очистка терминала
    cout << EW << CUP(1, 1);
    return 0;
}
