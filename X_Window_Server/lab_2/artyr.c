// ! Компиляция: cc xfloor.c -lX11

#include <X11/Xlib.h>  /* заголовок базовой Х графики */
#include <X11/Xutil.h> /* заголовок графических утилит */
/* Габаритные макросы для рисунка фона*/
#define WIDTH 128  /* ширина повторяющегося элемента */
#define HEIGHT 128 /* высота повторяющегося элемента */

int main(int argc, char *argv[])
{
    Display *dpy;              /* адрес дисплейной структуры */
    int src;                   /* номер экрана дисплея */
    GC gc;                     /* графический контекст */
    int depth;                 /* число цветовых плоскостей экрана */
    Window root;               /* корневое окно экрана */
    Pixmap pix;                /* пиксельная карта элемента фона */
    Window win;                /* основное окно программы */
    XSetWindowAttributes attr; /* атрибуты окна программы*/
    unsigned long amask;       /* маска атрибутов окна */
    unsigned long emask;       /* маска событий */
    XEvent event;              /* структура оконных событий */
    unsigned int done = 0;     /* флаг завершения программы */

    /* Графическая инициализация */
    dpy = XOpenDisplay(NULL);       /* Контакт с Х-сервером */
    src = DefaultScreen(dpy);       /* номер экрана (0)*/
    depth = DefaultDepth(dpy, src); /* глубина экрана */
    root = DefaultRootWindow(dpy);  /* корневое окно */
    gc = DefaultGC(dpy, src);       /* графический контекст */

    pix = XCreatePixmap(dpy, root, 2 * WIDTH, 2 * HEIGHT, depth);
    XSetBackground(dpy, gc, WhitePixel(dpy, src));
    XSetForeground(dpy, gc, WhitePixel(dpy, src));
    XFillRectangle(dpy, pix, gc, 0, 0, 2 * WIDTH, 2 * HEIGHT);
    XSetForeground(dpy, gc, BlackPixel(dpy, src));

    XDrawArc(dpy, pix, gc, 0, 0, WIDTH, HEIGHT, 0, (360 * 64));
    XDrawLine(dpy, pix, gc, WIDTH / 2, HEIGHT, WIDTH / 2, 2 * HEIGHT);
    XDrawLine(dpy, pix, gc, WIDTH, HEIGHT / 2, 2 * WIDTH, HEIGHT / 2);
    XFlush(dpy);

    amask = (CWOverrideRedirect | CWBackPixmap);
    attr.override_redirect = False; /* Обрамление окна */
    attr.background_pixmap = pix;   /* Фон пиксельной карты */

    win = XCreateWindow(dpy, root, 0, 0, 800, 600, 1, depth,
                        InputOutput, CopyFromParent, amask, &attr);

    emask = (ButtonPressMask | ButtonReleaseMask |
             EnterWindowMask | LeaveWindowMask |
             KeyPressMask); /* Маска событий */

    XSelectInput(dpy, win, emask);   /* маскировка событий */
    XMapRaised(dpy, win);            /* отображение окна */
    XStoreName(dpy, win, "Floor");   /* заголовок окна */
    XSetFunction(dpy, gc, GXinvert); /* для инверсии фона */

    while (done == 0)
    {
        XNextEvent(dpy, &event); /* Чтение событий */
        switch (event.type)
        {
        case EnterNotify:
        case LeaveNotify:
        case ButtonPress:
        case ButtonRelease:
            XCopyArea(dpy, pix, pix, gc, 0, 0,
                      2 * WIDTH, 2 * HEIGHT, 0, 0);
            XSetWindowBackgroundPixmap(dpy, win, pix);
            XClearWindow(dpy, win);
            break;
        case KeyPress: /* Выход из цикла обработки событий */
            done = event.xkey.keycode;
            break;
        default:
            break;
        }
    }

    XFreePixmap(dpy, pix);    /* Освободить память карты */
    XDestroyWindow(dpy, win); /* Закрыть окно */
    XCloseDisplay(dpy);       /* Разрыв связи с Х-сервером */

    return (done); /* exit-код */
}