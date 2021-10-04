#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;

unsigned char word[] = "INTEGRAL";
// 128 в двоичной форме - 10000000
unsigned char lead = 128;

void printSequence(unsigned char B)
{
    static int inRow = 0;

    if (inRow == 4)
    {
        cout << endl;
        inRow = 0;
    }

    cout << '{';

    for (int i = 0; i < 8; i++)
    {
        char digit = (B >> i) & 1;
        if (digit)
        {
            cout << word[i];
        }
    }

    cout << "} ";
    inRow++;
}

unsigned char nextSequence(unsigned char B, int n)
{
    int E = 0, N = 0, counter = n;
    unsigned char copyB = B;

    // Считаем E в бинарном числе B, где E - кол-во лидирующих единиц
    while ((copyB & lead) && counter)
    {
        E++;
        counter--;
        copyB = copyB << 1;
    }

    // Считаем N в бинарном числе B, где N - кол-во нулей после лидирующих единиц
    while (!(copyB & lead) && counter)
    {
        N++;
        counter--;
        copyB = copyB << 1;
    }

    int shift_one = pow(2, n - E);
    int shift_two = pow(2, n - N + 1) - pow(2, n - N - E + 1);
    int shift_tre = pow(2, n - N - E - 1);

    return B + shift_one + shift_two + shift_tre;
}

int main()
{
    // Кол-во символов в слове INTEGRAL
    int n = 8;
    // 15 в двоичном виде - 00001111
    unsigned char B = 15, copyB = 15;

    do
    {
        printSequence(copyB);
        copyB = nextSequence(copyB, n);
    } while ((B & copyB));

    printSequence(copyB);

    cout << endl;

    return 0;
}