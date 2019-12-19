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

int main(int argc, char* argv[])
{
    int digit, number;
    
    scanf("%d", &number);
    
    while( number != 111 )     // считываем числа из файла
    {
        digit = number;
        
        fill_in(digit);
        
        scanf("%d", &number);
    }
    
    searchMin();
    searchMax();
    change();
    output();
    
    return 0;
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
    
    printf("%d\n", min);
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
    
    printf("%d\n", max);
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
        printf("@: %d\n", pf -> num);
        
        pf = pf -> next;
    }
}






















