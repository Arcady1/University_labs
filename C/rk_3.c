#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    int num;
    struct List *next;
} List;

List *first = NULL;

List* fill_in(int);
List* search(void);
void output(void);

int main()
{
    int digit = 0;
    
    while( digit != 5 )
    {
        scanf("%d", &digit);
        
        fill_in(digit);
    }
    
    search();
    output();
    
    return 0;
}

List* fill_in(int digit)
{
    List *p;
    
    p = (List *) malloc( sizeof(List) );
    
    p -> num = digit;
    p -> next = first;
    first = p;
    
    return first;
}

List* search(void)
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
    
    return first;
}

void output(void)
{   
    while( first != NULL )
    {
        printf("=======\n");
        printf("%d\n", first -> num);
        
        first = first -> next;
    }
    
    printf("=======\n");
}
