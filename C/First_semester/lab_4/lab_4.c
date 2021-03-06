﻿// Гусаров Аркадий РК6-13Б 1 курс. Программа находит предел отношения двух последовательных чисел ряда Фибоначчи с заданной точностью.

#include <stdio.h>
#include <math.h>
#define EPS 0.01

double search();
double pogr(double);

int main()
{
    double x = search();

    pogr(x);
}

double search(void)		// ф-ия выводит эл-ты последовательности, предел, номер итерации; возвращает последнее отношение эл-ов
{
    double V, a_1, a_2, a_3, x;
    int k;
     
    a_1 = 1.;
    a_2 = 1.;
    a_3 = 2.;
    V = 2.;
    k = 1;
    
    printf("%.0f, %.0f, %.0f, V = %f, k = %d\n----------------------------------------\n", a_1, a_2, a_3, V, k);
    
    while(fabs((a_2/a_1)-(V)) > EPS)		// считаем разность отношений двух последовательных чисел ряда Фибоначчи
    {
        a_1 = a_2;        
        a_2 = a_3;
        a_3 = a_1 + a_2;
        
	V = a_3/a_2;

        printf("%.0f, %.0f, %.0f, V = %.12lf, k = ", a_1, a_2, a_3, V);      
        
        k ++;
        
        printf("%d\n----------------------------------------\n", k);
    }

    x = a_3/a_2;

    return x;
}

double pogr(double x)		// ф-ия считает и выводит абсолютную погрешность и относительную
{
    double eps_pogr, otn_pogr;

    eps_pogr = fabs(x - ((sqrt(5)+1)/2));
    otn_pogr = eps_pogr / ((sqrt(5)+1)/2);

    printf("Абсолютная погрешность = %.12lf\nОтносительная погрешность = %.12lf\n", eps_pogr, otn_pogr);
}
