// dlink.cpp
// Dlink class cpp file

#include "dlink.hpp"

Dlink::Dlink() {
  _next = _prev = NULL;
}

Dlink* Dlink::incr() {
  return _next;
}

Dlink* Dlink::decr() {
  return _prev;
}

Dlink* Dlink::append(Dlink* p) {
  p->_next = this;
  _prev = p;
  return p;
}

void Dlink::excluse() {
  if (_next != NULL) {
    _next->_prev = _prev;
  }
  if (_prev != NULL) {
    _prev->_next = _next;
  }
  return;
}

Dlink* Dlink::after(Dlink* p) {
  p->_next = _next;
  p->_prev = this;
  if (_next != NULL) {
    _next->_prev = p;
  }
  _next = p;
  return p->_next;
}

Dlink* Dlink::before(Dlink* p) {
  p->_next = this;
  p->_prev = _prev;
  if (_prev != NULL) {
    _prev->_next = p;
  }
  _prev = p;
  return p->_prev;
}

Dlink* Dlink::toHead() {
  Dlink* p = this;
  Dlink* q = NULL;
  while (p != NULL) {
    q = p;
    p = p->_prev;
  }
  return q;
}

Dlink* Dlink::toHead(int n) {
  Dlink* p = this;
  Dlink* q = this;
  int i = 0;
  while (p != NULL) {
    q = p;
    if (i == n)
      break;
    p = p->_prev;
    i++;
  }
  return q;
}

Dlink* Dlink::toTail() {
  Dlink* p = this;
  Dlink* q = NULL;
  while (p != NULL) {
    q = p;
    p = p->_next;
  }
  return q;
}

Dlink* Dlink::toTail(int n) {
  Dlink* p = this;
  Dlink* q = this;
  int i = 0;
  while (p != NULL) {
    q = p;
    if (i == n)
      break;
    p = p->_next;
    i++;
  }
  return q;
}
