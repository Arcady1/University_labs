// Гусаров Аркадий РК6-13Б 1 курс. Программа считает объём прямоугольного параллелепипеда.

#include <stdio.h>				//объявление директивы препроцессора

float input(float, float, float);		// предопределяем ф-ию
float VolumeValue(float, float, float);		// предопределяем ф-ию

int main()
{
	float a, b, h; 
	
	input(a, b, h);				// передаем в ф-ию переменные
	
	return 0;
}

float input(float a, float b, float h)
{
    printf("Введите стороны основания прямоугольного параллелепипеда:\n");
	printf("a = ");
	scanf("%f", &a);
	printf("b = ");
	scanf("%f", &b);
	printf("Введите высоту прямоугольного параллелепипеда:\n");
	printf("h = ");
	scanf("%f", &h);

	VolumeValue(a, b, h);
	
	return 0;
}

float VolumeValue(float a,float b,float h)
{
	float volume;
	
	volume = a*b*h;
	
	printf("Объём прямоугольного параллелепипеда = %.2f\n", volume);	//%.2f - оставляем два знака после запятой
	
	return 0;
}  
