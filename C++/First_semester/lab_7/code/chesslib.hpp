// chesslib header file

#ifndef CHESSLIB
#define CHESSLIB

#include "figure.hpp"

// фигура Alfil
class Alfil : virtual public Figure
{
public:
  Alfil(char *p) : Figure(p){}; // конструктор
  char isA() { return 'A'; };   // перегрузка метода
  int attack(char *);           // перегрузка метода
};

// фигура King
class King : virtual public Figure
{
public:
  King(char *p) : Figure(p){}; // конструктор
  char isA() { return 'K'; };  // перегрузка метода
  int attack(char *);          // перегрузка метода
};

// фигура Sultan, наследующая Alfil и King
class Sultan : public Alfil, public King
{
public:
  Sultan(char *p) : Alfil(p), King(p), Figure(p){}; // конструктор
  char isA() { return 'S'; };                       // перегрузка метода
  int attack(char *);                               // перегрузка метода
};

#endif
