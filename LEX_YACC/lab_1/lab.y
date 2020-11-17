// Гусаров Аркадий РК6-33Б 2 курс.

// Блок глобальных описаний
%{
    #include <stdio.h>        
    
    void yyerror(char const *);
    int yylex(void);
    int yywrap() { return 1; }
    int Round(int, int);
%}

%token NUMBER

// Секция правил
%%
input: { printf("Enter the line: \n"); }        // позволяет трактовать нетерминал input как одиночную лексему line, или последовательность лексем line произвольной длины
     | input line
     ;

line: '\n' { printf("Empty line!\n"); }
    | error '\n' { yyerrok; }                   // оператор yyerrok переводит анализатор в обычное состояние
    | expr
    ;

expr: NUMBER '/' NUMBER '\n'
    {
        if ($3 == 0)
            yyerror("syntax error");        
        else
            printf("%d\n", Round($1, $3));
    }
    ;
%%

int main()
{
    yyparse();      // yyparse() вызывается для чтения лексем 
    return 0;
}
     
void yyerror(char const *s)
{
    fprintf(stderr, "%s\n", s);
    return 1;     
}

int Round(int numer, int denom)
{
    if (numer % denom != 0)
    {
        if (((numer < 0) && (denom > 0)) || ((numer > 0) && (denom < 0)))
            return (numer / denom);
        return (numer / denom + 1);
    }
    else
        return (numer / denom);
}
