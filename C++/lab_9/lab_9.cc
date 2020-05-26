// Гусаров Аркадий РК6-23Б 1 курс. Программа для поиска в любом заданном текстовом файле абзаца, который состоит из максимального числа строк.
// Пример ввода: ./a.out file.txt

#include <stdio.h> // для работы с файлом
#include <iostream>
using namespace std;

class Paragraph
{
private:
    FILE *file;                   // указатель на файл
    int maxParagraphStrings = -1; // max число строк в абзаце
    int paddingTopMax = 0;        // отступ от начала файла до абзаца с max числом строк

public:
    Paragraph(char *);   // конструктор по умолчанию
    void error(int);     // ф-ия проверки на ошибки; принимает кол-во аргументов командной строки
    void scanFile();     // ф-ия поиска в текстовом файле абзаца, который состоит из максимального числа строк
    bool isSymbol(char); // ф-ия проверки символа (разделитель / нет); принимает символ, возвращает false, если разделитьель, иначе - true
    void output();       // ф-ия вывода результата
};

Paragraph::Paragraph(char *name)
{
    file = fopen(name, "r+"); // файл открыт для чтения и записи (должен существовать)
};

void Paragraph::error(int argc)
{
    char c;                  // текущий символ
    bool someSymbol = false; // есть ли символ в строке

    if (argc != 2)
    {
        cout << "Ошибка при вводе аргументов" << endl;
        exit(1);
    }
    if (file == NULL)
    {
        cout << "Файл не найден" << endl;
        exit(2);
    }
    // добавление в конец файла '\n'
    fseek(file, 0, SEEK_END); // сдвиг в конец файла
    fputs("\n", file);        // дописывание '\n'
    fseek(file, 0, SEEK_SET); // сдвиг в начало файла
};

void Paragraph::scanFile()
{
    char c;                       // текущий символ
    bool someSymbol = false;      // есть ли символ в строке
    int currentString = 0;        // текущая строка в файле
    int paddingTop = 0;           // отступ от начала файла до текущего абзаца
    int thisParagraphStrings = 0; // кол-во строк в текущем абзаце

    while ((c = fgetc(file)) != EOF)
    {
        // проверка, что в строке есть символы помимо ' ' и '\t'
        if (c != '\n')
            someSymbol += isSymbol(c);
        else
        {
            currentString += 1;
            // если были символы в строке, то абзац продолжается
            if (someSymbol == true)
                thisParagraphStrings += 1;
            // иначе - абзац закончился
            else if (someSymbol == false)
            {
                if (maxParagraphStrings < thisParagraphStrings)
                {
                    maxParagraphStrings = thisParagraphStrings;
                    paddingTopMax = paddingTop;
                }

                paddingTop = currentString;
                thisParagraphStrings = 0;
            }
            someSymbol = false;
        }
    }
};

bool Paragraph::isSymbol(char c)
{
    bool someSymbol = false;

    if ((c != ' ') && (c != '\t'))
        someSymbol = true;

    return someSymbol;
};

void Paragraph::output()
{
    fclose(file); // файл закрыт

    cerr << "Максимальное кол-во строк: " << maxParagraphStrings << endl;
    cerr << "Отступ до абзаца: " << paddingTopMax << endl;
};

int main(int argc, char *argv[])
{
    Paragraph par(argv[1]);

    par.error(argc);
    par.scanFile();
    par.output();

    return 0;
}