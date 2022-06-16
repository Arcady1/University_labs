/*
Гусаров Аркадий РК6-63Б. Лабораторная работа №4. Вариант №10.

Задание: Разработать средствами MPI параллельную программу решения уравнения струны методом конечных разностей
с использованием явной вычислительной схемы. Временной интервал моделирования и количество (кратное 8)
узлов расчетной сетки - параметры программы.
Уравнение струны имеет следующий вид:

d^2*z / dt^2 = a^2 * (d^2*z / dx^2) + f(x,t), где

t - время,
x - пространственная координата, вдоль которой ориентирована струна,
z - отклонение (малое) точки струны от положения покоя,
a - фазовая скорость,
f(x,t) - внешнее "силовое" воздействие на струну.

Предусмотреть возможность задания ненулевых начальных условий и ненулевого внешнего воздействия.
Количество элементов в сетке и временной интервал моделирования - параметры программы.
Программа должна демонстрировать ускорение по сравнению с последовательным вариантом.
Предусмотреть визуализацию результатов посредством утилиты gnuplot. При этом утилита gnuplot должна вызываться
отдельной командой после окончания расчета.

При выполнении данной лабораторной работы используется виртуальный вычислительный кластер МГТУ.
Для получения терминального доступа к вычислительному кластеру необходимо выполнить команду
ssh user@rk6.clusters.bmstu.ru
, где user - одно из имен student1, student2, ..., student9. Работать одновременно под одним именем нескольким пользователям настоятельно не рекомендуется.

Для загрузки на кластер исходных файлов программ необходимо использовать команду
sftp user@rk6.clusters.bmstu.ru
Компиляция и компоновка исполняемого файла прикладной программы выполняется командой
mpicc -o prg prg.c
Запуск исполняемого файла на 4 узлах кластера по 1 процессу на узел осуществляется командой
mpiexec -f ~/.machinefile -n 4 ./prg

Перед выходом с кластера обязательно удалить все временные файлы!!!

Для визуализации результатов решения задачи идеально подходит стандартная для UNIX рутина gnuplot.
Для перенаправления графического вывода gnuplot (и любой другой графической программы, например, kedit) на экран локальной машины пользователя необходимо:
- на локальной машине выполнить команду "xhost +" (разрешение локальному X-серверу принимать запросы от любого узла сети);
- на кластере выполнить команду "export DISPLAY=localIP:0.0", где localIP - IP-адрес локальной машины.

?
Компиляция:
    $ mpicc -o prg lab_4.c
?
Запуск:
    На сервере:
    $ mpiexec -f ~/.machinefile -n 4 ./prg 16 2000
    Локально:
    $ ./prg # #

    $ gnuplot 'script.dat'
?
Коротко:
    $ mpicc -o prg lab_4.c && mpiexec -f ~/.machinefile -n 4 ./prg # #
    $ ./prg # # && gnuplot 'script.dat'
?
Варианты запуска:
1) Одна сила в центре
XRANGE 20
./prg 20 2000 && gnuplot 'script.dat'

2) Две силы по бокам
XRANGE 40
./prg 40 2000 && gnuplot 'script.dat'

3) Одна сила справа
XRANGE 20
./prg 16 2000 && gnuplot 'script.dat'

Кол-во процессов    Время выполнения, с
    1               111.101
    2               53.067
    4               28.54
    8               16.325

Граничное условие 1-го рода в центре, в серелине 1-ой половины и 2-ой. 
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
// #include "/home/arcady/anaconda3/pkgs/mpich-3.3.2-hc856adb_0/include/mpi.h"
#include "mpi/mpi.h"

#define A 0.5
#define LEFT 1
#define RIGHT 2
#define LENGTHX 20
#define LENGTHT 200
#define LENGTHY 10
#define XRANGE 40

// Комментирование этой строки приведет к отсутсвию вывода
#define GNUPLOT

double dx;
double dt;
double dx2;
double dt2;
double a2;
FILE *out, *fp;

struct timeval tv1, tv2, dtv;
struct timezone tz;

void time_start()
{
    gettimeofday(&tv1, &tz);
}

void writeIntoFile(double *Z, int lengthX, double CurrentTime)
{
    int i, k;

    for (i = 0; i < lengthX; i++)
        fprintf(out, "%d\t%lf\n", i * (int)dx, Z[i]);
    fprintf(out, "\n");
    fprintf(out, "\n\n");
}

// Генерация скрипта Gnuplot
void GenerateGnuplot(int timeInterval)
{
    out = fopen("out.txt", "w");
    fp = fopen("script.dat", "w");
    fprintf(fp, "set cbrange [0.9:1]\n");
    // fprintf(fp, "set xrange [0:%d]\n", (int)LENGTHX - (int)dx);
    fprintf(fp, "set xrange [0:%d]\n", (int)XRANGE);
    fprintf(fp, "set yrange [-%d:%d]\n", (int)LENGTHY, (int)LENGTHY);
    fprintf(fp, "set palette defined (1 '#ce4c7d')\n");
    fprintf(fp, "set style line 1 lc rgb '#b90046' lt 1 lw 0.5\n");
    fprintf(fp, "do for [i=0:%d] {\n", (int)LENGTHT - 1);
    fprintf(fp, "plot 'out.txt' index i using 1:2 smooth bezier\n");
    fprintf(fp, "pause 0.1}\npause -1\n");
}

// Задание граничных условий
void FirstCalculation(double *Z0, double *Z1, int lengthX)
{
    int i;

    for (i = 0; i < lengthX; i++)
    {
        Z0[i] = Z1[i] = 0;
    }
    writeIntoFile(Z0, lengthX, 0);
}

// Внешняя сила
double F(int x, double curtime, int a)
{
    if (curtime <= 5 && (int)x == a)
    {
        return 1;
    }
    return 0;
}

int time_stop()
{
    gettimeofday(&tv2, &tz);
    dtv.tv_sec = tv2.tv_sec - tv1.tv_sec;
    dtv.tv_usec = tv2.tv_usec - tv1.tv_usec;

    if (dtv.tv_usec < 0)
        dtv.tv_sec--;
    dtv.tv_usec += 1000000;

    return dtv.tv_sec * 1000 + dtv.tv_usec / 1000;
}

// Аргумент Z0 всегда текущий, а Z1 - предыдущий
// Z0 может быть как Z0, так и Z1
void calculate(double *Z0, double *Z1, int lengthX, double CurrentTime, int myrank, int total, double *zleft, double *zright)
{
    int i;
    int index;

    if (myrank != 0)
    {
        index = 0;
        Z1[index] = dt2 * (a2 * (*zleft - 2 * Z0[index] + Z0[index + 1]) / dx2 +
                           F(myrank * lengthX + index, CurrentTime, 10) -
                           F(myrank * lengthX + index, CurrentTime, 25)) +
                    2 * Z0[index] - Z1[index];
        *zleft = Z1[index];
    }

    for (i = 1; i < lengthX - 1; i++)
    {
        index = i;
        Z1[index] = dt2 * (a2 * (Z0[index - 1] - 2 * Z0[index] + Z0[index + 1]) / dx2 +
                           F(myrank * lengthX + index, CurrentTime, 10) -
                           F(myrank * lengthX + index, CurrentTime, 25)) +
                    2 * Z0[index] - Z1[index];
    }

    if (myrank != total - 1)
    {
        index = lengthX - 1;
        Z1[index] = dt2 * (a2 * (Z0[index - 1] - 2 * Z0[index] + *zright) / dx2 +
                           F(myrank * lengthX + index, CurrentTime, 10) -
                           F(myrank * lengthX + index, CurrentTime, 25)) +
                    2 * Z0[index] - Z1[index];
        *zright = Z1[index];
    }

    // Крайние узлы
    // Если это не последний процесс, то нужен правый ряд
    if (myrank != total - 1)
    {
        // Кидаем правую часть следующему процессу
        MPI_Send((void *)zright, 1, MPI_DOUBLE, myrank + 1, LEFT, MPI_COMM_WORLD);

        // Ловим левую часть следующего процесса
        // Для вычисляющего процесса это будет правой
        MPI_Recv((void *)zright, 1, MPI_DOUBLE, myrank + 1, RIGHT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Если это не нулевой процесс, то нужно получить левый ряд
    if (myrank != 0)
    {
        // Кидаем левую часть предыдущему процессу
        MPI_Send((void *)zleft, 1, MPI_DOUBLE, myrank - 1, RIGHT, MPI_COMM_WORLD);

        // Ловим правую часть предыдущего процесса
        // Для вычисляющего процесса это будет левой
        MPI_Recv((void *)zleft, 1, MPI_DOUBLE, myrank - 1, LEFT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

int main(int argc, char **argv)
{
    // Номер процесса, кол-во процессов
    int myrank, total;

    double *Z0;
    double *Z1;
    double *z0;
    double *z1;
    double zleft;
    double zright;
    double *tmp;

    if (argc < 3)
    {
        printf("./a.out <lengthX> <timeInterval>\n");
        exit(0);
    }

    // Сетка по х
    int lengthX = atoi(argv[1]);

    // Временной интервал
    double timeInterval = atof(argv[2]);

    if (lengthX > LENGTHX)
        dx = 1.0;
    else
        dx = LENGTHX / lengthX;

    if (timeInterval > LENGTHT)
        dt = 1.0;
    else
        dt = timeInterval / LENGTHT;

    dx2 = dx * dx;
    dt2 = dt * dt;
    a2 = A * A;

    // Текущий момент времени
    double CurrentTime = dt;

    // В какой массив записывать
    int znumber = 1;

    // Инициализация коммуникационных средств MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    // Узлов на один процесс
    int newlengthX = lengthX / total;

    // Остаток
    int lengthXmod = lengthX % total;

    if (myrank == 0)
    {
        GenerateGnuplot(timeInterval);

        // Значение узлов в текущий момент времени
        Z0 = (double *)calloc(lengthX, sizeof(double));

        // Значение узлов в предыдущий момент времени
        Z1 = (double *)calloc(lengthX, sizeof(double));

        FirstCalculation(Z0, Z1, lengthX);

        if (myrank == total - 1)
        {
            newlengthX += lengthXmod;
        }

        // Для каждого процесса (включая нулевой) выделяем память
        z0 = (double *)calloc(newlengthX, sizeof(double));
        z1 = (double *)calloc(newlengthX, sizeof(double));

        // Каждому процессу передадим необходимую часть
        int *sendArr;
        sendArr = (int *)calloc(total, sizeof(int));

        int i;

        for (i = 0; i < total; i++)
            sendArr[i] = i * newlengthX;

        int *sendArrCount;
        sendArrCount = (int *)calloc(total, sizeof(int));

        for (i = 0; i < total; i++)
            sendArrCount[i] = newlengthX;

        sendArrCount[total - 1] += lengthXmod;

        // Разбрызгиватель
        MPI_Scatterv((void *)(Z0), sendArrCount, sendArr,
                     MPI_DOUBLE, (void *)(z0), newlengthX,
                     MPI_DOUBLE, 0, MPI_COMM_WORLD);

        MPI_Scatterv((void *)(Z1), sendArrCount, sendArr,
                     MPI_DOUBLE, (void *)(z1), newlengthX,
                     MPI_DOUBLE, 0, MPI_COMM_WORLD);

        zleft = z0[0];
        zright = z0[newlengthX - 1];

        // Если это не последний процесс, то нужен правый
        if (myrank != total - 1)
        {
            // Кидаем правую часть следующему процессу
            MPI_Send((void *)&zright, 1, MPI_DOUBLE, myrank + 1, LEFT, MPI_COMM_WORLD);

            // Ловим левую часть следующего процесса
            MPI_Recv((void *)&zright, 1, MPI_DOUBLE, myrank + 1, RIGHT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Если это не нулевой процесс, то нужно получить левый ряд
        if (myrank != 0)
        {
            // Кидаем левую часть предыдущему процессу
            MPI_Send((void *)&zleft, 1, MPI_DOUBLE, myrank - 1, RIGHT, MPI_COMM_WORLD);

            // Ловим правую часть предыдущего процесса
            // Для вычисляющего процесса это будет левой
            MPI_Recv((void *)&zleft, 1, MPI_DOUBLE, myrank - 1, LEFT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        if (myrank == 0)
            time_start();

        while (CurrentTime < timeInterval)
        {
            if (znumber == 1)
                calculate(z0, z1, newlengthX, CurrentTime, myrank, total, &zleft, &zright);
            else
                calculate(z1, z0, newlengthX, CurrentTime, myrank, total, &zleft, &zright);

#ifdef GNUPLOT
            if (znumber == 1)
            {
                MPI_Gatherv((void *)z1, newlengthX, MPI_DOUBLE,
                            (void *)(Z1), sendArrCount, sendArr,
                            MPI_DOUBLE, 0, MPI_COMM_WORLD);
                if (myrank == 0)
                    // Запись в gnuplot
                    writeIntoFile(Z1, lengthX, CurrentTime);
            }
            else
            {
                MPI_Gatherv((void *)z0, newlengthX, MPI_DOUBLE,
                            (void *)(Z0), sendArrCount, sendArr,
                            MPI_DOUBLE, 0, MPI_COMM_WORLD);
                if (myrank == 0)
                    // Запись в gnuplot
                    writeIntoFile(Z0, lengthX, CurrentTime);
            }

            // Ждем запись
            MPI_Barrier(MPI_COMM_WORLD);
#endif
            if (!myrank)
            {
                znumber *= -1;
                CurrentTime += dt;
            }

            MPI_Bcast((void *)&znumber, 1, MPI_INT, 0, MPI_COMM_WORLD);

            // Делимся со всеми процессами значением времени на текущем
            // шаге, это нужно для того, чтобы правильно рассчитывалось
            // внешнее воздействие на каждый узел, которое зависит от
            // координаты и времени
            MPI_Bcast((void *)&CurrentTime, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }

        // Вывод времени работы
        if (myrank == 0)
        {
            int ms = time_stop();
            printf("Time: %d milliseconds\n", ms);
            free(Z0);
            free(Z1);
        }

        // Освобождение выделенной памяти
        free(z0);
        free(z1);
        free(sendArr);
        free(sendArrCount);
        MPI_Finalize();
        exit(0);
    }
}