#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 256

typedef struct Word {               // typedef - чтобы указать, что создан новый тип (не нужно будет писать struct)
    char *str;                      // указатель на введенное слово
    int count;                      // кол-во повторений слова
    struct Word *next;              // указатель на следующий узел списка
} List;                             // задаем имя списка

List *first = NULL;                 // first - указатель на узел

int errors(FILE *, int, char *[]);  // ф-ия принимает имя файла, кол-во введенных аргументов, имена аргументов
List* search(char []);              // ф-ия принимает введенное слово, проверят на повторения; возвращает список first
List* create(char []);              // ф-ия принимает буфер buff[] и создает новый узел с новым словом; возвращает List
FILE* output(FILE *);               // ф-ия принимает имя файла, заполняет его и возвращает

int main(int args, char *argv[])
{    
    FILE *file;

    file = fopen(argv[args - 1], "w");
    
    errors(file, args, argv);
    
    char buff[SIZE], c;
    int index_w, cut;
	
    index_w = 0;
    cut = 1;
	
    while( (c = getchar()) != EOF )
    {
        if( (c >= 'a') & (c <= 'z') |
            (c >= 'A') & (c <= 'Z') )
        {
                buff[index_w] = c;
                ++index_w;
                cut = 0;                                                        // счетчик символов-разделителей
        }
        else if( ((c == ' ') | (c == '\t') | (c == '\n')) & (cut == 0) )        // получили слово
        {
            buff[index_w] = '\0';
            
            search(buff);
            
            index_w = 0;                                                        // заполняем буфер с 0-го эл-та
            ++cut;
        }
    }
	
    output(file);
    
    fclose(file);
    
    return 0;
}
