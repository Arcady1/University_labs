// Гусаров Аркадий РК6-23Б 1 курс. Программа для поиска в любом заданном текстовом файле абзаца, который состоит из максимального числа строк.

#include <stdio.h> // для работы с файлом
#include <iostream>
using namespace std;

void error(int, FILE *); // ф-ия проверки на ошибки; принимает кол-во аргументов командной строки и указатель на файл
bool isSymbol(char);     // ф-ия проверки символа (разделитьель / нет); принимает символ, возвращает false, если разделитьель, иначе - true
void scanFile(FILE *);   // ф-ия поиска в текстовом файле абзаца, который состоит из максимального числа строк; принимает указатель на файл

int main(int argc, char *argv[])
{
    FILE *file;                  // указатель на файл
    file = fopen(argv[1], "r+"); // файл открыт для чтения и записи (должен существовать)
    //
    error(argc, file);
    fseek(file, 0, SEEK_SET); // сдвиг в начало файла
    scanFile(file);
    //
    fclose(file); // файл закрыт

    return 0;
}

void error(int argc, FILE *file)
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
    // добавление в конец фалйа '\n'
    fseek(file, 0, SEEK_END); // сдвиг в конец файла
    fputs("\n", file);        // дописывание '\n'
}

bool isSymbol(char c)
{
    bool someSymbol = false;

    if ((c != ' ') && (c != '\t'))
        someSymbol = true;

    return someSymbol;
}

void scanFile(FILE *file)
{
    char c;                       // текущий символ
    bool someSymbol = false;      // есть ли символ в строке
    int currentString = 0;        // текущая строка в файле
    int paddingTop = 0;           // отступ от начала файла до текущего абзаца
    int paddingTopMax = 0;        // отступ от начала фала до абзаца с max числом строк
    int thisParagraphStrings = 0; // кол-во строк в текущем абзаце
    int maxParagraphStrings = -1; // max число строк в абзаце

    while ((c = fgetc(file)) != EOF)
    {
        // проверка, что в строке есть символы помимо ' ' и '\t'
        if (c != '\n')
        {
            printf("%c", c);
            someSymbol = isSymbol(c);
        }
        else
        {
            currentString += 1;
            printf("\ncurrentString: %d\n", currentString);
            // если были символы в строке, то абзац продолжается
            if (someSymbol == true)
            {
                thisParagraphStrings += 1;
                printf("thisParagraphStrings: %d\n", thisParagraphStrings);
            }
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

    cout << maxParagraphStrings << endl;
    cout << paddingTopMax << endl;
}