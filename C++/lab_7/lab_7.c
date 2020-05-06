#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
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
        }

        else if (i == 1)
        {
            printf("Введите конечную дату в формате MM.DD.[CC]YY: ");
            scanf("%d.%d.%d", &date_2[0], &date_2[1], &date_2[2]);
        }
    }

    

    // printf("%d ", date_1[0]);
    // printf("%d ", date_1[1]);
    // printf("%d\n", date_1[2]);

    // printf("%d ", date_2[0]);
    // printf("%d ", date_2[1]);
    // printf("%d\n", date_2[2]);

    return 0;
}
