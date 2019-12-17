#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    int num;
    struct List *next;
} List;

List *first = NULL;

List* fill_in(int);

int main()
{
    int digit = 0;
    
    while( digit != 111 )
    {
        scanf("%d", &digit);
        
        fill_in(digit);
        //printf("%d\n", digit);
    }
    
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
