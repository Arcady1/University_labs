#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include "clock.h"

/* Main function */

int main(int argc, char *argv[])
{
    Display *dpy;
    Window win;
    GC gc[2];
    XArrow arrow_one;
    XArrow arrow_two;

    {
        /* Display Block */
        unsigned long tone;
        XFontStruct *fnptr;
        dpy = XOpenDisplay(NULL);
        DefaultScreen(dpy);
        win = DefaultRootWindow(dpy);
        DefaultScreen(dpy);
        gc[0] = XCreateGC(dpy, win, 0, 0);
        gc[1] = XCreateGC(dpy, win, 0, 0);
        tone = 0x0FFF0F;
        XSetForeground(dpy, gc[0], tone);
        if ((fnptr = XLoadQueryFont(dpy, "9x15")) != NULL)
            XSetFont(dpy, gc[0], fnptr->fid);
    } /* Display block */

    {
        /* Window block  */
        unsigned w, h;
        XSetWindowAttributes attr;
        XGCValues gval;
        unsigned long amask;
        Window root = win;
        XSizeHints hint;
        Atom wdw[1];
        if (argc < 2)
            argv[1] = "6:9";
        int value_1, value_2;
        if (sscanf(argv[1], "%d:%d", &value_1, &value_2) != 2)
        {
            value_1 = 6;
            value_2 = 9;
        }
        maxisize(&arrow_one, "16x8");
        decent(&arrow_one);
        maxisize(&arrow_two, "16x8");
        w = decent(&arrow_two);
        reset_two(&arrow_two, value_2, 90);
        h = reset_one(&arrow_one, value_1, 120);
        fflush(stdout);
        amask = (CWOverrideRedirect | CWBackPixel);
        XGetGCValues(dpy, gc[1], GCBackground, &gval);
        attr.background_pixel = gval.background;
        attr.override_redirect = False;
        win = XCreateWindow(dpy, root, 0, 0, w, h, 1, CopyFromParent,
                            InputOutput, CopyFromParent, amask, &attr);
        hint.flags = (PMinSize | PMaxSize);
        hint.min_width = w;
        hint.min_height = h;
        hint.max_width = 785;
        hint.max_height = 785;
        XSetNormalHints(dpy, win, &hint);
        XStoreName(dpy, win, "clock");
        wdw[0] = XInternAtom(dpy, "WM_DELETE_WINDOW", True);
        XSetWMProtocols(dpy, win, wdw, 1);
        XMapWindow(dpy, win);
    } /* window block */

    {
        /* Multi Block */
        unsigned long emask;
        XEvent event;
        int freeze_one = 0;
        unsigned delay_one = (1 << 12);
        int multi_one = (1 << 12);
        int count_one = 0;
        int freeze_two = 0;
        unsigned delay_two = (1 << 12);
        int multi_two = (1 << 12);
        int count_two = 0;
        int g = 0;
        emask = (ExposureMask | KeyPressMask | FocusChangeMask |
                 VisibilityChangeMask | ButtonReleaseMask | ButtonPressMask);
        XSelectInput(dpy, win, emask);
        while (multi_one != 0 || multi_two != 0)
        {
            event.type = 0;
            XCheckWindowEvent(dpy, win, emask, &event);
            switch (event.type)
            {
            case Expose:
                redraw(&event, gc[0], &arrow_one, &arrow_two);
                break;
            case VisibilityNotify:
                freeze_one = overlap(&event);
                freeze_two = overlap(&event);
                break;
            case ButtonRelease:
                if (event.xbutton.button == Button1)
                {
                    delay_one = multi_one = (1 << 12);
                    freeze_one = 0;
                }
                else
                {
                    if (event.xbutton.button == Button3)
                    {
                        delay_two = multi_two = (1 << 12);
                        freeze_two = 0;
                    }
                }
                break;
            case ButtonPress:
            case KeyPress:
                if (event.xbutton.button == Button1)
                {
                    if ((multi_one = rapid(&event, delay_one)) < 0)
                    {
                        freeze_one = -1;
                    }
                }
                else
                {
                    if (event.xbutton.button == Button3)
                    {
                        if ((multi_two = rapid(&event, delay_two)) < 0)
                        {
                            freeze_two = -1;
                        }
                    }
                    else
                    {
                        if (event.xbutton.button == Button2)
                        {
                            arrow_one.dA = -arrow_one.dA;
                            arrow_two.dA = -arrow_two.dA;
                        }
                        else
                        {
                            if ((multi_one = rapid(&event, delay_one)) == 0)
                                multi_two = 0;
                        }
                    }
                }
                break;
            default:
                break;
            }

            if (count_two++ < delay_two || count_one++ < delay_one)
            {
                continue;
            }

            if ((freeze_one < 0) && (freeze_two < 0))
            {
                continue;
            }

            if ((freeze_one < 0))
            {
                count_two = 0;
                twist_only_two(dpy, win, gc[g], &arrow_one, &arrow_two);
                continue;
            }

            if ((freeze_two < 0))
            {
                count_one = 0;
                twist_only_one(dpy, win, gc[g], &arrow_one, &arrow_two);
                continue;
            }
            count_one = 0;
            count_two = 0;

            twist_all(dpy, win, gc[g], &arrow_one, &arrow_two);
        }
    } /* multi block */

    {
        /* Exit block */
        rep5355(dpy, AutoRepeatModeOn);
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
        return (0);
    } /* exit block */

} /* main */