/* Гусаров Аркадий РК6-23Б 1 курс. Программа для закраски окна алфавитно-цифровой консоли поочередно во все цвета фона 
в порядке роста их escape-кодов.
Запуск: ./a.out */
#include <string.h>    // для работы со строками
#include <sstream>     // i(o)stringsteam, str
#include <sys/ioctl.h> // winsize, (tty_)ioctl
#include <termios.h>   // termios, tc(s)getattr
#include <unistd.h>    // read
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
    // манипулятор EW - для очистки терминала
    ostream &EW(ostream &s)
    {
        return s << string("\033[2J"); // '\033[' - ESCAPE последовательность; 2 - очистка всей строки, J - очистка всего окна
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
        sout << "\033[" << code << "m "; // m - режим псевдографического отображения
        return estream(sout.str());
    }
} // namespace con

using con::CUP;
using con::EW;
using con::hmax;
using con::SGR;
using con::wmax;

int kbhit()
{
    int n = 0;
    char buf[512];
    struct termios t[2];
    tcgetattr(0, &t[0]);
    tcgetattr(0, &t[1]);
    t[0].c_lflag &= ~(ICANON | ECHO);
    t[0].c_cc[VMIN] = 0;
    t[0].c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &t[0]);
    n = read(0, buf, 512);
    tcsetattr(0, TCSAFLUSH, &t[1]);

    return (n);
}

int main(int argc, char *argv[])
{
    int wterm = wmax();         // ширина терминала
    int hterm = hmax();         // высота терминала
    int code_color = 40;        // цвет фона (код: 40 - 47)
    int x, y, x_mirror, center; // координаты
    int num_of_col = 0;         // кол-во закрашенных колонок

    center = wterm / 2;
    x = center;
    x_mirror = x - 1;
    y = 0;

    cout << EW; // очистка окна

    while (true)
    {
        wterm = wmax();                                       // ширина терминала
        hterm = hmax();                                       // высота терминала
        center = wterm / 2;                                   // обновление центра терминала
        cout << CUP(y, x) << SGR(code_color) << flush;        // точка справа
        cout << CUP(y, x_mirror) << SGR(code_color) << flush; // точка слева
        y++;

        if (y > hterm)
        {
            y = 0;
            x++;
            x_mirror = center - (x - center);
            num_of_col++;

            if (num_of_col == 2)
            {
                ++code_color;
                num_of_col = 0;
            }

            if (code_color > 47)
                code_color = 40;

            usleep(30000); // задержка в микросекундах
        }
        if (x == wterm)
        {
            x = center;
            x_mirror = x - 1;
            y = 0;
        }
        if (kbhit() > 0) // остановка при нажатии на любую клавишу
            break;
    }

    cout << SGR(0) << CUP(1, 1) << EW; // SGR(0): 0 - для сброса цвета строки; EW - для очистки терминала
    return 0;
}
