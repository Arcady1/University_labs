// Гусаров Аркадий РК6-13Б 1 курс. Программа переводит десятичное вещественное число в новую систему счисления [2,16].

#include <stdio.h>
#include <math.h>

void int_treatment(int, int);			// ф-ия принимает целую часть введенного числа, сс; выводит целую часть в новой сс
void double_treatment(double, int, int);	// ф-ия принимает дробную часть введенного числа, сс, указанную точность; выводит дробную 
						// часть в новой сс
double input_a(void);				// ф-ия возвращает проверенное введенное число (исходное)
int input_cc(void);				// ф-ия возвращает проверенное введенное число (сс)
int input_eps(void);				// ф-ия возвращает проверенное введенное число (точность)

int main()
{
	double a, f;
	int i, cc, eps;

	a = input_a();
	cc = input_cc();
	eps = input_eps();

	if(a < 0)
	{
		printf("-");			// если число отрицательное, то выводим "-"; затем берем его по модулю
		a = fabs(a);
	}				
	    

	i = (int)a;				// берем целую часть от введенного числа
	f = (double)(a-i);			// проверяем, имеет ли введенное число дробную часть

	if(f == 0)				// если число целое, то обрабатывается только целая часть, иначе - каждая отдельно
	{
		int_treatment(i, cc);
		printf("\n");
	}

	else
	{
		int_treatment(i, cc);
		printf(".");
		double_treatment(f, cc, eps);
		printf("\n");
	}

	return 0;
}

void int_treatment(int i, int cc)
{
	int x, y, z, arr[20], k;		// создаем массив arr[], чтобы внести в него число в новой сс

	x = i / cc;
	y = i % cc;
	k = 1;
	arr[0] = y;

	for(k; x != 0; k++)
	{
		z = x / cc;			// посчитали целую часть от деления
		y = x - (cc*z);			// посчитали остаток
		arr[k] = y;			// внесли остаток в массив
		x = z;				// переприсвоили целую часть от деления
	}
	
	k--;					// k-- - чтобы не выводить последний незначащий ноль из массива

	for(k; k >= 0; k--)			// вывод элементов массива в обратном порядке
		printf("%x", arr[k]);
}

void double_treatment(double f, int cc, int eps)
{
	int k, x;

	k = 0;
	x = (int)f;

	for(k; k != eps; k++)
	{
		f *= cc;			// дробную часть числа на cc
		x = (int)f;			// выделяем целую часть; затем выводим ее
		f -= (int)f;			// оставляем дробную часть

		printf("%x", x);
	}
}

double input_a(void)
{
	double a;

	a = 0;

	while(a == 0)
	{
		printf("Введите число: ");

		while(scanf("%lf", &a) == 0)
		{
			printf("Введите число: ");
			while(getchar() != '\n');
		}
	}

	return a;
}

int input_cc(void)
{
    int cc;

    cc = 0;

    while((cc < 2) | (cc > 16))
    {
        printf("Введите основание системы счисления [2-16]: ");

        while(scanf("%d", &cc) == 0)
        {
            printf("Введите основание системы счисления [2-16]: ");
            while(getchar() != '\n');
        }
    }

    return cc;
}

int input_eps(void)
{
    int eps;

    eps = -1;

    while((eps < 0) | (eps > 20))
    {
        printf("Задайте точность (до 20 знаков после запятой): ");

        while(scanf("%d", &eps) == 0)
        {
            printf("Задайте точность (до 20 знаков после запятой): ");
            while(getchar() != '\n');
        }
    }

    return eps;
}
