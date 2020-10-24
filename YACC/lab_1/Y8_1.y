/* Гусаров Аркадий РК6-33Б 2 курс.
Разработать синтаксический анализатор для грамматического разбора 
входного потока цифровых данных с целью распознавания записей любых 
двоичных наборов, где после каждого нуля стоит, по крайней мере, одна единица. 
Записи любых двоичных наборов должны передаваться синтаксическомy 
анализатору строками потока стандартного ввода. Результаты грамматического 
разбора должны отображать диагностические сообщения потока стандартного вывода.

Запуск: yacc Y8_1.y
        g++ y.tab.c
*/

%{
    #include <stdio.h>        
    
    void yyerror(char const *);
    int yylex(void);
    
    int lengZero = 0;
    int maxLengZero = 0;
%}

/* %start input */
%token ZERO
%token ONE

%%
input: { printf("Enter the line: \n"); }    // рекурсивное правило работает только в первый раз : { printf("Enter the line: \n"); }
    | input line                            // затем - input line
    ;

line: '\n' { printf("Empty line!\n"); }
    | error '\n' { printf("Try again: "); yyerrok; }    // оператор переводит анализатор в обычное состояние
    | expr '\n'                                             // пустое действие при появлении \n в конце строки
    {                                                   // сообщение об ошибке, если нули повторяются
        if (maxLengZero > 1) 
            yyerror("LONG ZERO!");
        printf(":: %d\n", $1);
    }
    ;

expr: ZERO { lengZero = 1; maxLengZero = 1; }
    | ONE { lengZero = 0; maxLengZero = 0; }
    | expr ZERO 
    {
        ++lengZero;
        if (lengZero > maxLengZero)
            maxLengZero = lengZero;

        $$ = maxLengZero;
    }
    | expr ONE
    {
        lengZero = 0;
        $$ = maxLengZero;
    }
    ;
%%

/* Функция yylex возвращает лексемы до тех пор, пока синтаксический анализатор не обнаружит 
ошибку или yylex не вернет маркер конца, означающий завершение входного потока */
int yylex(void)
{
    int c;

    c = getchar();
    if(c == '0')
        return ZERO;    // шаблоны в потоке ввода 0
    if(c == '1')
        return ONE;     // шаблоны в потоке ввода 1
    if (c == EOF)
        return 0;
        
    return c;
}
     
void yyerror(char const *s)
{
    fprintf(stderr, "%s\n", s);      
}

int main()
{
    yyparse();      // yyparse() вызывает для чтения лексем функцию yylex()
    return 0;
}