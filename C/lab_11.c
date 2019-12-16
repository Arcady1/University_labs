//Гусаров Аркадий РК6-13Б 1 курс. Программа читает из стандартного потока ввода слова и размещает их в стек. Перед добавлением в стек из слова удаляются все символы-не-буквы.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 256

typedef struct Word {           // typedef - чтобы указать, что создан новый тип (не нужно будет писать struct)
    char *str;                  // указатель на введенное слово
    struct Word *next;          // указатель на следующий узел списка
} List;                         // задаем имя списка

List *first = NULL;             // first - указатель на узел

List* work(char [], int);       // ф-ия принимает введенное слово и его длину; возвращает полученный список first
void output();                  // ф-ия выводит список на экран

int main()
{
	char buff[SIZE], c;
	int index_w, length, cut;
	
	index_w = 0;
	cut = 1;
	
	while( (c = getchar()) != EOF )
	{
		if( (c >= 'a') & (c <= 'z') |
		    (c >= 'A') & (c <= 'Z') )
		{
			buff[index_w] = c;
			++index_w;
			cut = 0;                                                                // счетчик символов-разделителей
		}
		else if( ((c == ' ') | (c == '\t') | (c == '\n')) & (cut == 0) )            // получили слово
		{
                    buff[index_w] = '\0';
                    length = strlen(buff);                                          // длина введенного слова
                    work(buff, length);
                    index_w = 0;                                                    // заполняем буфер с 0-го эл-та
                    ++cut;
		}
	}
	
	output();
    
	return 0;
}

List* work(char buff[], int length)
{    
    char *p1;
    
    p1 = (char *) malloc( length * sizeof(char) + 1 );       // выделили память под слово (получили указатель)
    
    if( p1 == NULL )                                         // если кончилась память, то выходим
        exit(10);

    strcpy(p1, buff);                                        // в выделенную память скоипровали слово
    
    List *p2 = (List *) malloc( sizeof(List) );              // выделили память под следующий узел (получили указатель)
    
    if( p2 == NULL )
        exit(11);
    
    p2 -> str = p1;                                          // в первый элемент узла внесли слово
    p2 -> next = first;                                      // во второй элемент узла внесли first - расширили список
    first = p2;                                              // сохранили полученный список в first
                                                             // переменная p2 указывает на последний узел списка    
    return (first);
}

void output(void)
{
    List *p;
    
    printf("\n");
	
    while( first != NULL )
    {
        printf("%s", first -> str);
        free(first -> str);
        
        p = first -> next;
        free(first);
        
        first = p;
        
        printf("\n");
    }
}
