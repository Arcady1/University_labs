/* Гусаров Аркадий РК6-33Б 2 курс.
Разработать конечный автомат для распознавания во входном потоке цифровой информации
записей двоичных наборов, где число единиц нечетно, а число нулей делится на 3. Записи
двоичных наборов должны передаваться конечному автомату строками потока стандартного
ввода. Результаты их распознавания должны отображаться через поток стандартного вывода.
Программная реализация конечного автомата должна формироваться генератором YACC по
правилам регулярной грамматики.

Запуск: yacc A08.y; g++ y.tab.c; ./a.out
*/

%{
    #include <stdio.h>
    int yylex();
    int yyerror(char* s);
    char* mes[] = {"Correct", "Incorrect"};
%}

%%
A: '0' E 
   |'1' B 
   ;
B: '0' F 
   |'1' A 
   |'\n' { return 0; }
   ;
C: '0' A
   |'1' D 
   ;
D: '0' B 
   |'1' C 
   ;
E: '0' C 
   |'1' F 
   ;
F: '0' D 
   |'1' E 
   ;
%%

int yylex()
{
    return (getchar());
}

int yyerror(char* s)
{
    return 1;
}

int main(int argc, char* argv[])
{
    int ret = yyparse();
    printf("%s\n", mes[ret]);
    return (ret);
}