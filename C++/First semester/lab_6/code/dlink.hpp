// dlink.hpp
// Dlink header file

#ifndef DLINK
#define DLINK

#include <cstdio>

// Dlink class
class Dlink {
protected:
  Dlink* _next;          // адрес следующей записи cписка
  Dlink* _prev;          // адрес предыдущей записи списка

public:
  Dlink();               // функция инициализации ссылок начала и конца
  void excluse();        // функция исключения текущей записи
  Dlink* append(Dlink*); // функция добавления новой записи
  Dlink* incr();         // функция получения адреса следующей записи
  Dlink* decr();         // функция получения адреса предыдущей записи
  Dlink* after(Dlink*);  // функция вставки записи после текущей
  Dlink* before(Dlink*); // функция вставки записи перед текущей
  Dlink* toHead();       // функция получения адреса начала списка
  Dlink* toHead(int);    // функция сдвига в направлении начала списка
  Dlink* toTail();       // функция получения адреса конца списка
  Dlink* toTail(int);    // функция сдвига в направлении конца списка

};

#endif
