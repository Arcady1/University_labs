// Гусаров Аркадий РК6-13Б 1 курс. Разработать программу, которая запоминает в двумерном массиве, имеющем 5 строк и 8 столбцов, числа от –5 до 5, получаемые случайным образом, а затем располагает их в порядке возрастания в строке. Поменять в отсортированном массиве все отрицательные элементы на их абсолютную величину.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define S 5
#define C 8

void frame(void);			// ф-ия выводит верхнюю рамку таблицы
void show_arr(int [][C]);		// ф-ия принимает массив arr[S][C] и выводит его
void fill_in(int [][C]);		// ф-ия принимает массив arr[S][C] и заполняет его случайными числами от -5 до 5
void sort(int [][C]);			// ф-ия принимает массив arr[S][C] и сортирует эл-ты каждой строки в порядке возрастания
void change_abs(int [][C]);		// ф-ия принимает массив arr[S][C] и заменяет отрицательные числа в строке на их абсолютную величину

int main()
{
	int arr[S][C];

	fill_in(arr);
	show_arr(arr);

	sort(arr);
	show_arr(arr);

	change_abs(arr);
	show_arr(arr);

	return 0;
}

void fill_in(int arr[][C])
{
	int i, j, a;

	srand(time(NULL));				// указываем сид, чтобы каждый раз генерировались новые числа

	a = -5;

	for(i = 0; i < S; i++)
	{
		for(j = 0; j < C; j++)
		{
			arr[i][j] = 0;
			arr[i][j] = a + (rand() % 11);
		}
	}
}

void sort(int arr[][C])					// сортировка методом пузырька
{
	int i, j, k, x;

	for(k = 0; k < S; k++)				// движемся по строкам
	{	
		for(i = 0; i < C - 1; i++)		// фиксируем 1-ый эл-т
		{
			for(j = i + 1; j < C; j++)	// перебираем последующие эл-ты в строке
			{
				if(arr[k][i] > arr[k][j])
				{	
					x = arr[k][j];
					arr[k][j] = arr[k][i];
					arr[k][i] = x;
				}
			}
			j = 0;
		}
		i = 0;
	}
}

void change_abs(int arr[][C])
{
	int i, j;

	for(i = 0; i < S; i++)
	{
		for(j = 0; j < C; j++)
		{
			if(arr[i][j] < 0)
				arr[i][j] = abs(arr[i][j]);
		}
		j = 0;
	}
}

void show_arr(int arr[][C])
{
	int i, j;

	frame();
	
	for(i = 0; i < S; i++)
	{
		printf("%d    |\t", i + 1);

		for(j = 0; j < C; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void frame(void)
{
	int i;

	printf("     |\t");

	for(i = 0; i < C; i++)
	{
		printf("%d\t", i + 1);
	}

	printf("\n");
	printf("------------------------------------------------------------------");
	printf("\n");
}
