/* Гусаров Аркадий РК6-23Б 1 курс. Программа для вычисление кол-ва прошедших лет и дней между двумя датами.
Запуск: ./a.out */
#include <stdlib.h>
#include <stdio.h>

int leap_year(int);              // ф-ия проверки, являтся ли год високосным; принимает год, возвращает кол-во дней, которое надо прибавить
int days_fD(int[], int[]);       // ф-ия проверки, сколько дней прошло от начальной даты до конца года; принимает начальную дату, возвращает кол-во дней
int days_lD(int[], int[]);       // ф-ия проверки, сколько дней прошло от начала года до конечной даты; принимает конечную дату, возвращает кол-во дней
void Errors_date(int[]);         // ф-ия проверки на ошибки при вводе даты
void Errors_DateS(int[], int[]); // ф-ия проверки на ошибки при вводе дат
int append_year(int);            // ф-ия дописывает год, если введены только две цифры; принимает и возвращает год

int main(int argc, char *argv[])
{
    int i, years, left_D, right_D, days;
    int date_1[3] = {0};
    int date_2[3] = {0};
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // считывание дат в массивы
    for (i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            printf("Введите начальную дату в формате MM.DD.[CC]YY: ");
            scanf("%d.%d.%d", &date_1[0], &date_1[1], &date_1[2]);
            Errors_date(date_1);
            date_1[2] = append_year(date_1[2]);
        }

        else if (i == 1)
        {
            printf("Введите конечную дату в формате MM.DD.[CC]YY: ");
            scanf("%d.%d.%d", &date_2[0], &date_2[1], &date_2[2]);
            Errors_date(date_2);
            date_2[2] = append_year(date_2[2]);
        }
    }

    Errors_DateS(date_1, date_2);

    // кол-во лет между датами (исключая их самих)
    years = (date_2[2] - 1) - date_1[2];

    left_D = days_fD(date_1, month);
    right_D = days_lD(date_2, month);

    days = left_D + right_D;
    years += days / 365;
    days = days % 365;

    printf("Лет: %d\n", years);
    printf("Дней: %d\n", days);

    return 0;
}

int leap_year(int year)
{
    if ((year % 4) == 0)
        return (1);

    else
        return (0);
}

int days_fD(int date_1[], int month[])
{
    int days, i;

    days = 0;
    i = 0;

    // кол-во дней от текущего числа до конца месяца
    days = month[date_1[0] - 1] - date_1[1] + 1;
    // кол-во дней от текущего месяца до конца года
    for (i = date_1[0]; i < 12; i++)
        days += month[i];

    // если указанный месяц янв. - фев. и год - високосный, то прибавляем 1 день
    if ((date_1[0] <= 2) & ((leap_year(date_1[2]) == 1)))
        days++;

    return days;
}

int days_lD(int date_2[], int month[])
{
    int days, i;

    days = 0;
    i = 0;

    // кол-во дней от начала месяца до конечного числа
    days = date_2[1];
    // кол-во дней от начала года до текущего месяца
    for (i = 0; i < date_2[0] - 1; i++)
        days += month[i];

    // если месяц > фев. и год - високосный, то прибавляем 1 день
    if ((date_2[0] > 2) & ((leap_year(date_2[2]) == 1)))
        days++;

    return days;
}

void Errors_date(int date[])
{
    if ((date[0] < 1) | (date[0] > 12))
    {
        printf("Некорректно введен месяц!\n");
        exit(8);
    }

    if ((date[1] < 1) | (date[1] > 31))
    {
        printf("Некорректно введен день!\n");
        exit(9);
    }

    if (date[2] < 0)
    {
        printf("Некорректно введен год!\n");
        exit(10);
    }
}

void Errors_DateS(int date_1[], int date_2[])
{
    if ((date_1[0] == date_2[0]) & (date_1[1] == date_2[1]) & (date_1[2] == date_2[2]))
    {
        printf("Одинаковые даты!\n");
        exit(11);
    }
}

int append_year(int year)
{
    int count;
    int num;

    num = year;
    count = 1;

    // подсчет кол-ва символов
    while (num != 0)
    {
        num /= 10;
        if (num != 0)
            count++;
    }

    if ((count < 1) | (count == 3) | (count > 4))
    {
        printf("Некорректно введен год!\n");
        exit(12);
    }

    if (count == 4)
        return year;

    else if (year <= 20)
        return (2000 + year);

    else
        return (1900 + year);
}