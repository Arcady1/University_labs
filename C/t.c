#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    int num;
    struct List *next;
} List;

List *first = NULL;  
List *pf = NULL;
List *pmin, *pmax;

void fill_in(int);
void searchMin(void);
void searchMax(void);
void change(void);
void output(void);
int errors(int, char *[], FILE *);

int main(int argc, char* argv[])
{
    int digit, number;
    
    FILE *file;    
    file = fopen(argv[1], "r");
    
    errors(argc, argv, file);
    
    while( fscanf(file, "%d", &number ) != EOF )     // считываем числа из файла
    {
        digit = number;
        
        fill_in(digit);
    }
    
    searchMin();
    searchMax();
    change();
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
    
    if( argc > 2 )                              // проверка, что аргументов не более 2-х
    {
        printf("ERROR: TOO MANY ARGUMENTS\n");
        exit (103);
    }
    
    if( file == NULL )                          // проверка, что файл существует
    {
        printf("ERROR: NO SUCH FILE\n");
        exit (101);
    }
    
    return 10;
}

void fill_in(int digit)
{
    List *pw;
    
    pw = (List *) malloc( sizeof(List) );           // создаем новый узел и заполняем его
    
    pw -> num = digit;
    pw -> next = first;
    first = pw;
}

void searchMin(void)
{
    List *pn;
    
    pf = first;
    
    int min, b;
    
    min = pf -> num;
    pn = pf -> next;
    b = pn -> num;
    
    pf = pn -> next;
    
    while(pf != NULL)
    {
        if( min > b )
        {
            min = b;

            pmin = pn;
            pn = pf;
            pf = pn -> next;
            
            b = pn -> num;
        }
        
        else
        {
            pn = pf;
            pf = pn -> next;
            
            b = pn -> num;
        }
    }
    
    if( min > b )
    {
        min = b;
        
        pmin = pn;
    }
}

void searchMax(void)
{
    List *pn;
    
    pf = first;
    
    int max, b;
    
    max = pf -> num;
    pn = pf -> next;
    b = pn -> num;
    
    pf = pn -> next;
    
    while(pf != NULL)
    {
        if( max < b )
        {
            max = b;
            
            pmax = pn;
            pn = pf;
            pf = pn -> next;
            
            b = pn -> num;
        }
        
        else
        {
            pn = pf;
            pf = pn -> next;
            
            b = pn -> num;
        }
    }
    
    if( max < b )
    {
        max = b;
        
        pmax = pn;
    }
}

void change(void)
{
    int helpful_digit;
    
    helpful_digit = pmax -> num;
    
    pmax -> num = pmin -> num;
    pmin -> num = helpful_digit;    
}

void output(void)
{
    pf = first;
    
    while( pf != NULL )
    {
        printf("%d\n", pf -> num);
        
        pf = pf -> next;
        
        free(first);
        
        first = pf;
    }
}






















