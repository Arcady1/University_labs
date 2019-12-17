#include <stdio.h>
#include <stdlib.h>

void input();

typedef struct List{
    int digit;
    struct List *next;
} List;

int main(int argc, char const *argv[])
{
    FILE *file;
    
    file = fopen(argv[0], r);
    printf("!");
    input();

    return 0;
}

void input()
{
    for 
}
