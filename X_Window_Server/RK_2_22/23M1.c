/* 2 centred spiral implementation */

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include "23M.h"
#include <math.h>

int side(int x1, int x2, int y1, int y2)
{
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
int maxi(int x, int y, int w, int h)
{
	int m;

	if (side(x, 0, y, 0) > side(x, 0, y, h))
	{
		m = side(x, 0, y, 0);
	}
	else
	{
		m = side(x, 0, y, h);
	}
	if (m < side(x, w, y, 0))
	{
		m = side(x, w, y, 0);
	}
	if (m < side(x, w, y, h))
	{
		m = side(x, w, y, h);
	}
	return sqrt(m);
}

/* задание точек стрелки */
int configure_arrow(XEvent *ev, XArrow *pr, int w, int h)
{
	pr->x = ev->xbutton.x;
	pr->y = ev->xbutton.y;
	pr->R = 0;
	pr->dR = 20;
	pr->w = 10;
	pr->n = 1;
	pr->m = maxi(pr->x, pr->y, w, h) / pr->dR;
	return 0;
}

/*отрисовка стрелы в окне*/
int draw_arrow(Display *dpy, Window win, GC Bgc, GC Fgc, XArrow *pr, int w, int h)
{

	int n;
	int r = pr->dR;
	for (int i = 0; i < pr->n; i++)
	{
		XDrawArc(dpy, win, Bgc, pr->x + 10 * i, pr->y + 10 * i, pr->R - r * i, pr->R - r * i, 0 * 64, 360 * 64);
	}
	pr->R += pr->w;
	n = (int)pr->R / pr->dR;
	n++;
	if (2 * (pr->m + 3) >= n)
	{
		pr->n = n;
	}
	pr->x -= 5;
	pr->y -= 5;
	for (int j = 0; j < pr->n; j++)
	{
		XDrawArc(dpy, win, Fgc, pr->x + 10 * j, pr->y + 10 * j, pr->R - r * j, pr->R - r * j, 0 * 64, 360 * 64);
	}
	XFlush(dpy);
}

/* перерисовка потерянных фрагментов окна */
int redraw(XEvent *ev, GC Bgc, GC Fgc, XArrow *pr, int w, int h)
{
	static XRectangle clip[32]; /* clip rectangles buffer */
	static int n = 0;			/* clip rectangles number */
	clip[n].x = ev->xexpose.x;
	clip[n].y = ev->xexpose.y;
	clip[n].width = ev->xexpose.width;
	clip[n].height = ev->xexpose.height;
	n++;
	if ((ev->xexpose.count > 0) && (n < 32))
		return (0);
	XSetClipRectangles(ev->xexpose.display, Fgc, 0, 0, clip, n, Unsorted);

	XGCValues gv;
	gv.line_style = LineOnOffDash;
	XChangeGC(ev->xexpose.display, Fgc, GCLineStyle, &gv);
	gv.line_style = LineSolid;
	XChangeGC(ev->xexpose.display, Fgc, GCLineStyle, &gv);
	draw_arrow(ev->xexpose.display, ev->xexpose.window, Bgc, Fgc, pr, w, h);

	XSetClipMask(ev->xexpose.display, Fgc, None);
	return (n = 0);
} /* redraw */

/* ответ на собития нажатия клавиш */
int key_check(XEvent *ev)
{
	KeySym ks = XLookupKeysym((XKeyEvent *)ev, 0);
	// if ((ks == XK_Alt_L) && (ev->xkey.state == ControlMask))
	if (ks == XK_Alt_L)
	{
		return 0; /*код выхода*/
	}
	return -1;
} /* rapid */
