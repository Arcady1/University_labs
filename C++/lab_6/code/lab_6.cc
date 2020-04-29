// Гусаров Аркадий РК6-23Б 1 курс. Программа ...
// Пример ввода: ./a.out ...

#include <cstdio>
#include <cstdlib>
#include "dlink.hpp"
using namespace std;

class SymLink : public Dlink // SymLink - наследник класса Dlink
{
private:
    unsigned char _sym;

public:
    SymLink(unsigned char c) : Dlink(), _sym(c){};        // констуктор
    SymLink *incr() { return (SymLink *)Dlink::incr(); }; // метод базового класса
    SymLink *decr() { return (SymLink *)Dlink::decr(); }; // метод базового класса
    SymLink *seek(int);                                   // функция, возвращающая адрес записи
    int count();                                          // подсчет количества символов
    int print();                                          // вывод списка на экран
    SymLink *top();                                       // поиск символа с максимальным кодом
    int mess(int, int);                                   // смена позиции буквы и установка знака '^'
};

SymLink *SymLink::seek(int n)
{
    if (n > 0)
        return (SymLink *)Dlink::toTail(n);

    if (n < 0)
        return (SymLink *)Dlink::toHead(abs(n));

    return this;
}

int SymLink::count()
{
    SymLink *p = this;
    SymLink *q;
    int n = 0;

    while (p != NULL)
    {
        q = p->incr();
        p = q;
        n++;
    }
    return (n - 2); // учет "стражей" - указателей на начало и конец
}

int SymLink::print()
{
    SymLink *p = this;
    SymLink *q;

    while (p != NULL)
    {
        putchar(p->_sym);
        q = p->incr();
        p = q;
    }

    return 0;
}

SymLink *SymLink::top()
{
    SymLink *p = this;
    SymLink *head = this; // указывает на head списка
    SymLink *q;
    SymLink *symbol;
    int count, lenght;
    int code_n, code_l;

    count = 0;
    lenght = 0;
    code_l = 10;
    p = p->incr();

    while (p != NULL) // поиск максимального кода, записывается в code_l
    {
        code_n = (int)p->_sym;

        if (code_n > code_l)
            code_l = code_n;

        q = p->incr();
        p = q;
    }

    p = head;
    while (p != NULL) // подсчет букв с max кодом - count
    {
        if (int(p->_sym) == code_l)
        {
            count++;
        }

        q = p->incr();
        p = q;
    }

    p = head;
    while (p != NULL) // длина слова - lenght
    {
        lenght++;
        q = p->incr();
        p = q;
    }

    lenght -= 2;

    p = head;
    while (p != NULL) // удаляю и переставляю букву с max кодом
    {
        if (int(p->_sym) == code_l)
        {
            symbol = p;
            symbol->excluse();
        }

        q = p->incr();
        p = q;
    }

    lenght -= count; 
    
    q = head->seek(lenght / 2);     // находимся в середине слова
    // printf("%c\n", q->_sym);

    SymLink* head_1 = q;            // d
    SymLink* head_2 = q->incr();    // a

    for (int i = 0; i < count; i++)
    {
        head_1->after(symbol);
        head_1 = head_1->incr();
    }

    head_1->_next = head_2;

    head->print();
    
    
    // длина слова без букв с max кодом
    // printf("%d\n", lenght);
    // for (int i = 0; i < count; i++)
    // {
    //     q = head->seek(lenght / 2); // буква в середине слова - q
    //     putchar(q->_sym);
    //     q->before(symbol);           // запись буквы с max кодом в середину слова
    //     lenght++;
    //     // exit (10);
    // }

    // p = head;
    // while (p != NULL)
    // {
    //     putchar(p->_sym);
    //     q = p->incr();
    //     p = q;
    // }

    // head->print();

    // symbol->excluse();       // удаляем букву с max кодом
    // lenght -= count; //

    // count--;

    // putchar(symbol->_sym);

    // над ячейкой списка с буквой f - указатель symbol
    // printf("%d\n", code_l);
    // printf("%d\n", count);
    // printf("%d\n", lenght);

    // q = symbol; // q хранит ячейку с буквой с max кодом
    // symbol->excluse();

    // return q;
}

int SymLink::mess(int code, int center)
{
    // char ch;
    SymLink *p = this;
    SymLink *q;

    // while ( int(p->_sym) != code )
    //     p = p->incr();

    // q = p;
    // p->excluse();

    q->toTail(center);
    // p->after(q);
}

int main(int argc, char *argv[])
{
    // int length, t;
    int ch;
    int code;
    int center;        // длина введенного слова
    SymLink *watch[2]; // начало и конец списка
    SymLink *head;
    SymLink *tail;
    // SymLink *head1;
    SymLink *c;
    SymLink *p;

    watch[0] = head = new SymLink('\n');
    watch[1] = tail = new SymLink('\n');
    tail->before(head); //прикрепляем tail к head

    while ((ch = getchar()) != '\n')
    {
        c = new SymLink(ch);
        tail->before(c);
    }

    p = head->top(); // p - символ, который нужно переставить в центр
    // center = (head->count()) / 2;

    // p->mess(code, center);

    // p = head->seek(center);

    // head->print();

    return 0;
}
