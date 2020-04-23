/* Гусаров Аркадий РК6-23Б 1 курс. Программа для определения среднего размера строки в заданном текстовом файле и количества непустых строк, длина которых не меньше средней величины.
Пример ввода: ./a.out file.txt > out.txt  2>&1
file.txt - файл, откуда считываются данные, '>' - стандартный вывод производится в файл out.txt, '2>&1': '2>' - вывод потока ошибок (stderr), '&1' - в тот же самый файл */

#include <stdio.h>
#include <stdlib.h>

int Strings_number(FILE*);                              // ф-ия подсчета кол-ва строк в файле; принимает файл, возвращает кол-во строк
void Array_fill_in(FILE*, int, int*);                   // ф-ия заполнения массива 'array' числами - кол-во символов в строке; принимает 'file', кол-во строк, указатель на массив 'array', ничего не возвращает, т.к. изменяет массив через указатель
int Average_length(int, int*);                          // ф-ия подсчета средней длины строки; принимает кол-во строк и указатель на массив 'array', возвращает среднюю длину строки
int Search_count(int, int*);                            // ф-ия подсчета непустых строк, длина которых >= средней величины; принимает среднюю длину строки и указатель на массив 'array'
void Errors(int);                                       // ф-ия проверки на ошибки при передаче аргументов командной строки

int main(int argc, char const *argv[])
{
    FILE *file;                                         // указатель на файл
    int strings_num;                                    // кол-во строк в файле
    int* array;                                         // указатель на выделенную память (размер = кол-во строк + 1)
    int aver_len;                                       // средняя длина строки
    int num_more_aver;                                  // кол-во непустых строк, длина которых >= средней величины

    Errors(argc);

    file = fopen(argv[1], "r");                         // 'r' - только для чтения

    if (file == NULL)
    {
        printf("Ошибка при обработке файла\n");         // если не удалось открыть файл - ошибка
        
        return 1;
    }

    strings_num = Strings_number(file);
    fseek(file, 0, SEEK_SET);                           // изменить позицию на 0 байт относительно начала файла; 'SEEK_SET' - начало файла

    array = (int*) malloc(strings_num * sizeof(int) + 1);

    Array_fill_in(file, strings_num, array);
    fclose(file);                                       // файл закрыт

    aver_len = Average_length(strings_num, array);
    num_more_aver = Search_count(aver_len, array);

    free(array);                                        // очистил динамически выделенную память

    printf("Средняя длина строки: %d\n", aver_len);
    printf("Кол-во строк, длина которых не меньше средней величины: %d\n", num_more_aver);
    
    return 0;
}

int Strings_number(FILE* file)
{
    int str_count;
    char symbol;

    str_count = 0;

    while( (symbol = fgetc(file)) != EOF )              // подсчет кол-ва строк
    {
        if ( symbol == '\n' )
            str_count++;
    }

    return str_count;
}

void Array_fill_in(FILE* file, int strings_num, int* array)
{
    char c;
    int symb_num;
    int i;

    symb_num = 0;

    for (i = 0; i < strings_num; i++)
    {
        while( (c = fgetc(file)) != '\n' )
            symb_num++;
        
        array[i] = symb_num;

        symb_num = 0;
    }

    array[strings_num] = -10;
}

int Average_length(int strings_num, int* array)
{
    int aver_len;
    int i;
    int digit;

    digit = 0;

    for ( i = 0; array[i] != -10; i++ )
        digit += array[i];

    aver_len = digit / strings_num;

    return aver_len;
}

int Search_count(int aver_len, int* array)
{
    int num_more_aver;
    int i;

    num_more_aver = 0;

    for ( i = 0; array[i] != -10; i++ )
        if ( array[i] >= aver_len )
            num_more_aver++;  

    return num_more_aver;
}

void Errors(int argc)
{
    if ( argc != 2 )                                // проверка на кол-во аргументов (= 2)
    {
        printf("Ошибка при вводе аргументов\n");

        exit (1);
    }
}