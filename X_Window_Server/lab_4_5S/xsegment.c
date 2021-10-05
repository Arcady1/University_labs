/* RubberSort & Search: Oval functions overload */

#include <X11/Xlib.h>

#include <math.h> /* nesessary for library sqrt() */

#include "xsort.h"

/* figure type set {XSegment, XRectangle, XArc} */

typedef XSegment XFig; /* set figure type for oval */

/* figure type macro converter from (XFragment* ) */

#define REFIG(F) (F->seg) /* address seg, rec or arc */

#define EXTRAFILL 0 /* extra fragment fill (set 1 or 0) */

#define FIXEDFILL 0 /* fix fragment nofill (set 1 or 0) */

/* check fragment fill macros by type */

#define ISFILL(t) ((t) > 0 ? EXTRAFILL : FIXEDFILL)

/* Check (x,y) hited fragment */

int fragon(XFragment *ff, int x, int y, int t)
{

    XFig *f = REFIG(ff);

    XPoint p[2]; /* focuses pos */

    if (((x < (f->x1 - 1)) || (x > (f->x2 + 1))) &&

        ((y < (f->y1 - 1)) || (y > (f->y2 + 1))))

        return (0); /* no oval inclusion rectangle zone */

    if (t < 0) /* for invoke by fragover */

        return (-t); /* to overlap control */

    if (ISFILL(t) > 0) /* check filling oval */

        return (1); /* hit inside oval */

    return (1); /* hit oval contour */

} /* fragon */

/* Overlap 2 fragmentes */

int fragover(XFragment *ff1, XFragment *ff2)
{

    XFig *f1 = REFIG(ff1);

    XFig *f2 = REFIG(ff2);

    XSegment s1, s2; /* oval f1 & f2 frames */

    XSegment r; /* overlap oval frames */

    int x, y; /* internal overlap frame pointer */

    s1.x1 = f1->x1;
    s1.x2 = f1->x2;

    s1.y1 = f1->y1;
    s1.y2 = f1->y2;

    s2.x1 = f2->x1;
    s2.x2 = f2->x2;

    s2.y1 = f2->y1;
    s2.y2 = f2->y2;

    if ((s1.x1 > s2.x2) || (s2.x1 > s1.x2) ||

        (s1.y1 > s2.y2) || (s2.y1 > s1.y2))

        return (0); /* No overlap oval frames */

    r.x1 = (s1.x1 > s2.x1) ? s1.x1 : s2.x1; /* max frames x1 */

    r.y1 = (s1.y1 > s2.y1) ? s1.y1 : s2.y1; /* max frames y1 */

    r.x2 = (s1.x2 < s2.x2) ? s1.x2 : s2.x2; /* min frames x2 */

    r.y2 = (s1.y2 < s2.y2) ? s1.y2 : s2.y2; /* min frames y2 */

    r.x1 -= 2;
    r.y1 -= 2;
    r.x2 += 2;
    r.y2 += 2; /* line width */

    for (y = r.y1; y < r.y2; y++) /* y-scan overframe */

        for (x = r.x1; x < r.x2; x++) /* x-scan overframe */

            if (fragon(ff1, x, y, -1) > 0) /* inner point oval 1 */

                if (fragon(ff2, x, y, -1) > 0) /* inner point oval 2 */

                    return (1); /* inner point overlap ovals */

    return (0); /* No overlap ovals */

} /* fragover */

/* 2 Fragment difference for qsort*/

int difrag(XFragment *ff1, XFragment *ff2)
{

    XFig *f1 = REFIG(ff1);

    XFig *f2 = REFIG(ff2);

    int s1 = sqrt(pow(f1->x2 - f1->x1, 2) + pow(f1->y2 - f1->y1, 2));

    int s2 = sqrt(pow(f2->x2 - f2->x1, 2) + pow(f2->y2 - f2->y1, 2));

    return s1 - s2;

} /* difrag */

/* Addressed Call fragment extra method by MACRO NUMBER */

int fragextra(int (*fe[])())
{ /* set extra method number */

    return ((*fe[IDENFRAG])()); /* MINI MAXI MEAN DIFF IDEN GRP2 */

} /* fragextra */

/* Fragment gabarit size */

int fragsize(XFragment *ff)
{
    XFig *f = REFIG(ff);

    int size = sqrt(pow(f->x2 - f->x1, 2) + pow(f->y2 - f->y1, 2));

} /* fragsize */

/* Tiny Fragment test */

int tinyfrag(XFragment *ff)
{

    XFig *f = REFIG(ff);

    if (fabs(f->x2 - f->x1) < 8 && fabs(f->y2 - f->y1) < 8)

        return 1;

    return 0;

} /* minifrag */

/* Stick fragment base xy-point */

int frag0(XFragment *ff, int x, int y)
{

    XFig *f = REFIG(ff);

    f->x1 = x;

    f->y1 = y;

    f->x2 = x;

    f->y2 = y;

    return (0);

} /* frag0 */

/* Variate fragment contour by xy-point */

int fragvar(XFragment *ff, int x, int y)
{

    XFig *f = REFIG(ff);

    f->x2 = x;

    f->y2 = y;

    return 0;

} /* fragvar */

/* Max fragment x-coordinate */

/* Draw rubber fragment contour */

int XContour(Display *dpy, Window win, GC gc, XFragment *ff)
{

    XFig *f = REFIG(ff);

    XDrawSegments(dpy, win, gc, f, 1);

    return (0);

} /* XContours */

/* Draw 1 Fixed Fragmentes */

int XFix(Display *dpy, Window win, GC gc, XFragment *ff)
{

    XFig *f = REFIG(ff);

    XDrawSegments(dpy, win, gc, f, 1); /* need at any case */

    return (0);

} /* XFix */

/* Draw Extra Fragment(s) */

int XExtra(Display *dpy, Window win, GC gc, XFragment *ff)
{

    XFig *f = REFIG(ff);

    XDrawSegments(dpy, win, gc, f, 1);

    return (0);

} /* XExtra */

int fragmaxix(XFragment *ff)
{

    XFig *f = REFIG(ff);

    return (f->x2);
} /* fragmaxix */

/* Max fragment y-coordinate */

int fragmaxiy(XFragment *ff)
{

    XFig *f = REFIG(ff);

    return (f->y2);

} /* fragmaxiy */