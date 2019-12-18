#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    int num;
    struct List *next;
} List;

List first;                         // создаем пустой список (внешняя переменная)
List *pl = &first;                  // создаем укзатель на последний узел списка (внешняя переменная)

void fill_in(int);                  // ф-ия принимает считанное из файла число и вносит его в список
void search(void);                  // ф-ия ищет числа, которые > 10, и удаляет их из списка
void output(void);                  // ф-ия выводит измененный список

int main(int argc, char* argv[])
{
    int digit, num_f;
    
    first.num = 100;                // заполняем внешний узел first значениями
    first.next = NULL;
    
    FILE *file;
    
    file = fopen(argv[1], "r");    
    
    while( fscanf(file, "%d", &num_f ) != EOF )     // считываем числа из файла
    {
        digit = num_f;
        
        fill_in(digit);
    }
    
    search();
    output();
    
    return 0;
}

void fill_in(int digit)
{
    List *pw;
    
    pw = (List *) malloc( sizeof(List) );           // создаем новый узел и заполняем
    
    pw -> num = digit;
    pw -> next = NULL;
    pl -> next = pw;                                // pl сдвигается в конец списка 
    pl = pw;
}

void search(void)
{
    List *pf, *pb, *pn, *p_first;
    
    pf = &first;                                    // pf - указатель на первый узел списка
    
    while( pf != NULL )
    {
        if( (pf -> num) > 10 )
        {
            if( (pf -> next) == (first.next) )
            {
                first = *first.next;
                
                //free(pf);
                
                pf = &first;
            }
            else
            {
                pn = pf -> next;
                
                //free(pf);
                
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
    List *a = &first;
    
    while( a -> next != NULL )
    {
        printf("%d\n", a -> num);
        
        a = a -> next;
    }
    
    printf("%d\n", a -> num);
}
