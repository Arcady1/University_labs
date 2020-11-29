/* Гусаров Аркадий РК6-33Б 2 курс.
Разработать конечный автомат для распознавания во входном потоке цифровой информации
записей двоичных наборов, где число единиц нечетно, а число нулей делится на 3. Записи
двоичных наборов должны передаваться конечному автомату строками потока стандартного
ввода. Результаты их распознавания должны отображаться через поток стандартного вывода.
Программная реализация конечного автомата должна формироваться генератором LEX по
правилам с предусловиями.

Запуск: lex -t A08.l > A08.c ; cc -o A08 A08.c -ll ; ./A08
*/

%{
	#include <ctype.h>
%}


%START Q1 Q2 Q3 Q4 Q5 Q6 ER
%%
<Q1>[ \n\t] {
    puts("INRUT ERROR!");
    BEGIN 0 ;
}
<Q1>0 BEGIN Q5;
<Q1>1 BEGIN Q2;

<Q2>[ \n\t] {
    puts("CORECR!");
    BEGIN 0 ;
}
<Q2>[^10\ \n\t] BEGIN ER ;
<Q2>0 BEGIN Q3;
<Q2>1 BEGIN Q1;

<Q3>[ \n\t] {
    puts("INRUT ERROR!");
    BEGIN 0 ;
}
<Q3>0 BEGIN Q4; 
<Q3>1 BEGIN Q5;

<Q4>[ \n\t] {
    puts("INRUT ERROR!");
    BEGIN 0 ;
}
<Q4>0 BEGIN Q2;
<Q4>1 BEGIN Q6;

<Q5>[ \n\t] {
    puts("INRUT ERROR!");
    BEGIN 0;
}
<Q5>0 BEGIN Q6;
<Q5>1 BEGIN Q3;

<Q6>[ \n\t] {
    puts("INRUT ERROR!");
    BEGIN 0;
}
<Q6>0 BEGIN Q1;
<Q6>1 BEGIN Q4;

<ER>[^\ \t\n] BEGIN ER;

0	BEGIN Q5;
1	BEGIN Q2;
\n	puts("INPUT ERROR!");
.		;
%%

int main()
{	
	yylex();
	exit(0);
}