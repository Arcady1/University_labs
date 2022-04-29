/*
Гусаров Аркадий РК6-63Б. Лабораторная работа №1. Вариант №2.

Задание: составить программу, решающую задачу разрешимости логического  выражения,
содержащего  3 переменные (т.е. задачу отыскания значений всех комбинаций 3  логических
переменных, делающих выражение истинным).

Компиляция: gcc lab_1.c
Запуск: ./a.out
Пример ввода: a*b+c
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool switch_op(bool a, bool b, char op)
{
    switch (op)
    {
    case '+':
        return a || b;
    case '*':
        return a && b;
    }
}

void check(bool *pid, int size, char *buf)
{
    bool result; // Результат сравнения
    char chars[3];
    char *smb1 = "+";
    char *smb2 = "*";

    if ((buf[0] == *smb1) & (buf[1] == *smb2))
    {
        result = switch_op(pid[1], pid[2], buf[1]);
        result = switch_op(result, pid[0], buf[0]);
    }
    else
    {
        result = switch_op(pid[0], pid[1], buf[0]);
        result = switch_op(result, pid[2], buf[1]);
    }

    // Отметка, что выражение истино
    if (result)
        printf("*");
    printf("\n");
}

int main()
{
    const int n = 3; // Количество логический переменных
    bool pid[n];     // Массив логических переменных
    char buf[n];     // Массив логических операций
    int idx = 0;     // Текущий индекс в buf

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
    check(pid, n, buf);

    return 0;
}