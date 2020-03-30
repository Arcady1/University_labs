#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *file;
    file = fopen(argv[1], "r");
    
    char symbol[100];
    char c;
    int symb_num;
    int i = 0;

    symb_num = 0;

    while( (c = fgetc(file)) != EOF )
    {
        if ( c == '\n' )
        {
            symbol[i] = 'Z';
            printf("%c", symbol[i]);
        }
        else
        {
            symbol[i] = c;
            printf("%c", symbol[i]);
        }
        
        i++;
    }
    
    return 0;
}
