#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    int num;
    struct List *next;
} List;

List *first = NULL;
List *pl = NULL;

void fill_in(int);
void search(void);
void output(void);

int main(int argc, char* argv[])
{
    int digit, num_f;
    List *pf;
    
    pf = (List *) malloc( sizeof(List) );
    
    pf -> num = 100;
    pf -> next = NULL;
    first = pf;
    
    pl = first;
    
    FILE *file;    
    file = fopen(argv[1], "r");
    
    while( fscanf(file, "%d", &num_f ) != EOF )
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
    
    pw = (List *) malloc( sizeof(List) );
    
    pw -> num = digit;
    pw -> next = NULL;
    pl -> next = pw;
    pl = pw;
}

void search(void)
{
    List *pf, *pb, *pn;
    
    pf = first;
    
    while( pf != NULL )
    {
        if( (pf -> num) > 10 )
        {
            if( (pf -> next) == (first -> next) )
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
    List *pf;
    
    pf = first;
    
    while( first -> next != NULL )
    {
        printf("%d\n", first -> num);
        
        first = first -> next;
    }
    
    printf("%d\n", first -> num);
}
