/* Гусаров Аркадий РК6-33Б 2 курс.
Разработать синтаксический анализатор для грамматического разбора 
входного потока цифровой информации с целью распознавания записей 
единичных или нулевых двоичных наборов. Записи двоичных наборов 
должны передаваться синтаксическому анализатору строками потока 
стандартного ввода. Результаты грамматического разбора должны отображаться 
строками диагностических сообщений потока стандартного вывода.

Запуск: yacc Y8_2.y
        g++ y.tab.c
        ./a.out
*/

%{
    #include <stdio.h>        
    
    void yyerror(char const *);
    int yylex(void);
    
    bool zero = false;
    bool one = false;
%}

%token ZERO
%token ONE

%%
input: { printf("Enter the line: \n"); }        // рекурсивное правило; в первый раз запускается: { printf("Enter the line: \n"); }
     | input line                               // затем - input line
     ;

line: '\n' { printf("Empty line!\n"); }
    | error '\n' { yyerrok; }                   // оператор yyerrok переводит анализатор в обычное состояние
    | expr '\n'                                 // пустое действие при появлении \n в конце строки
    {
        if (zero == one)                        // сообщение об ошибке, если в последовательности есть и 0, и 1
            yyerror("syntax error");
    }
    ;

expr: ZERO { zero = true; one = false; }
    | ONE { zero = false; one = true; }
    | expr ZERO { zero = true; }
    | expr ONE { one = true; }
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