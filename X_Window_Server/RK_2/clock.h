#ifndef CLOCK_H
#define CLOCK_H

typedef struct
{
  int A;
  int dA;
  XPoint c[2];
  int LengthMax;
  int Length;
} XArrow;

int maxisize(XArrow *, char *);
int reset_one(XArrow *, int value, int);
int reset_two(XArrow *, int value, int);
int decent(XArrow *);
int redraw(XEvent *, GC, XArrow *, XArrow *);
int amod2pi(XArrow *);
int twist_all(Display *, Window, GC, XArrow *, XArrow *);
int twist_only_one(Display *, Window, GC, XArrow *, XArrow *);
int twist_only_two(Display *, Window, GC, XArrow *, XArrow *);
int rep5355(Display *, int);
int rapid(XEvent *, int);
int overlap(XEvent *);

#endif //CLOCK_H
