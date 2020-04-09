// Гусаров Аркадий РК6-23Б 1 курс. Программа подсчета числа различных заглавных букв в любом слове из латинских букв, которое задается аргументы командной строки.
// Пример ввода: ./a.out AbcCdDD

#include <cctype>
#include <iostream>
using namespace std;

class Letters
{
    private:
        unsigned low;                                           // находятся строчные буквы слова
        unsigned cap;                                           // находятся заглавные буквы слова
    public:
        Letters() { low = 0; cap = 67108863; };                 // конструктор по умолчанию
        Letters(char*);                                         // конструктор инициализации строки и преобразования слова в 'word', заполнение 'alpha' алфавитом заглавных букв; принимает введенное слово
        int operator,(Letters&);                                // перегрузка оператора ',' для перемножения 'word' и 'alpha'; принимает введенное слово, возвращает число заглавных букв в слове
        friend ostream& operator<<(ostream&, Letters&);         // перегрузка оператора '<<'
};

Letters::Letters(char* s)
{
    int code;
    
    cap = 0;
    low = 0;

    while (*s)                                          // заполнение cap и low 
    {
        code = (int)(*s);

        if ( isupper(*s) )                              // если буква прописная
            cap |= (1 << (code - 'A'));

        else
            low |= (1 << (code - 'a')); 

        s++;
    }
}

int Letters::operator,(Letters& object_)
{
    unsigned bin;
    unsigned digit;
    int count;

    count = 0;
    digit = 1;
    bin = cap & object_.cap;

    for (int i = 0; i < 26; i++)                        // подсчет заглавных букв
    {
        digit = 1 << i;

        if ( ((bin & digit) > 0) )
            count++;
    }

    return count;
}

ostream& operator<<(ostream& out, Letters& text_)
{
    unsigned bin;

    bin = 1;

    for (int i = 0; i < 26; i++)
    {
        if ( (text_.cap & bin) > 0 )
            out << (char)('A' + i);
        
        bin = bin << 1;
    }

    return out;
}

void Errors_check(int);                                 // ф-ия проверки на ошибки при передаче аргументов; принимает кол-во аргументов

int main(int argc, char *argv[])
{
    Errors_check(argc);

    int result;
    Letters text(argv[1]);
    Letters object;

    result = (text, object);

    cout << result << " = (" << text << ", " << object << ")" << endl;

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