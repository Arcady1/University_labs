/* Гусаров Аркадий РК6-33Б 2 курс.

Запуск: yacc Y8_1.y
        g++ y.tab.c
        ./a.out
*/

%{
    #include <stdio.h>        
    
    void yyerror(char const *);
    int yylex(void);
    int yywrap() {return 1;}
%}

%token NUMBER

%%
input: { printf("Enter the line: \n"); }        // рекурсивное правило; в первый раз запускается: { printf("Enter the line: \n"); }
     | input line                               // затем - input line
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
            printf("%d and %d\n", (int)($1), (int)($3));
    }
    ;
%%
     
void yyerror(char const *s)
{
    fprintf(stderr, "%s\n", s);      
}

int main()
{
    yyparse();      // yyparse() вызывает для чтения лексем функцию yylex()
    return 0;
}