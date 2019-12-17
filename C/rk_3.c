#include <stdio.h>
#include <stdlib.h>

void input();

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
        
        //printf("%d\n", digit);
    }
    
    return 0;
}
