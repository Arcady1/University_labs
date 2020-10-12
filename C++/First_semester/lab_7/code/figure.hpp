// Figure header file

#ifndef CHESSMAN
#define CHESSMAN

#include <iostream>

// Базовый класс шахматной фигуры
class Figure
{
public:
  Figure(char *);                     // конструктор преобразования
  Figure(){};                         // конструктор по умолчанию
  virtual char isA() { return '*'; }; // метод получения символа фигуры
  virtual int attack(char *);         // метод проверки угрозы для позиции
  static int deskout(char *);         // проверка выхода за границы доски
  void printBoard();                  // метод отображения доски с фигурой и позициями атаки
  Figure &operator=(char *);          // оператор присваивания
  int operator!=(char *);             // оператор неравенства

protected:
  char _position[2]; // позиция фигуры на доске a-h, 1-8
};

#endif
