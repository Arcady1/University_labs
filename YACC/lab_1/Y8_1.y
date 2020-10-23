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
int yylex(void);
void yyerror(char const *);
%}

%token ZERO
%token ONE

%%
input: { printf("Enter the line: \n"); }
    | input line; // рекурсия (имя правила input должно быть слева от line)

line: '\n' { printf("Empty line!\n"); }
    | error '\n' { printf("Try again: "); yyerrok; } // оператор переводит анализатор в обычное состояние
    | expr '\n' 
    {                                                   //выведем сообщение об ошибке, если количество разрядов нечётное
        if(($1 % 2) == 1) 
            yyerror("syntax error");
        else
            printf("Nice!\n");
    }
/*будем увеличивать значение псевдопеременной $$ с каждой единицей и нулём*/
expr: ONE { $$++; }
	| ZERO { $$++; }
	| expr ONE { $$++; }
	| expr ZERO { $$++; }
;
%%

/* Функция yylex возвращает лексемы до тех пор, пока синтаксический анализатор не обнаружит 
ошибку или yylex не вернет маркер конца, означающий завершение входного потока */
int yylex(void)
{
    int c;

    c = getchar();
    if(c == '1')
        return ONE; // шаблоны в потоке ввода ONE
    if(c == '0')
        return ZERO; // шаблоны в потоке ввода ZERO
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
    yyparse(); // yyparse() вызывает для чтения лексем функцию yylex()
    return 0;
}