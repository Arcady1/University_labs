/* Гусаров Аркадий РК6-33Б 2 курс.
Разработать ООП для компьютерной реализации игры с покрытием клеток 
шахматной доски (10х10) фишками домино. При этом за 1 ход можно покрыть 
любую пару смежных клеток без наложения фишек и нарушения границ доски. 
Проигрывает тот, кто не может сделать очередной ход. Эта игра должна быть 
реализована в варианте, когда противниками являются компьютер и человек. 
Человек может выбирать произвольные ходы, указывая позиции своей фишки 
по запросу стандартного ввода. При этом любая ошибка ввода должна 
приводить к аварийному прерыванию партии игры. Компьютер должен отвечать 
симметричными ходами относительно центра шахматной доски. Все ходы обоих 
игроков должны отображаться в клетках стандартного вывода шахматной доски. 
Игра должна завершаться диагностикой ее итогового результата.

Пример ввода: ./a.out
" " a1 a2
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
using namespace std;

class Domino
{
private:
    int sizeOfBoard = 10;
    char board[10][10];

public:
    Domino() { boardFill(); };
    void boardFill();          // заполнение поля (матрицы)
    void printBoard();         // метод отображения доски
    void moveUser();           // ход человека
    void movePC(int[], int[]); // ход компьютера
};

void Domino::boardFill()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '.';
}

void Domino::printBoard()
{
    cout << "\ta b c d e f g h i j\n\n";  // верхняя строка
    for (int i = 0; i < sizeOfBoard; i++) // цикл по строкам
    {
        cout << i << "\t"; // номер строки доски слева
        for (int j = 0; j < sizeOfBoard; j++)
            cout << board[i][j] << " ";

        cout << "\t" << i << "\n"; // номер строки доски справа
    }
    cout << "\n\ta b c d e f g h i j\n"; // нижняя строка
}

void Domino::moveUser()
{
    int posStart[2]; // позиции фишек по индексам матрицы
    int posEnd[2];
    char posS[2]; // введенные координаты
    char posE[2];
    char userSymbol = 'u';

    scanf("%c%c %c%c", &posS[0], &posS[1], &posE[0], &posE[1]);
    printf("\n=================\nYour input: %c%c %c%c\n=================\n", posS[0], posS[1], posE[0], posE[1]);

    posStart[0] = int(posS[1]) - 48;
    posStart[1] = int(posS[0])-97;
    posEnd[0] = int(posE[1]) - 48;
    posEnd[1] = int(posE[0]) - 97;

    // ввод одинаковых координат
    if ((posStart[0] == posEnd[0]) && (posStart[1] == posEnd[1]))
    {
        cout << "ERROR: No difference!" << endl;
        exit(3);
    }
    // за пределами поля
    else if ((posStart[0] < 0) || (posStart[0] > 9) || (posEnd[0] < 0) || (posEnd[0] > 9) || (posStart[1] < 0) || (posStart[1] > 9) || (posEnd[1] < 0) || (posEnd[1] > 9))
    {
        cout << "ERROR: Off the chessboard!" << endl;
        exit(4);
    }
    // свободны ли клетки
    else if ((board[posStart[0]][posStart[1]] != '.') || (board[posEnd[0]][posEnd[1]]) != '.')
    {
        cout << "ERROR: Is not free!" << endl;
        exit(5);
    }
    // неправильное расположение фишек
    else if ((abs(posStart[0] - posEnd[0]) >= 1) && (abs(posStart[1] - posEnd[1]) >= 1))
    {
        cout << "ERROR: Chips are diagonally!" << endl;
        exit(6);
    }
    else if ((abs(posStart[0] - posEnd[0]) > 1) || (abs(posStart[1] - posEnd[1]) > 1))
    {
        cout << "ERROR: Over-distance!" << endl;
        exit(7);
    }
    else
    {
        board[posStart[0]][posStart[1]] = userSymbol;
        board[posEnd[0]][posEnd[1]] = userSymbol;
    }

    movePC(posStart, posEnd); // ход компьютера
    printBoard();
}

void Domino::movePC(int posStart[], int posEnd[])
{
    int res11, res12, res21, res22;
    char PCsymbol = 'c';

    res11 = 9 - posStart[0];
    res12 = 9 - posEnd[0];
    res21 = 9 - posStart[1];
    res22 = 9 - posEnd[1];

    if ((board[res11][posStart[1]] == '.') && (board[res12][posEnd[1]] == '.'))
    {
        board[res11][posStart[1]] = PCsymbol;
        board[res12][posEnd[1]] = PCsymbol;
    }
    else if ((board[posStart[0]][res21] == '.') && (board[posEnd[0]][res22] == '.'))
    {
        board[posStart[0]][res21] = PCsymbol;
        board[posEnd[0]][res22] = PCsymbol;
    }
    else if ((board[res11][res21] == '.') && (board[res12][res22] == '.'))
    {
        board[res11][res21] == PCsymbol;
        board[res12][res22] == PCsymbol;
    }

    else
    {
        printBoard();
        cout << "You are winner!" << endl;
        exit(2);
    }
}

int main(int argc, char *argv[])
{
    // проверка числа аргументов
    if (argc != 1)
    {
        cout << "Incorrect number of arguments" << endl;
        return 1;
    }

    Domino U;
    U.printBoard();

    printf("Input: ");
    while (getchar() != '\0')
    {
        U.moveUser(); // ход игрока
    }

    return 0;
}
