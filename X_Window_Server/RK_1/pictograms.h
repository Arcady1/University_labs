#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
    Window window;
    unsigned long color;
} cell;

int xcustom();
int dispatch();
int redraw(short);
int repaint(XEvent *ev);
int key_analiz(XEvent*);
int free_custom();
int main(int, char* []);