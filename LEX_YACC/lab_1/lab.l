/* Гусаров Аркадий РК6-33Б 2 курс.


Запуск: yacc -d lab.y; lex lab.l; cc y.tab.c lex.yy.c; ./a.out
*/


%{
    #include "y.tab.h"
%}

DIGIT       0|-?[1-9]+[0-9]*

%%
{DIGIT}     { yylval = atoi(yytext); return NUMBER; }
\/          { return '/'; }
\n          { return '\n'; }
.           { }
%%

// Нет main(), т.к. она определена в lab.y