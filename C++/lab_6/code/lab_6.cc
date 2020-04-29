// Гусаров Аркадий РК6-23Б 1 курс. Программа ...
// Компиляция: g++ dlink.cpp lab_6.cc
// Пример ввода: ./a.out asdasd

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
    void *work();                                         // поиск символа с максимальным кодом
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

void *SymLink::work()
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

    q = head->seek(lenght / 2); // находимся в середине слова

    SymLink *head_1 = q;
    SymLink *head_2 = q->incr();

    for (int i = 0; i < count; i++)
    {
        head_1->after(symbol);
        putchar(head_1->_sym);
        printf("\n");
        // head_1->_next = symbol;
        head_1 = head_1->incr();
        putchar(head_1->_sym);
        printf("\n");
        // head_1 = head_1->_next;
    }

    head_1->_next = head_2;
}

int main(int argc, char *argv[])
{
    int ch;
    // int center;        // длина введенного слова
    SymLink *watch[2]; // начало и конец списка
    SymLink *head;
    SymLink *tail;
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

    head->work(); // p - символ, который нужно переставить в центр

    head->print();

    return 0;
}
