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
    int top();                                            // поиск символа с максимальным кодом
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

int SymLink::top()
{
    SymLink *p = this;
    SymLink *q;

    int code_n, code_l;

    code_l = 10;
    p = p->incr();

    while (p != NULL)
    {
        code_n = (int)p->_sym;

        if (code_n > code_l)
            code_l = code_n;

        q = p->incr();
        p = q;
    }

    printf("%d\n", code_l);
}

int main(int argc, char *argv[])
{
    // int length, t;
    int ch;
    int code;
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

    // while (  != '\n' ) // поиск символа с максимальным кодом
    // {
    //     code = int(#);

    //     /* code */
    // }

    head->top();
    // head->print();

    return 0;
}
