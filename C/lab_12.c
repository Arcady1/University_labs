//Гусаров Аркадий РК6-13Б 1 курс. Программа читает из стандартного потока ввода слова и размещает их в односвязный список следующим образом: если слово встретилось первый раз, то для него добавляется новый элемент в конец списка. В противном случае в соответствующем элементе списка увеличивается счетчик слов.

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
List *pl = NULL;                    // создаем указатель который сдвигается в конец списка
List *pend = NULL;                  // создаем указатель на последний узел списка
List *pf = NULL;                    // создаем указатель, который будет перемещаться по списку во время поиска слова

int errors(FILE *, int, char *[]);  // ф-ия принимает имя файла, кол-во введенных аргументов, имена аргументов
List* search(char []);              // ф-ия принимает введенное слово, проверят на повторения
void create(char []);               // ф-ия принимает буфер buff[] и создает новый узел с новым словом
FILE* output(FILE *);               // ф-ия принимает имя файла, заполняет его и возвращает

int main(int args, char *argv[])
{    
    char buff[SIZE], c;
    int index_w, cut;
    FILE *file;

    file = fopen(argv[args - 1], "w");
    
    errors(file, args, argv);
	
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
    pf = first;                                     // создаю указатель на first
    
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

void create(char buff[])
{
    int length;
    char *pw;
    
    length = strlen(buff);                                  // длина введенного слова
    
    pw = (char *) malloc( length * sizeof(char) + 1 );      // выделили память под слово (получили указатель)
    
    if( pw == NULL )                                        // если кончилась память, то выходим
        exit(10);

    strcpy(pw, buff);                                       // в выделенную память скоипровали слово
    
    List *pn = (List *) malloc( sizeof(List) );             // выделили память под следующий узел (получили указатель)
    
    if( pn == NULL )
        exit(11);
    
    pn -> str = pw;                         // внесли слово в  узел
    pn -> count += 1;
    
    if( first == NULL )                     // смещаем указатель на первый узел
    {
        pl = first;
        first = pn;
        
        free(pl);
        
        pl = first;        
        pl -> next = pend;
    }

    else
    {
        pl -> next = pn;
        
        free(pf);
        
        pl = pn;        
        pl -> next = pend;
    }
}

FILE* output(FILE *file)
{
    pl = first;
    
    while( first != NULL )
    {
        fprintf(file, "%s\t%d\n", first -> str, first -> count);
        
        free(first -> str);
        
        pl = pl -> next;
        
        free(first);
        
        first = pl;
    }
	
    return file;
}
