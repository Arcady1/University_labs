//Гусаров Аркадий РК6-13Б 1 курс. Программа определяет и выводит на экран количество очков, набранных каждой футбольной командой, максимальное число очков, все команды, набравшие максимальное число очков

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 8

void main_diag(int [][N]);                // ф-ия принимает массив arr[][N] и заполняет главную диагональ матрицы 0
void high_low(int [][N]);                 // ф-ия принимает массив arr[][N] и заполняет матрицу над главной диагональю и под ней
void num_strings(int [][N]);		  // ф-ия принимает массив arr[][N], нумерует его строки и выводит
void score_(int [][N]);                   // ф-ия принимает массив arr[][N] и считает кол-во очков у каждой команды
void answer_1(int []);                    // ф-ия принимает массив score[] и выводит кол-во очков у каждой команды
void answer_2(int []);                    // ф-ия принимает массив score[] и выводит команды, набравшие максимальное кол-во очков
void frame(void);                         // ф-ия создает верхнюю рамку таблицы

int main()
{
    int arr[N][N];
    
    frame();
    
    main_diag(arr);
    
    high_low(arr);
    
    num_strings(arr);
    
    score_(arr);
    
    return 0;
}

void main_diag(int arr[][N])
{
    int i;
    
    for(i = 0; i < N; i++)
    {
        arr[i][i] = 0;
    }
}

void high_low(int arr[][N])
{
    int i, j, a;
    
    srand(time(NULL));                          // указываем сид, чтобы каждый раз числа были случайными
    
    for(i = 0; i < N - 1; i++)
    {
        for(j = i + 1; j < N; j++)
        {
            a = rand() % 3;                     // случайное число от 0 до 2
            
            if((a == 1))
            {
                arr[i][j] = 1;
                arr[j][i] = 1;
            }
                
            else if(a == 0)
            {
                arr[i][j] = a;
                arr[j][i] = 3;
            }
            
            else if(a == 2)
            {
                arr[i][j] = 3;
                arr[j][i] = 0;
            }
        }
    }
}

void num_strings(int arr[][N])
{
    int i, j;
    
    for(i = 0; i < N; i++)
    {
        printf("%d\t| ", i + 1);              // нумерация строк
        
        for(j = 0; j < N; j++)                // вывод обработанного массива
        {
            printf("%d\t", arr[i][j]);
        }
        
        printf("\n");
        
        j = 0;
    }
}

void score_(int arr[][N])
{
    int score[N], i, j;                      // score[N]: номер комманды = индекс + 1; эл-т - кол-во очков
    
    for(i = 0; i < N; i++)
    {
        score[i] = 0;                        // заполняем i эл-ты 0
        
        for(j = 0; j < N; j++)
        {
            score[i] += arr[i][j];           // вносим кол-во очков, которое набрала каждая команда
        }
        
        j = 0;
    }    
    
    printf("\n");    
    
    answer_1(score);
    
    answer_2(score);
}

void answer_1(int score[])
{
    int i;
    
    for(i = 0; i < N; i++)
    {
        printf("Кол-во очков у команды №%d: %d\n", i + 1, score[i]);
    }
}

void answer_2(int score[])
{
    int i, x;
    
    x = 0;
    
    for(i = 0; i < N; i++)
    {
        if(score[i] > x)
        {
            x = score[i];
        }
    }
    
    printf("\n");
    
    for(i = 0; i < N; i++)
    {
        if(score[i] == x)
        {
            printf("Команда №%d набрала максимальное кол-во очков: %d\n", i + 1, x);
        }
    }
}

void frame(void)
{
	int i, j;
	
	printf("\t| ");
	
	for(i = 1; i < N + 1; i++)
	{
		printf("%d\t", i);
	}
	
    printf("\n");
	
	for(j = 0; j < i; j++)
	{
		printf("--------");
	}
	
	printf("\n");
}