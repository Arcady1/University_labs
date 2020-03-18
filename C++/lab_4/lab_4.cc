#include <math.h>
#include <iostream>
using namespace std;

class Letters
{
    private:
        unsigned word;                                          // кодировка слова (только заглавные буквы)
        unsigned alpha;                                         // кодировка алфавита заглавных букв
    public:
        Letters(char*, unsigned&);                              // конструктор инициализации строки и закодирования слова 'word', заполнение 'alpha' алфавитом заглавных букв; принимает введенное слово, адрес на алфавит
        int operator,(unsigned&);                               // перегрузка оператора ',' для перемножения 'word' и 'alpha'; принимает введенное слово, возвращает число заглавных букв в слове
        friend ostream& operator<<(ostream&, Letters&);         // перегрузка оператора '<<'
};

Letters::Letters(char* s, unsigned& alpha_)
{
    int code;

    word = 0;
    alpha_ = 0;

    while (*s)                                          // в 'word' записывается закодированное введенное слово (позиции: a-z: 32-57; A-Z: 0-25)
    {
        code = (int)(*s);
        word |= ( 1 << (abs(code - 'A')) );

        s++;
    }

    for (int i = 0; i < 26; i++)                        // заполнение 'alpha' алфавитом заглавных букв (позиции: A-Z: 0-25)
        alpha_ |= (1 << i);
    
    this->alpha = alpha_;
}

int Letters::operator,(unsigned& alpha_)
{
    unsigned bin;
    int count;
    
    bin = 0;
    count = 0;

    word = word & alpha_;                               // в word перезаписываются позиции заглавных букв слова

    for (int i = 0; i < 26; i++)                        // подсчитываются заглавные буквы
    {
        bin = 1 << i;

        if ( ((word & bin) > 0) )
            ++count;
    }

    return count;
}

ostream& operator<<(ostream& out, Letters& wd)
{
    unsigned bin;

    bin = 0;

    for (int i = 0; i < 26; i++)
    {
        bin = 1 << i;

        if ( (wd.word & bin) > 0 )
            out<<(char)('A' + i);        
    }

    return out;
}

void Errors_check(int);                                 // ф-ия проверки на ошибки при передаче аргументов; принимает кол-во аргументов

int main(int argc, char *argv[])
{
    Errors_check(argc);

    unsigned Alphabet;
    int result;

    Letters text(argv[1], Alphabet);
    
    result = (text, Alphabet);                          // перегрузка оператора ','

    cout << text << endl;
    cout << result << endl;

    return 0;
}

void Errors_check(int ac)
{
    if (ac != 2)
    {
        printf("Ошибка при вводе аргументов\n");
        exit (1);
    }
}