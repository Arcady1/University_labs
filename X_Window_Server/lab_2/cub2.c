#include "polyhedron.h" //cc -o Lab2 xheap0.c xheap1.c xheap2.c -lX11 -L/usr/X11R6/lib
#include <X11/XKBlib.h>

static XVertex *vertex;                                 /* адрес массива вершин */
static XEdge *edge;                                     /* адрес массива ребер */
static XFace *face;                                     /* адрес массива граней */
static unsigned long palette[(NTONE+1)];                /* коды цветов */

int relink(XPolyGraph *pg)
{
    vertex = pg->vertex;                                /* адрес массива вершин */
    edge = pg->edge;                                    /* адрес массива ребер */
    face = pg->face;                                    /* адрес массива граней */
    return(0);
} /* relink */

int colorite(Display* dpy) 
{
    int scr;                                            /* номер экрана (по умолчанию) */
    Colormap cmap;                                      /* палитра (карта) цветов экрана */
    XColor rgb;                                         /* цветная структура */
    int i;                                              /* спектральный номер цвета */
    static char* spector[] = {                          /* Cпектр кодов (имен) цветов */
                            "#ffffff",                  /* или "W(w)hite" (белый) */
                            "#ff0000",                  /* или "R(r)ed" (красный) */
                            "#00ff00",                  /* или "G(g)reen" (зеленый) */
                            "#0000ff",                  /* или " B(b)lue" (синий) */
                            "#000000"                   /* или "B(b)lack" (черный) */
                            };                          /* RGB-спецификация цветов */
    scr = DefaultScreen(dpy);                           /* получить номер экрана (0) */
    cmap = DefaultColormap(dpy, scr);                   /* экранная палитра */
    for(i = 0; i < (NTONE+1); i++ ) {                   /* Спектральный цикл */
    XParseColor(dpy, cmap, spector[i], &rgb);           /* −> RGB */
    XAllocColor(dpy, cmap, &rgb);                       /* −> pixel-код */
    palette[i] = rgb.pixel;                             /* запомнить pixel-код цвета */
    } /* for */
    return(0);
} /* colorite */

GC congraph(Display* dpy) 
{
    int scr = DefaultScreen(dpy);                       /* номер экрана */
    XGCValues gcval;                                    /* параметры графконтекста */
    GC gc;                                              /* идентификатор графконтекста */
    gcval.line_width = EWIDTH;                          /* толщина контура графа */
    gcval.background = palette[DEFTONE];                /* код фона */
    gc = DefaultGC(dpy, scr);                           /* Установка графконтекста */
    XChangeGC(dpy, gc, GCLineWidth | GCBackground, &gcval);
    return(gc);                                         /* GC −> main */
} /* congraph */

Window wingraph(Display* dpy) 
{
    Window root;                                        /* идентификатор корневого окна экрана */
    int scr;                                            /* номер экрана по умолчанию */
    int depth;                                          /* число цветовых плоскостей экрана */
    Window win;                                         /* идентификатор окна программы */
    XSetWindowAttributes attr;                          /* структура атрибутов окна */
    XSizeHints hint;                                    /* геометрия окнного менеджмента */
    int x, y;                                           /* координаты окна */
    unsigned w, h;                                      /* габариты окна */
    unsigned long mask;                                 /* маска атрибутов окна */
    mask = CWOverrideRedirect | CWBackPixel | CWEventMask;
    attr.override_redirect = False;                     /* WM-контроль окна */
    attr.background_pixel = palette[DEFTONE];           /* цвет фона */
    attr.event_mask = (ButtonPressMask | KeyPressMask |
                                ExposureMask | StructureNotifyMask | 
                                FocusChangeMask);       /* Маска событий */
    root=DefaultRootWindow(dpy);                        /* корневое окно */
    scr = DefaultScreen(dpy);                           /* номер экрана */
    depth=DefaultDepth(dpy, scr);                       /* глубина экрана */
    w = DisplayWidth(dpy, scr) / 2;                     /* Расположить окно */
    h = DisplayHeight(dpy, scr) / 2;                    /* площадью 1/4 экрана */
    x = w / 2; y = h / 2;                               /* в центре экрана */
    win = XCreateWindow(dpy, root, x, y, w, h, 1, depth,
                        InputOutput, CopyFromParent, mask, &attr);
    hint.flags = (PMinSize | PPosition | PMaxSize);     /* Задать поля для геометрического свойства WM */
    hint.min_width = hint.min_height = (8*VDOT);       
    hint.max_width = 2*w; hint.max_height = 2*h;          
    hint.x = x; hint.y = y;    
    XSetNormalHints(dpy, win, &hint);                   /* −> свойство WM */
    //XStoreName(dpy, win);                        /* Задать заголовок окна */
    XMapWindow(dpy, win);                               /* Отобразить окно на экране */
    return(win);                                        /* возврат идентификатока окна в main */
} /* wingraph */

/* Перерисовка контура и перекраска граней графа */
int regraph(Display* dpy, Window win, GC gc, int NoFillFace) 
{
    int i;                                                  /* счетчик вершин и граней */
    /* Раскраска всех или 0 внутренних граней */
    for(i = NoFillFace; i < NFACE; i++) 
    {
        XSetForeground(dpy, gc, palette[face[i].tone]);     /* цвет грани */
        XFillPolygon(dpy, win, gc, face[i].top, face[i].Cn,
                                            Convex, CoordModeOrigin);
    } /* for face */
/* Перерисовка всех ребер и вершин */
    XSetForeground(dpy, gc, palette[NTONE]);                /* −> Black */
    XDrawSegments(dpy, win, gc, edge, NEDGE);
    for(i = 0; i< NVERT; i++)
    XFillArc(dpy, win, gc, vertex[i].x - (VDOT >> 1), 
                                            vertex[i].y - (VDOT >> 1), 
                                        VDOT, VDOT, 0, (64*360));
    return(0);
} /* regraph */

int reface(Display* dpy, Window win, GC gc, int f) 
{
    int i;                                                  /* счетчик вершин грани */
    if(f == NFACE)                                          /* перекраска внешней грани */
    return(reset(dpy, win, f));
    XSetForeground(dpy, gc, palette[face[f].tone]);
    XFillPolygon(dpy, win, gc, face[f].top, face[f].Cn,
                        Convex, CoordModeOrigin);           /* Перекраска */
    XFlush(dpy);                                            /* внутренней грани */

    /* Перерисовка контура грани */
    XSetForeground(dpy, gc, palette[NTONE]);                /* −> Black*/
    XDrawLines(dpy, win, gc, face[f].top, face[f].Cn + 1,
                        CoordModeOrigin);                   /* перерисовка ребер */
    for(i = 0; i< face[f].Cn; i++)                          /* перерисовка вершин */
    XFillArc(dpy, win, gc, face[f].top[i].x - (VDOT/2), 
                                            face[f].top[i].y - (VDOT/2),
                                        VDOT, VDOT, 0, (64*360));
    return(0);
} /* reface */

/* Перезагрузка раскраски граней */
int reset(Display* dpy, Window win, int FillFace) 
{
    int f = FillFace;                                       /* индекс грани */
    /* Сохранить или Установить цвета внутренних граней по фону внешней грани*/
    for(f ; f < NFACE; f++)                                 
        face[f].tone = DEFTONE;  
    /* Установить фон окна и инициировать Expose */
    XSetWindowBackground(dpy, win, palette[face[f].tone]);
    XClearArea(dpy, win, 0, 0, 0, 0, True);                 /* −> Expose */
    return(f);
} /* reset */

int rekey(Display* dpy, Window win, GC gc, XEvent* ev) 
{
    KeySym sym;                                      /* Key symbol code */
    sym = XkbKeycodeToKeysym(dpy, ev->xkey.keycode, 0, 0);
    if(sym == XK_F10)                    /* Press F10 for programm exit */
    return(10);         /* exit return for event dispatcher in main() */
    if((sym == XK_l) && (ev->xkey.state & ControlMask))    /* Press C-L */
    reset(dpy, win, NFACE);               /* to Refresh graph display */
    if(sym == XK_Escape)    /* Press Escape to redraw default face tone */ 
    reset(dpy, win, 0);
    return(0);        /* continue return for event dispatcher in main() */
} /* rekey */
