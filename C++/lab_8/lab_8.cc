// Гусаров Аркадий РК6-23Б 1 курс. Программа

#include <string.h> // для работы со строками (пр.: 10)
#include <sstream>  // i(o)stringsteam, str
#include <iostream>
using namespace std;
// консольное пространство имен
namespace con
{
    // манипуляторы без параметров (ED, EL) для очистки терминала
    ostream &ED(ostream &s)
    {
        return s << string("\033[2J"); // '\033[' - ESCAPE последовательность; 2 - очистка всей строки, J - очистка всего окна
    }
    ostream &EL(ostream &s)
    {
        // !  в примере используется просто К
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
        ostringstream sout; // объект класса ostringstream. Это переменная выходного строкового потока, в которой будет формироваться ESCAPE - последовательность
        sout << "\033[" << y << ";" << x << "H";
        return estream(sout.str());
    }

} // namespace con

using con::CUP;

int main(int argc, char *argv[])
{

    return 0;
}
