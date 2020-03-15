#include <cctype>
#include <iostream>
using namespace std;

class Letters
{
    private:
        unsigned short bin;                     // состав слова в виде бинарного кода
    public:
        Letters() { bin = 0; };
        Letters(char*);                         // конструктор преобразование слова в бинарный код; присваивание в bin
};

Letters::Letters (char* s)
{
    bin = 0;
    
    while (*s)
    {
        bin |= ( 1 << (tolower(*s) - 'a' ) );
        s++;
    }
}

int main(int argc, char *argv[])
{
    // ф-ия проверки на ошибки при вводе в терминал

    Letters x(argv[1]);
    Letters y(argv[2]);

    return 0;
}
