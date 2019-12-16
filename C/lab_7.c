// Гусаров Аркадий РК6-13Б 1 курс. Программа вводит со стандартного потока ввода множество символов, ограниченное вводом признака конца файла (EOF). Определяет и выводит на экран число введенных символов и строк и др. (см. ниже)

#include <stdio.h>
#include <stdlib.h>

void output(int, int, int, int, int, int, int);
void full_counting(char [], int);

int main()
{
    char arr[2];
    int count_of_words = -1;
    
    arr[0] = ' ';
    
    if(arr[0] == EOF)                   // если сразу нажали Ctrl + D -- выход с кодом 0
        exit(0);
    
    full_counting(arr, count_of_words);
}

void full_counting(char arr[], int count_of_words)
{
    int count_of_symbols = -1;
    int count_of_strings = 0;
    
    int count_of_control_characters = -1;
    int count_of_latin = 0;
    int count_of_digits = 0;
    int count_of_punct = 0;
    
    while (arr[0] != EOF)
        {
            arr[1] = getchar();
            
            ++count_of_symbols;                                                     // кол-во введенных символов
            
            if( ((arr[0] == ' ') | (arr[0] == '\n') | (arr[0] == '\t')) )
            {
                ++count_of_control_characters;                                      // кол-во управляющих символов
                
                if ( (arr[1] != ' ') & (arr[1] != '\n') & (arr[1] != '\t') )        // если последовательность: символ-разделитель -- буква, тогда у нас слово
                    ++count_of_words;                                               // кол-во введенных слов
            }
             
            if(arr[0] == '\n')
                ++count_of_strings;                                                 // кол-во введенных строк
            
            else if( ((arr[0] >= 'a') & (arr[0] <= 'z')) |
                     ((arr[0] >= 'A') & (arr[0] <= 'Z')) )
                ++count_of_latin;                                                   // кол-во латинских букв
                
            else if( (arr[0] >= '0') & (arr[0] <= '9') )
                ++count_of_digits;                                                  // кол-во цифр
                
            else if( ((arr[0] >= '!') & (arr[0] <= '/')) | 
                     ((arr[0] >= ':') & (arr[0] <= '@')) |
                     ((arr[0] >= '[') & (arr[0] <= '`')) |
                     ((arr[0] >= '{') & (arr[0] <= '~')) )
                ++count_of_punct;                                                   // кол-во знаков препинания
            
            arr[0] = arr[1];
        }
        
        output(count_of_symbols, count_of_strings, count_of_words, count_of_control_characters, count_of_latin, count_of_digits, count_of_punct);
}

void output(int count_sy, int count_str, int count_w, int count_of_control_characters, int count_of_latin, int count_of_digits, int count_of_punct)
{
    printf("\nКол-во введенных символов: %d", count_sy);
    
    printf("\nКол-во введенных слов: %d", count_w);
        
    printf("\nКол-во введенных строк: %d", count_str);
    
    printf("\nКол-во управляющих символов: %d", count_of_control_characters);
    
    printf("\nКол-во латинских букв: %d", count_of_latin);
    
    printf("\nКол-во цифр: %d", count_of_digits);
    
    printf("\nКол-во знаков препинания: %d\n", count_of_punct);
}
