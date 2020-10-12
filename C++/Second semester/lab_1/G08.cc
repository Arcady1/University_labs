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
using namespace std;

class Domino
{
private:

public:
    friend void printBoard(); // метод отображения доски
};

// TODO
void printBoard()
{
    char s[2];
    int sizeOfBoard = 10;
    // ! const char *mark = ".x+";      // маркер позиции (безопасная / под атакой)
    cout << "\ta b c d e f g h i j\n\n";  // верхняя строка
    for (int i = sizeOfBoard; i > 0; i--) // цикл по строкам
    {
        cout << i << "\t"; // номер строки доски слева
        // ! s[1] = '0' + i;   // текущая позиция по горизонтали
        for (int j = 0; j < sizeOfBoard; j++)
        { // цикл по столбцам
            // ! s[0] = 'a' + j; // текущая позиция по вертикали
            // если позиция не совпадает с положением фигуры, то вывести маркер
            //! char m = (*this != s) ? mark[attack(s)] : isA();
            cout << ". ";
        }
        cout << "\t" << i << "\n"; // номер строки доски справа
    }
    cout << "\n\ta b c d e f g h i j\n"; // нижняя строка
}

int main(int argc, char *argv[])
{
    Domino A;
    printBoard();

    return 0;
}