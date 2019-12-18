#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    int num;
    struct List *next;
} List;

List first;
List *pl = &first;

void fill_in(int);
void search(void);
void output(void);

int main(int argc, char* argv[])
{
    int digit, num_f;
    
    first.num = 100;
    first.next = NULL;
    
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
    List *pf, *pb, *pn, *p_first;
    
    pf = &first;
    
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
        printf("=======\n");
        printf("%d\n", a -> num);
        
        a = a -> next;
    }
    
    printf("=======\n");
    printf("%d\n", a -> num);
    printf("=======\n");
}
