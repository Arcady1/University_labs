#include <cctype>
#include <iostream>
using namespace std;

class Letters
{
    private:
        unsigned bin;                                       // хранится состав слова в виде бинарного кода
    public:
        Letters() { bin = 0; };
        Letters(char*);                                     // конструктор преобразование слова в бинарный код; присваивание в bin
        Letters operator*(Letters &);                       // метод пересечения множеств букв
        friend ostream& operator<<(ostream&, Letters&);     // перегрузка оператора вывода; ostream& - тип возвращаемого значения (ссылка на ostream), 
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

Letters Letters::operator*(Letters &y)
{
    Letters z;

    z.bin = bin | y.bin;                                    // поиск совпадений букв в словах

    return z;
}

ostream& operator<<(ostream& out, Letters& z)
{
    unsigned f;
    int i;

    f = 1;

    for ( i = 0; i < 26; i++ )
    {
        if ( (z.bin & f) > 0 )
            out << (char)('a' + i);                         // (char)('a' + i) - преобразование к типу 'char'
        
        f = f << 1;
    }

    return out;
}

int main(int argc, char *argv[])
{
    // ф-ия проверки на ошибки при вводе в терминал

    Letters x(argv[1]);
    Letters y(argv[2]);
    Letters z;

    z = x.operator*(y);

    cout << z << endl;

    return 0;
}
