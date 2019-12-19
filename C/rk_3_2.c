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
int errors(int, char *[], FILE *);

int main(int argc, char* argv[])
{
    int digit, number;
    
    FILE *file;    
    file = fopen(argv[1], "r");
    
    errors(argc, argv, file);
    
    while( fscanf(file, "%d", &number ) != EOF )     // СЃС‡РёС‚С‹РІР°РµРј С‡РёСЃР»Р° РёР· С„Р°Р№Р»Р°
    {
        digit = number;
        
        fill_in(digit);
    }
    
    searchMin();
    searchMax();
    change();
    output();
    
    return 0;
}

int errors(int argc, char *argv[], FILE *file)
{
    int check;
    
    if( argc < 2 )                              // РїСЂРѕРІРµСЂРєР°, С‡С‚Рѕ Р°СЂРіСѓРјРµРЅС‚РѕРІ РЅРµ РјРµРЅРµРµ 2-С…
    {
        printf("ERROR: NO ARGUMENTS\n");
        exit (102);
    }
    
    if( argc > 2 )                              // РїСЂРѕРІРµСЂРєР°, С‡С‚Рѕ Р°СЂРіСѓРјРµРЅС‚РѕРІ РЅРµ Р±РѕР»РµРµ 2-С…
    {
        printf("ERROR: TOO MANY ARGUMENTS\n");
        exit (103);
    }
    
    if( file == NULL )                          // РїСЂРѕРІРµСЂРєР°, С‡С‚Рѕ С„Р°Р№Р» СЃСѓС‰РµСЃС‚РІСѓРµС‚
    {
        printf("ERROR: NO SUCH FILE\n");
        exit (101);
    }
    
    return 10;
}

void fill_in(int digit)
{
    List *pw;
    
    pw = (List *) malloc( sizeof(List) );           // СЃРѕР·РґР°РµРј РЅРѕРІС‹Р№ СѓР·РµР» Рё Р·Р°РїРѕР»РЅСЏРµРј РµРіРѕ
    
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
        printf("%d\n", pf -> num);
        
        pf = pf -> next;
        
        free(first);
        
        first = pf;
    }
}
