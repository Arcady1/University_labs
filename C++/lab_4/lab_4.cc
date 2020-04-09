// Гусаров Аркадий РК6-23Б 1 курс. Программа подсчета числа различных заглавных букв в любом слове из латинских букв, которое задается аргументы командной строки.
// Пример ввода: ./a.out AbcCdDD

#include <cctype>
#include <iostream>
using namespace std;

class Letters
{
    private:
        unsigned bin[2];                                        // массив с заглавными и строчными буквами слова
    public:
        Letters() { bin[0] = 0; bin[1] = 67108863; };           // конструктор по умолчанию
        Letters(char*);                                         // конструктор инициализации строки и преобразования слова в 'word', заполнение 'alpha' алфавитом заглавных букв; принимает введенное слово
        int operator,(Letters&);                                // перегрузка оператора ',' для перемножения 'word' и 'alpha'; принимает введенное слово, возвращает число заглавных букв в слове
        friend ostream& operator<<(ostream&, Letters&);         // перегрузка оператора '<<'
};

Letters::Letters(char* s)
{
    int code;
    
    bin[1] = 0;                                         // заглавные буквы слова
    bin[0] = 0;                                         // строчные буквы слова

    while (*s)                                          // заполнение bin[1] и bin[0] 
    {
        code = (int)(*s);

        if ( isupper(*s) )                              // если буква прописная
            bin[1] |= (1 << (code - 'A'));

        else
            bin[0] |= (1 << (code - 'a')); 

        s++;
    }
}

int Letters::operator,(Letters& object_)
{
    unsigned mult;
    unsigned digit;
    int count;

    count = 0;
    digit = 1;
    mult = bin[1] & object_.bin[1];                     // в mult заглавные буквы слова без повторений

    for (int i = 0; i < 26; i++)                        // подсчет заглавных букв
    {
        digit = 1 << i;

        if ( ((mult & digit) > 0) )
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
        if ( (text_.bin[1] & bin) > 0 )
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