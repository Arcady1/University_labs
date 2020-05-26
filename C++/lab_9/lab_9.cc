// Гусаров Аркадий РК6-23Б 1 курс. Программа для поиска в любом заданном текстовом файле абзаца, который состоит из максимального числа строк.

#include <stdio.h> // для работы с файлом
#include <iostream>
using namespace std;

void scanFile(FILE *);

int main(int argc, char *argv[])
{
    FILE *file;                 // указатель на файл
    file = fopen(argv[1], "r"); // файл открыт для чтения
    if (file == NULL)
    {
        printf("Файл не найден\n");
        return 1;
    }

    //
    scanFile(file);

    //
    fclose(file); // файл закрыт

    return 0;
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
            if ((c != ' ') || (c != '\t'))
            {
                someSymbol = true;
            }
            printf("%c", c);
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