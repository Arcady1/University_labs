#include <iostream>
using namespace std;

class Letters
{
    private:
        unsigned word;                                          // кодировка слова
        unsigned alpha;                                         // кодировка алфавита заглавных букв
    public:
        Letters() { word = 0; alpha = 0; };                     // конструктор по умолчанию
        Letters(char*);                                         // конструктор инициализации строки и преобразования слова в 'word'; принимает слово
        int operator,(unsigned&);                               // перегрузка оператора ',' для перемножения 'word' и 'alpha'; принимает введенное слово, возвращает число заглавных букв в слове
        friend ostream& operator<<(ostream&, Letters&);         // перегрузка оператора '<<'
        unsigned getAlpha() { return alpha; };
};

Letters::Letters(char* s)
{
    
}

int Letters::operator,(unsigned& alph)
{

}

ostream& operator<<(ostream& out, Letters& word)
{

}

int main(int argc, char *argv[])
{
    Letters w;
    int result;
    unsigned alp;


    w = argv[1];
    alp = w.getAlpha();
    result = (w.operator,(alp));                      // перегрузка оператора ','

    printf("%d\n", result);

    return 0;
}
