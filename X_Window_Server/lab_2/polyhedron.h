#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef XPoint XVertex;                             /* Структура вершины */
typedef XSegment XEdge;                             /* Структура ребра */

typedef struct {                                    /* Структура грани */
  XPoint *top;                                      /* Адрес набора вершин */
  int Cn;                                           /* Число вершин */
  int tone;                                         /* Номер цвета */
  Region zone;                                      /* Региональная зона */
}XFace;

typedef struct {                                    /* Структура многоугольного графа */
  XVertex* vertex;                                  /* Адрес массива вершин */
  XEdge* edge;                                      /* Адрес массива ребер */
  XFace* face;                                      /* Адрес массива граней */
} XPolyGraph;

#define MB0  7                                      /* 7-угольная внешняя грань */
#define NF4  7                                      /* 7 4-угольные внутренние грани */
#define NF7  1                                      /* 1 7-угольные внутренние грани */
#define NFACE (NF4+NF7)                             /* (NF4+NF7) - число граней*/
#define NEDGE ((4*NF4 + 7*NF7 + MB0)/2)             /* ((4*NF4 + 7*NF7+ MB0)/2)- число ребер */
#define NVERT (NEDGE-(NFACE+1)+2)                   /* число вершин */
#define NTONE      4                                /* число цветов граней графа */
#define DEFTONE 0                                   /* номер цвета грани по умолчанию */
#define VDOT        8                               /* диаметр вершин графа */
#define EWIDTH   2                                  /* толщина ребер графа (<VDOT) */
#define NUNIT    17                                /* диапазон градуировка схемы  %8=0 */

/*Геометрический модуль (cub1) */
int assoc(XPolyGraph*);
GC congraph(Display*);
Window wingraph(Display*);
int colorite(Display*);
int regraph(Display*, Window, GC, int);
int reset(Display*, Window, int);
int reface(Display*, Window, GC, int);
/*Дисплейный модуль (cub2) */
int relink(XPolyGraph*);
int retrace();
int resize(unsigned, unsigned);
int rescale(unsigned, unsigned);
int rebuild();
int reconf(unsigned, unsigned);
int zotone(int, int);
/*Контрольный модуль (cub3) */
int rekey(Display*, Window, GC, XEvent*);
int dispatch(Display*, Window, GC);
int main(int, char* argv[]);

