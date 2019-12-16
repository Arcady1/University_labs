//Гусаров Аркадий РК6-13Б 1 курс. Программа выделяет память под строки (динамические массивы) и выводит их.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 256

void input(void);               // ф-ия ввода
void output(char *[]);          // ф-ия вывода, принимает массив указателей на введенные строки

int main()
{
    char c, buff[SIZE], *strings[SIZE];
    int i = 0, length = 0, num_of_str = 0;
    
    while( (c = getchar()) != EOF )
    {
        if( (c != ' ') & (c != '\t') )			// игнорируем пробелы и табуляцию
        {
            if( (c == '\n') )				// если '\n', новую строку записываем с 0-го элемента
            {
                buff[i] = '\0';
                i = 0;
                
                length = strlen(buff);			// считаем длину слова, чтобы выделить под него память
                
                strings[num_of_str] = (char *) malloc( length * sizeof(char) + 1 );     // num_of_str'ый эл-т массива указателей strings[] расширяем на длину введенной строки + 1 для '\0'
                strcpy( strings[num_of_str], buff );
    
                ++num_of_str;				// кол-во введенных строк - 1
            }
            else
            {
                buff[i] = c;
                ++i;
            }
        }
    }
    
    strings[num_of_str] = NULL;
    output(strings);
    
    return 0;
}

void output(char *strings[])
{
    int i;
    
    i = 0;
    
    while( strings[i] != NULL )
    {
        printf("%s\n", strings[i]);
        free(strings[i]);
        ++i;
    }
}
