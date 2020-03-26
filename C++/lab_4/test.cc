#include <cctype>
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
        // friend ostream& operator<<(ostream&, Letters&);         // перегрузка оператора '<<'
};

Letters::Letters(char* s)
{
    int code;

    code = 0;
    word = 0;
    alpha = 0;

    while (*s)                                          // инициализация единицами позиции букв введенного слова    #######################################
    {
        code = (int)(*s);

        if ( (code > 64) & (code < 91) )
        {
            printf("A: %c; ", (char)(code));
            word |= (1 << (26 + (code - 'A')));
            printf("code: %d\n", 26 + (code - 'A'));
        }
            

        else if ( (code > 96) & (code < 123) )
        {
            printf("a: %c; ", (char)(code));
            word |= ( 1 << (code - 'a') );
            printf("code: %d\n", code - 'a');
        }

        s++;
    }

    int i = 0;

    for (i = 26; i < 52; i++)                       // заполнение 'alpha' алфавитом заглавных букв
    {
        alpha |= (1 << 30);
        printf("\n%d\n", alpha);
        exit (20);
    }
}

int Letters::operator,(unsigned& alp)
{
    unsigned bin;
    int count;
    
    // alp = alpha;
    bin = 0;
    count = 0;

    word = word & alpha;                                      // в word перезаписали позиции заглавных букв слова

    for (int i = 0; i < 100; i++)                           // подсчет заглавных букв
    {
        bin = 1 << i;

        if ( ((word & bin) > 0) )
            count++;
    }

    printf("%d\n", count);

    exit (1);

    return count;
}

// ostream& operator<<(ostream& out, Letters& wd)
// {
//     unsigned bin;

//     bin = 0;

//     for (int i = 65; i < 91; i++)
//     {
//         bin = 1 << i;

//         if ( (wd.word & bin) > 0 )
//             out<<(char)(i);        
//     }

//     return out;
// }

void Errors_check(int);                                 // ф-ия проверки на ошибки при передаче аргументов; принимает кол-во аргументов

int main(int argc, char *argv[])
{
    Errors_check(argc);

    unsigned alp;
    int result;

    Letters text(argv[1]);
    result = (text.operator,(alp));

    // cout << text << endl;
    // cout << result << endl;

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