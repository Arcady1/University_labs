#include <stdio.h>
#include <stdlib.h>

int Strings_number(FILE*);                              // ф-ия подсчета кол-ва строк в файле; принимает файл, возвращает кол-во строк
void Array_fill_in(FILE*, int, int*);                   // ф-ия заполнение массива 'array' числами - кол-во символов в строке; принимает 'file', кол-во строк, указатель на массив 'array', ничего не возвращает, т.к. изменяет массив через указатель

int main(int argc, char const *argv[])
{
    FILE *file;                                         // указатель на файл
    int strings_num;                                    // кол-во строк в файле
    int* array;                                         // указатель на выделенную память (размер = кол-во строк + 1)
    int i;

    file = fopen(argv[1], "r");                         // 'r' - только для чтения

    if (file == NULL)
    {
        printf("Error\n");                              // если не удалось открыть файл - ошибка

        return 1;
    }

    strings_num = Strings_number(file);
    array = (int*) malloc(strings_num * sizeof(int) + 1);

    // Array_fill_in(file, strings_num, array);

    array[strings_num] = -10;

    for ( i = 0; array[i] != -10 ; i++ )
    {
        printf("[%d] Строка %d: %d\n", i, i + 1, array[i]);
    }

    


    fclose(file);                                       // файл закрыт

    printf("Кол-во строк: %d\n", strings_num);
    
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
    char symbol;
    int symb_num;
    int i;

    symb_num = 0;

    for ( i = 0; i < strings_num; i++ )
    {
        // printf("@\n");
        // while ( (symbol = fgetc(file)) != '\n' )
        // {
        //     if ( symbol != '\n' )
        //         symb_num++;
            
        //     else if ( symbol == '\n' )
        //         break;
        // }
        
        array[i] = i + 1;
    }

    array[strings_num - 1] = (int)('b');
    printf("Строк: %d\n", strings_num);
    printf("Последнее значение: %d\n", array[strings_num]);

    exit (100);
}

// printf("# %d\n", strings_num);