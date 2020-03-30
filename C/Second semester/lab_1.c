#include <stdio.h>

void Average_length(FILE*);

int main(int argc, char const *argv[])
{
    FILE *file;                                 // указатель на файл

    file = fopen(argv[1], "r");                 // 'r' - только для чтения

    if (file == NULL)
    {
        printf("Error\n");                      // если не удалось открыть файл - ошибка

        return 1;
    }

    Average_length(file);





    fclose(file);                               // закрываю файл
    
    return 0;
}

void Average_length(FILE* file)
{
    int str_count;
    char symbol;
    char string[60];

    str_count = 0;

    while( (symbol = fgetc(file)) != EOF )              // Подсчет кол-ва строк
    {
        if ( symbol == '\n' )
            str_count++;
    }

    // while ( (fscanf(file, "%s", string)) != EOF )
    // {
    //     if ( string == '\n' )
    //     {
    //         a++;
    //     }
    // }
    

    printf("%d\n", str_count);


}