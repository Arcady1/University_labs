#include <iostream>
using namespace std;

class Letters
{
    private:
        unsigned word;                                          // кодировка слова (только заглавные буквы)
        unsigned alpha;                                         // кодировка алфавита заглавных букв
    public:
        Letters() { word = 0; alpha = 0; };                     // конструктор по умолчанию
        Letters(char*);                                         // конструктор инициализации строки и преобразования слова в 'word', заполнение 'alpha' алфавитом заглавных букв; принимает введенное слово
        int operator,(unsigned&);                               // перегрузка оператора ',' для перемножения 'word' и 'alpha'; принимает введенное слово, возвращает число заглавных букв в слове
        friend ostream& operator<<(ostream&, Letters&);         // перегрузка оператора '<<'
        unsigned getAlpha() { return alpha; };
};

Letters::Letters(char* s)
{
    int code;

    word = 0;
    alpha = 0;

    while (*s)                                          // инициализация единицами позиции заглавных букв введенного слова
    {
        code = (int)(*s);

        if ( ((code > 64) & (code < 91)) )
            word |= (1 << code);
        
        s++;
    }

    for (int i = 65; i < 91; i++)                       // заполнение 'alpha' алфавитом заглавных букв
        alpha |= (1 << i);
    
}

int Letters::operator,(unsigned& alp)
{
    unsigned bin;
    int count;
    
    bin = 0;
    count = 0;

    word = word & alp;                                      // в word перезаписали позиции заглавных букв слова

    for (int i = 65; i < 91; i++)                           // подсчет заглавных букв
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

    for (int i = 65; i < 91; i++)
    {
        bin = 1 << i;

        if ( (wd.word & bin) > 0 )
            out<<(char)(i);        
    }

    return out;
}

int main(int argc, char *argv[])
{
    Letters w;
    int result;
    unsigned alp;


    w = argv[1];
    alp = w.getAlpha();
    result = (w.operator,(alp));                      // перегрузка оператора ','

    cout << w << endl;
    cout << result << endl;

    return 0;
}
