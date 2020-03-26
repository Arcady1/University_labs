// Гусаров Аркадий РК6-23Б 1 курс. Программа вычисления пересечения двух любых подмножеств латинских букв, которые передаются ей через аргументы командной строки.
// Пример ввода: ./a.out abcd acdef

#include <iostream>
using namespace std;

class Letters
{
    private:
        unsigned word;                                          // закодированное слово (из терминала)
        unsigned alpha;                                         // закодированный алфавит
    public:
        Letters() { word = 0; alpha = 0; };                     // конструктор по умолчанию
        Letters(char*);                                         // конструктор инициализации строки и преобразования слова в 'word', заполнение 'alpha' алфавитом заглавных букв; принимает введенное слово
        int operator,(unsigned&);                               // перегрузка оператора ',' для перемножения 'word' и 'alpha'; принимает введенное слово, возвращает число заглавных букв в слове
        friend ostream& operator<<(ostream&, Letters&);         // перегрузка оператора '<<'
};

Letters::Letters(char* s)
{
    int code;
    
    word = 0;
    alpha = 0;

    while (*s)                                          // инициализация единицами позиций заглавных букв введенного слова
    {
        code = (int)(*s);

        if ( (code > 64) & (code < 91) )
        {
            printf("U: %c; ", (char)(code));
            word |= (1 << (code - 'A'));
            printf("code: %d\n", code - 'A');
        }    

        s++;
    }

    for (int i = 0; i < 26; i++)                        // заполнение 'alpha' алфавитом заглавных букв
        alpha |= (1 << i);
}

int Letters::operator,(unsigned& alp)
{
    unsigned bin;
    int count;
    
    alp = alpha;
    bin = 0;
    count = 0;

    word = word & alpha;                                // в word перезаписали позиции заглавных букв слова

    for (int i = 0; i < 26; i++)                        // подсчет заглавных букв
    {
        bin = 1 << i;

        if ( ((word & bin) > 0) )
            count++;
    }

    return count;
}

ostream& operator<<(ostream& out, Letters& wd)
{
    unsigned bin;

    bin = 1;

    for (int i = 0; i < 26; i++)
    {
        if ( (wd.word & bin) > 0 )
            out << (char)('A' + i);
        
        bin = bin << 1;
    }

    return out;
}

void Errors_check(int);                                 // ф-ия проверки на ошибки при передаче аргументов; принимает кол-во аргументов

int main(int argc, char *argv[])
{
    Errors_check(argc);

    unsigned alp;
    int result;

    Letters text(argv[1]);
    result = (text.operator,(alp));

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