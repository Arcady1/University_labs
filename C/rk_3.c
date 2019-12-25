//Гусаров Аркадий РК6-13Б 1 курс. Программа вводит из файла, имя которого определяется в командной строке, числа и помещает их в линейный односвязный список. Затем удаляет из списка все элементы, числа в которых больше 10. Числа из результирующего списка вывести в стандартный поток вывода.

#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    int num;
    struct List *next;
} List;

List *first = NULL;                     // создаем указатель на первый узел списка
List *pl = NULL;                        // создаем указатель который сдвигается в конец списка
List *pend = NULL;                      // создаем указатель на последний узел списка

void fill_in(int);                      // ф-ия принимает считанное из файла число и вносит его в список
void search(void);                      // ф-ия ищет числа, которые > 10, и удаляет их из списка
void output(void);                      // ф-ия выводит измененный список
void errors(int, char *[], FILE *);     // ф-ия принимает argc (кол-во аргументов), их имена, значение, которое вернула ф-ия fopen(); возвращает код ошибки

int main(int argc, char* argv[])
{
    int num_f;
    FILE *file;    
    
    file = fopen(argv[1], "r");
    
    errors(argc, argv, file);
    
    while( fscanf(file, "%d", &num_f ) != EOF )     // считываем числа из файла
        fill_in(num_f);
    
    fclose(file);
    
    pl -> next = pend;
    
    search();
    output();
    
    return 0;
}

void errors(int argc, char *argv[], FILE *file)
{
    if( argc > 2 )                              // проверка, что аргументов не более 2-х
    {
        printf("ERROR: TOO MANY ARGUMENTS\n");
        exit (103);
    }
    if( argc < 2 )                              // проверка, что аргументов не менее 2-х
    {
        printf("ERROR: NO ARGUMENTS\n");
        exit (102);
    }
    
    if( file == NULL )                          // проверка, что файл существует
    {
        printf("ERROR: NO SUCH FILE\n");
        exit (101);
    }
}

void fill_in(int digit)
{    
    List *pw;
    
    pw = (List *) malloc( sizeof(List) );           // создаем новый узел и заполняем его
    
    if( pw == NULL )                                // если кончилась память, то выходим
        exit(10);
    
    pw -> num = digit;
    pw -> next = NULL;
    
    if( first == NULL )
    {
        first = pw;
        pl = first;
    }        
    
    pl -> next = pw;
    pl = pw;                                        // pl сдвигается в конец списка
}

void search(void)
{
    List *pf, *pb, *pn;
    
    pf = first;                                     // pf - указател на первый элемент списка
    
    while( pf != NULL )
    {
        if( (pf -> num) > 10 )
        {
            if( (pf -> next) == (first -> next) )   // сдвиг первого узла, если первое число > 10
            {
                first = first -> next;
                
                free(pf);
                
                pf = first;
            }
            else
            {
                pn = pf -> next;
                
                free(pf);
                
                pf = pn;
                pb -> next = pf;
            }
        }
        else
        {
            pb = pf;
            pf = pf -> next;
        }
    }
}

void output(void)
{   
    pl = first;
    
    while( first != NULL )
    {
        printf("%d\n", first -> num);
        
        pl = pl -> next;
        
        free(first);
        
        first = pl;
    }
}
