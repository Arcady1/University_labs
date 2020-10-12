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

TODO Пример ввода: ./a.out ###
*/

#include <iostream>
#include <string>
using namespace std;
// ! #define SIZE 10;

class Domino
{
private:
    int sizeOfBoard = 10;
    char posS[2];
    char posE[2];
    char board[10][10];

public:
    Domino() { boardFill(); };
    void boardFill();  // заполнение поля (матрицы)
    void printBoard(); // метод отображения доски
    void move();
    void modBoard();          // метод преобразует поле после хода
    char letterToIndex(char); // метод возвращает индекс, соответсвующий букве поля
};

void Domino::boardFill()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '.';
}

// TODO
void Domino::printBoard()
{
    char s[2];
    // ! const char *mark = ".x+";      // маркер позиции (безопасная / под атакой)
    cout << "\ta b c d e f g h i j\n\n";  // верхняя строка
    for (int i = 0; i < sizeOfBoard; i++) // цикл по строкам
    {
        cout << sizeOfBoard - i << "\t"; // номер строки доски слева
        // ! s[1] = '0' + i;   // текущая позиция по горизонтали
        for (int j = 0; j < sizeOfBoard; j++)
        { // цикл по столбцам
            // ! s[0] = 'a' + j; // текущая позиция по вертикали
            // если позиция не совпадает с положением фигуры, то вывести маркер
            //! char m = (*this != s) ? mark[attack(s)] : isA();
            cout << board[i][j] << " ";
        }
        cout << "\t" << sizeOfBoard - i << "\n"; // номер строки доски справа
    }
    cout << "\n\ta b c d e f g h i j\n"; // нижняя строка
}

// TODO
void Domino::move()
{
    // char *position[2];

    scanf("%c%c %c%c", &posS[0], &posS[1], &posE[0], &posE[1]);
    printf("\n=======================\nYour input: %c%c %c%c\n=======================\n", posS[0], posS[1], posE[0], posE[1]);
    int POSS_x = letterToIndex(posS[0]);
    int POSS_y = int(posS[1]) - 49;
    int POSE_x = letterToIndex(posE[0]);
    int POSE_y = int(posE[1]) - 49;

    int q = sizeof(POSS_x);
    int w = sizeof(POSS_y);
    int e = sizeof(POSE_x);
    int r = sizeof(POSE_y);
    printf("Bytes:\t\t%d%d %d%d\n", q, w, e, r);
    printf("Real input:\t%d%d %d%d\n=======================\n", POSS_x, POSS_y, POSE_x, POSE_y);
    // TODO проверка хода
    // ход компьютера

    // преобразование поля

    // отображение доски
}

char Domino::letterToIndex(char pos)
{
    switch (pos)
    {
    case 'a':
        return 0;
    case 'b':
        return 1;
    case 'c':
        return 2;
    case 'd':
        return 3;
    case 'e':
        return 4;
    case 'f':
        return 5;
    case 'g':
        return 6;
    case 'h':
        return 7;
    case 'i':
        return 8;
    case 'j':
        return 9;
    default:
        return -1;
    }
}

int main(int argc, char *argv[])
{
    // проверка числа аргументов и допустимости позиции
    if (argc != 1)
    {
        std::cout << "Incorrect number of arguments" << std::endl;
        return 1;
    }
    Domino U;
    U.printBoard();

    // TODO  проверка, что координаты корректны
    // отображение хода
    while (getchar() != '\t')
    {
        U.move();       // ход игрока
        U.printBoard(); // вывод доски
    }
    // зеркально ход делает комьютер

    return 0;
}