/* 2 centred spiral main function */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "23M.h"

/* Main function */

int main()
{
    Display *dpy; /* Graphic Display */
    Window win;   /* programm main window */
    GC gc[2];     /* Black & White Graphic Context */
    int scr;      /* screen number = 0 */
    XArrow r;     /* spiral structure */
    XArrow *frag = (XArrow *)malloc(sizeof(XArrow));
    XArrow *p;
    int nfrag = 0;

    {                       /* Display Block */
        unsigned long tone; /* Light drawing tone */
        dpy = XOpenDisplay(NULL);
        scr = DefaultScreen(dpy);
        win = DefaultRootWindow(dpy);
        scr = DefaultScreen(dpy);
        gc[0] = XCreateGC(dpy, win, 0, 0);
        gc[1] = XCreateGC(dpy, win, 0, 0);
        tone = WhitePixel(dpy, scr); /* = 0xFFFFFF; */
        XSetForeground(dpy, gc[0], tone);

    } /* Display block */

    {                              /* Window block  */
        unsigned w = 640, h = 480; /* main window width & height */
        XSetWindowAttributes attr; /* window attributes structure */
        XGCValues gval;            /* GC structure */
        unsigned long amask;       /* window attributes mask */
        Window root = win;         /* Display root window */
        XSizeHints hint;           /* Geometry WM hints */

        /*создание окна*/
        amask = (CWOverrideRedirect | CWBackPixel);
        XGetGCValues(dpy, gc[1], GCBackground, &gval);
        attr.background_pixel = gval.background; /* = 0x0 */
        attr.override_redirect = False;
        win = XCreateWindow(dpy, root, 0, 0, w, h, 1, CopyFromParent,
                            InputOutput, CopyFromParent, amask, &attr);

        /*задание фиксированного размера окна*/
        hint.flags = (PMinSize | PMaxSize);
        hint.min_width = hint.max_width = w;
        hint.min_height = hint.max_height = h;
        XSetNormalHints(dpy, win, &hint);
        XStoreName(dpy, win, "spiral");
        XMapWindow(dpy, win);

    } /* window block */

    { /* Multi Block */

        unsigned long emask;    /* window event mask */
        XEvent event;           /* graphic event structure */
        int freeze = -1;        /* window visibility stop state */
        unsigned delay = DELAY; /* multi delay period = 2^rate */
        int multi = (1 << 12);  /* multi code */
        int count = 0;          /* delay count */
        int w = 500, h = 500;
        int reconf;

        emask = (EnterWindowMask | LeaveWindowMask | ButtonPressMask | ButtonReleaseMask | ExposureMask | StructureNotifyMask | KeyPressMask);
        XSelectInput(dpy, win, emask);

        while (multi != 0)
        { /* Async dispatch event with multic ground */
            event.type = 0;
            XCheckWindowEvent(dpy, win, emask, &event);
            switch (event.type)
            {
            case Expose:
                redraw(&event, gc[1], gc[0], &r, w, h);
                break;
            case ButtonPress:
                nfrag++;
                p = (XArrow *)malloc(sizeof(XArrow));
                configure_arrow(&event, p, w, h);
                frag = realloc(frag, (nfrag + 1) * sizeof(XArrow));
                memcpy((frag + nfrag - 1), p, sizeof(XArrow));
                break;
            case LeaveNotify:
                freeze = -1;
                break;
            case EnterNotify:
                freeze = 1;
            case KeyPress:
                multi = key_check(&event);
                break;
            default:
                break;
            } /* switck /
            }*/

            if (freeze < 0) /* Freeze display spiral */
            {
                continue;
            }
            if (count++ < delay) /* Delay display spiral */
            {
                continue;
            }
            count = 0; /* reset count to next delay */
            if (freeze == 1)
            {
                for (int i = 0; i < nfrag; i++)
                {
                    draw_arrow(dpy, win, gc[1], gc[0], &frag[i], w, h); //отрисовка треугольника
                }
            }
        } /* while event */
    }     /* multi block */

    { /* Exit block */
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
        free(frag);
        return (0);
    } /* exit block */

} /* main */
