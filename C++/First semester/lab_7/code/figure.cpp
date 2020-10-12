// Figure cpp file

#include "figure.hpp"

using std::cout;

// конструктор
Figure::Figure(char *p)
{
  // TODO проверка длины p
  _position[0] = p[0];
  _position[1] = p[1];
}

// проверка выхода за границы доски
int Figure::deskout(char *p)
{
  // TODO проверка длины p
  return (p[0] > 'h') || (p[0] < 'a') || (p[1] < '1') || (p[1] > '8');
}

// оператор присваивания
Figure &Figure::operator=(char *p)
{
  // TODO проверка длины p
  _position[0] = p[0];
  _position[1] = p[1];
  return *this;
}

// оператор неравенства
int Figure::operator!=(char *p)
{
  // TODO проверка длины p
  return (_position[0] != p[0]) || (_position[1] != p[1]);
}

// вывод доски с фигурой
void Figure::printBoard()
{
  char s[2];
  const char *mark = ".x+";      // маркер позиции (безопасная / под атакой)
  cout << "  a b c d e f g h\n"; // верхняя строка
  for (int i = 8; i > 0; i--)
  {                   // цикл по строкам
    cout << i << ' '; // номер строки доски слева
    s[1] = '0' + i;   // текущая позиция по горизонтали
    for (int j = 0; j < 8; j++)
    {                 // цикл по столбцам
      s[0] = 'a' + j; // текущая позиция по вертикали
      // если позиция не совпадает с положением фигуры, то вывести маркер
      char m = (*this != s) ? mark[attack(s)] : isA();
      cout << m << ' ';
    }
    cout << i << "\n"; // номер строки доски справа
  }
  cout << "  a b c d e f g h\n"; // нижняя строка
}

// функция проверки позиции
int Figure::attack(char *p)
{
  return 0;
}
