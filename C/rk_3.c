#include <stdio.h>
#include <stdlib.h>

void fill_in(int);

typedef struct List{
    int digit;
    struct List *next;
} List;

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

void fill_in(int digit)
{
    
}
