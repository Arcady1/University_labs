#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    int num;
    struct List *next;
} List;

List *first = NULL;

List* fill_in(int);
void output(void);

int main()
{
    int digit = 0;
    
    while( digit != 111 )
    {
        scanf("%d", &digit);
        
        fill_in(digit);
        //printf("%d\n", digit);
    }
    
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

void output(void)
{
    while( first != NULL )
    {
        printf("=======\n");
        printf("%d\n", first -> num);
        
        first = first -> next;
    }
}
























