#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <string.h>
#include "clock.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int maxisize(XArrow *pr, char *R0xN)
{
    int R0;
    int N;
    int empty;
    XParseGeometry(R0xN, &empty, &empty, &R0, &N);
    if (((pr->Length = R0) < 1) || (N < 1))
        N = R0 = 0;
    return (pr->LengthMax = 2 * R0 * N);
}

int decent(XArrow *pr)
{
    int w = 2 * (pr->LengthMax + pr->Length) + (8 + 8); /* R = R0 = dR now */
    pr->c[0].x = w / 2 - (pr->Length / 2);
    pr->c[1].x = pr->c[0].x + pr->Length; /* = w/2 + (pr->R/2); */
    pr->c[0].y = pr->c[1].y = w / 2 + 8;
    return (w);
}

int reset_one(XArrow *pr, int value, int length)
{
    pr->A = (30 * value * 64);
    pr->dA = (1 * 64);
    pr->Length = length;
    return (2 * (pr->c[0].y));
}

int reset_two(XArrow *pr, int value, int length)
{
    pr->A = (30 * value * 64);
    pr->dA = (6 * 64);
    pr->Length = length;
    return (2 * (pr->c[0].y));
}

int redraw(XEvent *ev, GC gc, XArrow *pr, XArrow *pr2)
{
    int y;
    XArrow r;
    XArrow r2;
    static XRectangle clip[32];
    static int n = 0;
    clip[n].x = ev->xexpose.x;
    clip[n].y = ev->xexpose.y;
    clip[n].width = ev->xexpose.width;
    clip[n].height = ev->xexpose.height;
    n++;
    if ((ev->xexpose.count > 0) && (n < 32))
        return (0);
    XSetClipRectangles(ev->xexpose.display, gc, 0, 0, clip, n, Unsorted);
    r = *pr;
    r2 = *pr2;
    XWindowAttributes attr;
    XGetWindowAttributes(ev->xexpose.display, ev->xexpose.window, &attr);
    pr->Length = attr.height / 5;
    pr2->Length = attr.height / 5;
    decent(pr);
    decent(pr2);
    reset_one(pr, 0, attr.width / 4);
    reset_two(pr2, 0, attr.width / 3);
    pr->c[0].x = attr.width / 2;
    pr->c[0].y = attr.height / 2;
    pr2->c[0].x = attr.width / 2;
    pr2->c[0].y = attr.height / 2;
    reset_one(&r, 0, attr.width / 4);
    y = reset_two(&r2, 0, attr.width / 3) - 8;
    while (twist_all(ev->xexpose.display, ev->xexpose.window, gc, &r, &r2) < pr->Length)
        ;
    r.dA = (pr->A - r.A);
    r2.dA = (pr2->A - r2.A);
    twist_all(ev->xexpose.display, ev->xexpose.window, gc, &r, &r2);
    XDrawString(ev->xexpose.display, ev->xexpose.window, gc,
                8, y, "Ctrl+End", 8);
    XSetClipMask(ev->xexpose.display, gc, None);
    return (n = 0);
}

int amod2pi(XArrow *pr)
{
    pr->A += (pr->dA);
    if (pr->A == (360 * 64))
        return (pr->A = (0 * 64));
    if (pr->A == (0 * 64))
        pr->A = (360 * 64);
    return (pr->A);
}

int twist_all(Display *dpy, Window win, GC gc, XArrow *arrow_one, XArrow *arrow_two)
{
    XClearWindow(dpy, win);

    float x1 = cos(3.14 * (arrow_one->A + 90 * 64) / (180 * 64)) * (arrow_one->Length);
    float y1 = sin(3.14 * (arrow_one->A + 90 * 64) / (180 * 64)) * (arrow_one->Length);

    float xs1 = cos(3.14 * (arrow_one->A + 100 * 64) / (180 * 64)) * (arrow_one->Length - 20);
    float ys1 = sin(3.14 * (arrow_one->A + 100 * 64) / (180 * 64)) * (arrow_one->Length - 20);

    float xs2 = cos(3.14 * (arrow_one->A + 80 * 64) / (180 * 64)) * (arrow_one->Length - 20);
    float ys2 = sin(3.14 * (arrow_one->A + 80 * 64) / (180 * 64)) * (arrow_one->Length - 20);

    XFillArc(dpy, win, gc, arrow_one->c[0].x - arrow_one->Length / 10, arrow_one->c[0].y - arrow_one->Length / 10, arrow_one->Length / 5, arrow_one->Length / 5, 0 * 64, 360 * 64);

    XDrawLine(dpy, win, gc, arrow_one->c[0].x, arrow_one->c[0].y, arrow_one->c[0].x - x1, arrow_one->c[0].y - y1);

    XDrawLine(dpy, win, gc, arrow_one->c[0].x - x1, arrow_one->c[0].y - y1, arrow_one->c[0].x - xs1, arrow_one->c[0].y - ys1);
    XDrawLine(dpy, win, gc, arrow_one->c[0].x - x1, arrow_one->c[0].y - y1, arrow_one->c[0].x - xs2, arrow_one->c[0].y - ys2);
    XDrawLine(dpy, win, gc, arrow_one->c[0].x - xs1, arrow_one->c[0].y - ys1, arrow_one->c[0].x - xs2, arrow_one->c[0].y - ys2);

    x1 = cos(3.14 * (arrow_two->A + 90 * 64) / (180 * 64)) * (arrow_two->Length);
    y1 = sin(3.14 * (arrow_two->A + 90 * 64) / (180 * 64)) * (arrow_two->Length);

    xs1 = cos(3.14 * (arrow_two->A + 100 * 64) / (180 * 64)) * (arrow_two->Length - 20);
    ys1 = sin(3.14 * (arrow_two->A + 100 * 64) / (180 * 64)) * (arrow_two->Length - 20);

    xs2 = cos(3.14 * (arrow_two->A + 80 * 64) / (180 * 64)) * (arrow_two->Length - 20);
    ys2 = sin(3.14 * (arrow_two->A + 80 * 64) / (180 * 64)) * (arrow_two->Length - 20);

    XDrawLine(dpy, win, gc, arrow_two->c[0].x, arrow_two->c[0].y, arrow_two->c[0].x - x1, arrow_two->c[0].y - y1);

    XDrawLine(dpy, win, gc, arrow_two->c[0].x - x1, arrow_two->c[0].y - y1, arrow_two->c[0].x - xs1, arrow_two->c[0].y - ys1);
    XDrawLine(dpy, win, gc, arrow_two->c[0].x - x1, arrow_two->c[0].y - y1, arrow_two->c[0].x - xs2, arrow_two->c[0].y - ys2);
    XDrawLine(dpy, win, gc, arrow_two->c[0].x - xs1, arrow_two->c[0].y - ys1, arrow_two->c[0].x - xs2, arrow_two->c[0].y - ys2);

    XFlush(dpy);
    amod2pi(arrow_one);
    amod2pi(arrow_two);
    return (arrow_one->Length);
}

int twist_only_one(Display *dpy, Window win, GC gc, XArrow *arrow_one, XArrow *arrow_two)
{
    XClearWindow(dpy, win);

    float x1 = cos(3.14 * (arrow_one->A + 90 * 64) / (180 * 64)) * (arrow_one->Length);
    float y1 = sin(3.14 * (arrow_one->A + 90 * 64) / (180 * 64)) * (arrow_one->Length);

    float xs1 = cos(3.14 * (arrow_one->A + 100 * 64) / (180 * 64)) * (arrow_one->Length - 20);
    float ys1 = sin(3.14 * (arrow_one->A + 100 * 64) / (180 * 64)) * (arrow_one->Length - 20);

    float xs2 = cos(3.14 * (arrow_one->A + 80 * 64) / (180 * 64)) * (arrow_one->Length - 20);
    float ys2 = sin(3.14 * (arrow_one->A + 80 * 64) / (180 * 64)) * (arrow_one->Length - 20);

    XFillArc(dpy, win, gc, arrow_one->c[0].x - arrow_one->Length / 10, arrow_one->c[0].y - arrow_one->Length / 10, arrow_one->Length / 5, arrow_one->Length / 5, 0 * 64, 360 * 64);

    XDrawLine(dpy, win, gc, arrow_one->c[0].x, arrow_one->c[0].y, arrow_one->c[0].x - x1, arrow_one->c[0].y - y1);

    XDrawLine(dpy, win, gc, arrow_one->c[0].x - x1, arrow_one->c[0].y - y1, arrow_one->c[0].x - xs1, arrow_one->c[0].y - ys1);
    XDrawLine(dpy, win, gc, arrow_one->c[0].x - x1, arrow_one->c[0].y - y1, arrow_one->c[0].x - xs2, arrow_one->c[0].y - ys2);
    XDrawLine(dpy, win, gc, arrow_one->c[0].x - xs1, arrow_one->c[0].y - ys1, arrow_one->c[0].x - xs2, arrow_one->c[0].y - ys2);

    x1 = cos(3.14 * (arrow_two->A + 90 * 64) / (180 * 64)) * (arrow_two->Length);
    y1 = sin(3.14 * (arrow_two->A + 90 * 64) / (180 * 64)) * (arrow_two->Length);

    xs1 = cos(3.14 * (arrow_two->A + 100 * 64) / (180 * 64)) * (arrow_two->Length - 20);
    ys1 = sin(3.14 * (arrow_two->A + 100 * 64) / (180 * 64)) * (arrow_two->Length - 20);

    xs2 = cos(3.14 * (arrow_two->A + 80 * 64) / (180 * 64)) * (arrow_two->Length - 20);
    ys2 = sin(3.14 * (arrow_two->A + 80 * 64) / (180 * 64)) * (arrow_two->Length - 20);

    XDrawLine(dpy, win, gc, arrow_two->c[0].x, arrow_two->c[0].y, arrow_two->c[0].x - x1, arrow_two->c[0].y - y1);

    XDrawLine(dpy, win, gc, arrow_two->c[0].x - x1, arrow_two->c[0].y - y1, arrow_two->c[0].x - xs1, arrow_two->c[0].y - ys1);
    XDrawLine(dpy, win, gc, arrow_two->c[0].x - x1, arrow_two->c[0].y - y1, arrow_two->c[0].x - xs2, arrow_two->c[0].y - ys2);
    XDrawLine(dpy, win, gc, arrow_two->c[0].x - xs1, arrow_two->c[0].y - ys1, arrow_two->c[0].x - xs2, arrow_two->c[0].y - ys2);

    XFlush(dpy);
    amod2pi(arrow_one);
    return (arrow_one->Length);
}

int twist_only_two(Display *dpy, Window win, GC gc, XArrow *arrow_one, XArrow *arrow_two)
{
    XClearWindow(dpy, win);

    float x1 = cos(3.14 * (arrow_one->A + 90 * 64) / (180 * 64)) * (arrow_one->Length);
    float y1 = sin(3.14 * (arrow_one->A + 90 * 64) / (180 * 64)) * (arrow_one->Length);

    float xs1 = cos(3.14 * (arrow_one->A + 100 * 64) / (180 * 64)) * (arrow_one->Length - 20);
    float ys1 = sin(3.14 * (arrow_one->A + 100 * 64) / (180 * 64)) * (arrow_one->Length - 20);

    float xs2 = cos(3.14 * (arrow_one->A + 80 * 64) / (180 * 64)) * (arrow_one->Length - 20);
    float ys2 = sin(3.14 * (arrow_one->A + 80 * 64) / (180 * 64)) * (arrow_one->Length - 20);

    XFillArc(dpy, win, gc, arrow_one->c[0].x - arrow_one->Length / 10, arrow_one->c[0].y - arrow_one->Length / 10, arrow_one->Length / 5, arrow_one->Length / 5, 0 * 64, 360 * 64);

    XDrawLine(dpy, win, gc, arrow_one->c[0].x, arrow_one->c[0].y, arrow_one->c[0].x - x1, arrow_one->c[0].y - y1);

    XDrawLine(dpy, win, gc, arrow_one->c[0].x - x1, arrow_one->c[0].y - y1, arrow_one->c[0].x - xs1, arrow_one->c[0].y - ys1);
    XDrawLine(dpy, win, gc, arrow_one->c[0].x - x1, arrow_one->c[0].y - y1, arrow_one->c[0].x - xs2, arrow_one->c[0].y - ys2);
    XDrawLine(dpy, win, gc, arrow_one->c[0].x - xs1, arrow_one->c[0].y - ys1, arrow_one->c[0].x - xs2, arrow_one->c[0].y - ys2);

    x1 = cos(3.14 * (arrow_two->A + 90 * 64) / (180 * 64)) * (arrow_two->Length);
    y1 = sin(3.14 * (arrow_two->A + 90 * 64) / (180 * 64)) * (arrow_two->Length);

    xs1 = cos(3.14 * (arrow_two->A + 100 * 64) / (180 * 64)) * (arrow_two->Length - 20);
    ys1 = sin(3.14 * (arrow_two->A + 100 * 64) / (180 * 64)) * (arrow_two->Length - 20);

    xs2 = cos(3.14 * (arrow_two->A + 80 * 64) / (180 * 64)) * (arrow_two->Length - 20);
    ys2 = sin(3.14 * (arrow_two->A + 80 * 64) / (180 * 64)) * (arrow_two->Length - 20);

    XDrawLine(dpy, win, gc, arrow_two->c[0].x, arrow_two->c[0].y, arrow_two->c[0].x - x1, arrow_two->c[0].y - y1);

    XDrawLine(dpy, win, gc, arrow_two->c[0].x - x1, arrow_two->c[0].y - y1, arrow_two->c[0].x - xs1, arrow_two->c[0].y - ys1);
    XDrawLine(dpy, win, gc, arrow_two->c[0].x - x1, arrow_two->c[0].y - y1, arrow_two->c[0].x - xs2, arrow_two->c[0].y - ys2);
    XDrawLine(dpy, win, gc, arrow_two->c[0].x - xs1, arrow_two->c[0].y - ys1, arrow_two->c[0].x - xs2, arrow_two->c[0].y - ys2);

    XFlush(dpy);
    amod2pi(arrow_two);
    return (arrow_two->Length);
}

int rep5355(Display *dpy, int r)
{
    XKeyboardControl kbval;
    kbval.key = XKeysymToKeycode(dpy, XK_KP_Add);
    kbval.auto_repeat_mode = r;
    XChangeKeyboardControl(dpy, (KBKey | KBAutoRepeatMode), &kbval);
    kbval.key = XKeysymToKeycode(dpy, XK_KP_Subtract);
    XChangeKeyboardControl(dpy, (KBKey | KBAutoRepeatMode), &kbval);
    return (r);
}

int rapid(XEvent *ev, int t)
{
    char sym[1];
    KeySym code[1];
    XLookupString((XKeyEvent *)ev, NULL, 0, code, NULL);
    switch (code[0])
    {
    case XK_plus:
    case XK_KP_Add:
        if (t > 1)
            t >>= 1;
        break;
    case XK_minus:
    case XK_KP_Subtract:
        if (t < (1 << 30))
            t <<= 1;
        break;
    case 0:
        t = (-32);
        break;
    case XK_End:
        if (ev->xkey.state & ControlMask)
            t = 0;
        break;
    default:
        break;
    }
    return (t);
}

int overlap(XEvent *ev)
{
    if (ev->xvisibility.state != VisibilityUnobscured)
        return (-32);
    return (0);
}
