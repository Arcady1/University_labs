//Гусаров Аркадий РК6-13Б 1 курс. Программа вводит из файла, имя которого определяется в командной строке, числа и помещает их в линейный односвязный список. Затем удаляет из списка все элементы, числа в которых больше 10. Числа из результирующего списка вывести в стандартный поток вывода.

#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    int num;
    struct List *next;
} List;

List *first = NULL;                     // создаем указатель на первый узел списка
List *pl = NULL;                        // создаем указатель на последний узел списка

void fill_in(int);                      // ф-ия принимает считанное из файла число и вносит его в список
void search(void);                      // ф-ия ищет числа, которые > 10, и удаляет их из списка
void output(void);                      // ф-ия выводит измененный список
int errors(int, char *[], FILE *);      // ф-ия принимает argc (кол-во аргументов), их имена, значение, которое вернула ф-ия fopen(); возвращает код ошибки

int main(int argc, char* argv[])
{
    int digit, num_f;
    List *pf;
    
    pf = (List *) malloc( sizeof(List) );           // создаем и заполняем новый узел; first становится указателем на него
    
    pf -> num = 100;
    pf -> next = NULL;
    first = pf;
    
    pl = first;                                     // последний узел сначала указывает на первый
    
    FILE *file;    
    file = fopen(argv[1], "r");
    
    errors(argc, argv, file);
    
    while( fscanf(file, "%d", &num_f ) != EOF )     // считываем числа из файла
    {
        digit = num_f;
        
        fill_in(digit);
    }
    
    fclose(file);
    
    search();
    output();
    
    return 0;
}

int errors(int argc, char *argv[], FILE *file)
{
    int check;
    
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
    
    if( fscanf(file, "%d", &check ) == EOF )    // проверка, что файл не пустой
    {
        printf("ERROR: FILE IS EMPTY\n");
        exit (104);
    }
    
    if( argc > 2 )                              // проверка, что аргументов не более 2-х
    {
        printf("ERROR: TOO MANY ARGUMENTS\n");
        exit (103);
    }
    
    return 10;
}

void fill_in(int digit)
{
    List *pw;
    
    pw = (List *) malloc( sizeof(List) );           // создаем новый узел и заполняем его
    
    pw -> num = digit;
    pw -> next = NULL;
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
    
    while( first -> next != NULL )
    {
        printf("%d\n", first -> num);
        
        pl = pl -> next;
        
        free(first);
        
        first = pl;
    }
    
    printf("%d\n", first -> num);
    
    free(first);
}
