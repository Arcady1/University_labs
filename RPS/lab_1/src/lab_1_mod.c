/*
Гусаров Аркадий РК6-63Б. Лабораторная работа №1. Вариант №2.

Задание: составить программу, решающую задачу разрешимости логического  выражения,
содержащего  3 переменные (т.е. задачу отыскания значений всех комбинаций 3  логических
переменных, делающих выражение истинным).

Доп. задание: в качестве аргумента командной строки передавать число переменных в выражении.

Компиляция: gcc lab_1_mod.c 
Запуск: ./a.out 4
Пример ввода: a+b+c+c
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool swap_operation(bool a, bool b, char op)
{
    switch (op)
    {
    case '+':
        return a || b;
    case '*':
        return a && b;
    }
}

void correct(bool *pid, int size, char *buf)
{
    bool result; // Результат сравнения

    result = swap_operation(pid[0], pid[1], buf[0]);

    for (int i = 2; i < size; i++)
        result = swap_operation(result, pid[i], buf[i - 1]);

    // Отметка, что выражение истино
    if (result)
        printf("!");
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Неверное количество аргументов\n");
        exit(11);
    }

    const int n = atoi(argv[1]); // Количество логический переменных
    bool pid[n];                 // Массив логических переменных
    char buf[n];                 // Массив логических операций
    int idx = 0;                 // Текущий индекс в buf

    if ((n < 2) || (n > 26))
    {
        printf("Введите число от 2 до 26\n");
        exit(12);
    }

    for (int i = 0; i < n * 2 - 1; i++)
    {
        char c = getchar();

        if (i % 2 == 1)
        {
            buf[idx] = c;
            idx++;
        }
    }

    buf[idx] = '\0';

    // Генерация последовательности из 0 и 1 и вывод на экран
    for (int i = 0; i < n; i++)
    {
        pid_t res = fork();
        pid[i] = !!res;

        // Ожидание завершения дочернего процесса
        wait(NULL);
        
        printf("%d ", pid[i]);
    }

    // Проверка истинности выражения
    correct(pid, n, buf);

    return 0;
}