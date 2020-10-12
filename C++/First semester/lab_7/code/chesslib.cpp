// chesslib cpp file

#include "chesslib.hpp"

// функция проверки позиции для Alfil
int Alfil::attack(char *p)
{
  if (deskout(p) > 0)
  {
    return 0;
  }
  int x = p[0] - _position[0];
  int y = p[1] - _position[1];
  if (x < 0)
  {
    x = -x;
  }
  if (y < 0)
  {
    y = -y;
  }
  if ((x == 2) & (y == 2))
  {
    return 1;
  }
  return 0;
}

// функция проверки позиции для King
int King::attack(char *p)
{
  if (deskout(p) > 0)
  {
    return 0;
  }
  int x = p[0] - _position[0];
  int y = p[1] - _position[1];
  if (x < 0)
  {
    x = -x;
  }
  if (y < 0)
  {
    y = -y;
  }
  if ((x <= 1) & (y <= 1))
  {
    return 2;
  }
  return 0;
}

// функция проверки позиции для Sultan
int Sultan::attack(char *s)
{
  if (Alfil::attack(s) > 0)
    return 1;
  if (King::attack(s) > 0)
    return 2;
  return 0;
}
