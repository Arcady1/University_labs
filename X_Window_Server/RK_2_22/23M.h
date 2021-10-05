#define DELAY (1 << 14)

/*структура стрелы*/
typedef struct
{
	int x;	//координаты
	int y;	//центра
	int R;	//текуий радиус
	int dR; //частота
	int w;	//фазовая скорость
	int n;	
	int m;
} XArrow;

/* Spiral Implementation function */

int configure_arrow(XEvent *, XArrow *, int, int);			   /* задание точек стрелки */
int redraw(XEvent *, GC, GC, XArrow *, int, int);			   /* перерисовка потерянных фрагментов окна */
int draw_arrow(Display *, Window, GC, GC, XArrow *, int, int); /*отрисовка стрелы в окне*/
int key_check(XEvent *);									   /* ответ на собития нажатия клавиш */
int maxi(int, int, int, int);
int side(int, int, int, int);
