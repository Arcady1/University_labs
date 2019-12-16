//Гусаров Аркадий РК6-13Б 1 курс. Программа ...
// Запись производится не как в стек!!!; слова добавляются в начало списка!!!

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

int errors(FILE *file, int args, char *argv[])
{
    if( file == NULL )
    {
        printf("FILE NOT FOUND\n");
        exit (20);
    }
    
    else if( args > 2 )
    {
        printf("TOO MANY ARGUMENTS\n");
        exit (21);
    }
    
    return (10);
}

List* search(char buff[])
{
    List *pf = first;                               // создаю указатель на first
    
    while( pf != NULL )
    {
        if( strcmp(pf -> str, buff) == 0 )          // лексикографическое сравнивание слов
        {
            pf -> count += 1;
            
            return first;
        }
        else
            pf = pf -> next;
    }
    
    create(buff);
}

List* create(char buff[])
{
    int length;
    char *pw;
    
    length = strlen(buff);                                  // длина введенного слова
    
    pw = (char *) malloc( length * sizeof(char) + 1 );      // выделили память под слово (получили указатель)
    
    if( pw == NULL )                                        // если кончилась память, то выходим
        exit(10);

    strcpy(pw, buff);                                       // в выделенную память скоипровали слово
    
    List *pl = (List *) malloc( sizeof(List) );             // выделили память под следующий узел (получили указатель)
    
    if( pl == NULL )
        exit(11);
    
    pl -> str = pw;                     // внесли слово в  узел
    pl -> count += 1;
    pl -> next = first;                 // объединили узел со списком
    first = pl;                         // сохранили полученный список в first
    
    return first;
}

FILE* output(FILE *file)
{
    List *ph;
	
    while( first != NULL )
    {
        fprintf(file, "%s\t%d\n", first -> str, first -> count);
        
        free(first -> str);
        
        ph = first -> next;
        free(first);
        
        first = ph;
    }
    
    return file;
}
