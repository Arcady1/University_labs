// main file
/* Вывести шахматную доску, на которой будет базовая фигура, Alfil, King или
Sultan в заданной позиции. Позиции под атакой фигуры должны быть обозначены *,
x, + в соответствии с фигурой. */

#include <iostream>
#include "chesslib.hpp"

int main(int argc, char **argv)
{
  // проверка числа аргументов и допустимости позиции
  if (argc < 2)
  {
    std::cout << "Incorrect argument" << std::endl;
    return 1;
  }
  if (Figure::deskout(argv[1]))
  { // вызов статического метода (sic!)
    std::cout << "Incorrect position " << argv[1] << std::endl;
    return 1;
  }
  Sultan f(argv[1]); // создание фигуры
  f.printBoard();    // (sic!)
  return 0;
}
