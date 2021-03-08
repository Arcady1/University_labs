#include "polyhedron.h"

static XVertex vertex[NVERT];               /* массив вершин */
static XEdge edge[NEDGE];                   /* массив ребер */
static XFace face[(NFACE+1)];               /* массив граней */

static XPoint face4[NF4][(4+1)];
static XPoint face7[NF7][(7+1)];

static XPoint scale;                        /*структура масштаба по Х и Y */

/* Модельная ассоциация структуры полиграфа */

int assoc(XPolyGraph* pg) 
{
    pg->vertex = vertex;                    /* адресация массива вершин */
    pg->edge = edge;                        /* адресация массива ребер */
    pg->face = face;                        /* адресация массива граней */
    retrace();                              /* трассировка граней */
    return(0);
}                                           /* assoc */

int retrace() {
int i=0;                                    /* сквозной индекс разноугольных граней */
int j;                                      /* индекс равноугольных граней */
for(j = 0; j<NF4; j++, i++)                 /* 4-угольная трассировка */         
{  
  face[i].top = face4[j];                   /* адрес массива вершин */
  face[i].Cn = 4;                           /* число вершин грани=4 */
  face[i].tone = DEFTONE;                   /* цветной индекс грани */
  face[i].zone = XCreateRegion();           /* пустой регион */
} /* face4 */
for(j = 0; j < NF7; j++, i++)               /* для m>3 */
{
  face[i].top = face7[j];                   /* адрес массива вершин */
  face[i].Cn = 7;                           /* число вершин грани=7 */
  face[i].tone = DEFTONE;                   /* цветной индекс грани */
  face[i].zone = XCreateRegion();           /* пустой регион */
}
face[i].tone = DEFTONE;                     /* цвет внешней грани */
return(0);
} /* retrace */

int rebuild() {
static XPoint vconf[] = {                   /* Конфигурация вершин в схеме куба*/
  {2, 6}, {5, 3}, {11, 3}, {14, 6}, {14, 12}, {8, 15}, {2, 12}, {7, 7}, {9, 7}, {10, 8}, {10, 10}, {8, 11}, {6, 10}, {6, 8}
}; /* vconf */
static int fconf4[NF4][(4+1)] = {           /* Циклические индексы вершин для 4-угольных граней куба */
  {0,1, 7, 13, 0},                              
  {1, 2, 8, 7, 1},             
  {2, 3, 9, 8, 2},
  {3, 4, 10, 9, 3},
  {4, 5, 11, 10, 4},
  {5, 6, 12, 11, 5},
  {6, 0, 13, 12, 6}
}; /* fconf4 */
static int fconf7[NF7][(7+1)] = {           /* Циклические индексы вершин для 7-угольных граней куба */
  {7, 8, 9, 10, 11, 12, 13, 7}
}; /* fconf7 */
static int econf[NEDGE][2] = {              /* Пары вершин ребер: */
       {0, 1}, {0, 13},              /* инцидентные V0 */
       {1, 2}, {1, 7},                      /* инцидентные V1 */
       {2, 3}, {2, 8},                      /* инцидентные V2 */
       {3, 4}, {3, 9},                     /* инцидентные V3 */
       {4, 5}, {4, 10},                     /* инцидентные V4 */
       {5, 6}, {5, 11},                     /* инцидентные V5 */
       {6, 0}, {6, 12},                     /* инцидентные V6 */
       {7, 8},                              /* инцидентные V7 */
       {8, 9},                             /* инцидентные V8 */
       {9, 10},                             /* инцидентные V9 */
       {10, 11},                            /* инцидентные V10 */
       {11, 12},                            /* инцидентные V11 */
       {12, 13},                   /* инцидентные V12 */
       {13, 7}                   /* инцидентные V13 */
}; /* edge */
int i, j;                                   /* индексы вершин, ребер и граней */
for(i = 0; i < NVERT; i++) {                /* Расчет оконных координат вершин  */
  vertex[i].x = scale.x * vconf[i].x;             
  vertex[i].y = scale.y * vconf[i].y;                   
} /* for-vertex */
for(i = 0; i < NEDGE; i++) {                /* Фиксировать оконные координаты пар вершин всех ребер */
  edge[i].x1 = vertex[econf[i][0]].x;          
  edge[i].y1 = vertex[econf[i][0]].y;           
  edge[i].x2 = vertex[econf[i][1]].x; ;            
  edge[i].y2 = vertex[econf[i][1]].y;
}
for(i = 0; i < NF4; i++)                    /* Фиксировать оконные координаты вершин 4-угольных граней */
  for(j = 0; j < (4+1); j++) {         
    face4[i][j].x = vertex[fconf4[i][j]].x;      
    face4[i][j].y = vertex[fconf4[i][j]].y;              
  }
for(i = 0; i < NF7; i++)                    /* Фиксировать оконные координаты вершин 7-угольных граней */
  for(j = 0; j < (7+1); j++) {         
    face7[i][j].x = vertex[fconf7[i][j]].x;      
    face7[i][j].y = vertex[fconf7[i][j]].y;              
  }
return(0);
} /* rebuild */

/* Контроль масштаба изображения */
int rescale(unsigned w, unsigned h) {
int x, y;                                   /* коэффициенты масштабирования по x и y */
x = w / NUNIT; y = h / NUNIT;               /* пересчет масштаба */
if((scale.x == x) && (scale.y == y))
  return(0);                                /* код сохранения масштаба */
scale.x = x; scale.y = y;                   /* запомнить масштаб */
return(NFACE);                              /*  код изменения масштаба */
} /* rescale */

/* Контроль изменения размеров окна */
int resize(unsigned w, unsigned h) {
static XRectangle bak = {0, 0, 0, 0 };      /* прошлые размеры */
if((bak.width == w) && (bak.height == h))
  return(0);                                /* код сохранения размеров окна */
bak.width = w; bak.height = h;              /* запомнить размеры */
return(NFACE);                              /* код изменения размеров окна */
} /* resize */

/* Реконфигурация графа */
int reconf(unsigned w, unsigned h) {
if(resize(w, h) == 0)                       /* Габаритный контроль */
  return(0);
if(rescale(w, h) != 0)                      /* Контроль масштаба */
  rebuild();                                /* Перестройка геометрии графа */
return(NFACE);
} /* reconf */

int zotone(int x, int y) {
static XPoint bak = {0, 0};                 /* прошлый масштаб */
int f = 0;                                  /* индекс грани */
if((bak.x == scale.x) && (bak.y == scale.y))/* Контроль */
  f = NFACE;                                /* изменений масштаба изображения */
for( ; f < NFACE; f++) {                    /* Перестройка регионов граней */
  XDestroyRegion(face[f].zone);
  face[f].zone = XPolygonRegion(face[f].top, face[f].Cn, 0);
} /* for */
bak.x = scale.x; bak.y = scale.y;           /* запомнить масштаб */
for(f = 0; f < NFACE; f++)                  /* поиск грани по точке внутри */
  if(XPointInRegion(face[f].zone, x, y) == True)
     break;
face[f].tone = (face[f].tone + 1) % NTONE;  /* новый цвет */
return(f);                                  /* возврат индекса грани для перекраски */
} /* zotone */

