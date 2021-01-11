#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TIME_MODEL 3600;
#define R1 6
#define G1 9
#define B1 11

class System
{
private:
    int id;
    int queue_length;
    double time_free;

public:
    System(int xx = 0, int yy = 0) : id(xx), queue_length(yy){};
    int get_id() { return id; };
    int get_queue_length() { return queue_length; };
    double get_time_free() { return time_free; };
    double set_time_free(double time)
    {
        time_free = time;
        return time_free;
    };
    int set_queue_length(int xx)
    {
        queue_length = xx;
        return queue_length;
    };
};

class Transaction
{
private:
    int id;
    double time_arrive;
    double time_queue;
    double time_service;
    double time_end;

public:
    Transaction(int xx1 = 0, double yy1 = 0, double yy2 = 0, double yy3 = 0, double yy4 = 0) : id(xx1), time_arrive(yy1), time_queue(yy2), time_service(yy3), time_end(yy4){};
    int get_id() { return id; };
    double get_time_arrive() { return time_arrive; };
    double get_time_queue() { return time_queue; };
    double get_time_service() { return time_service; };
    double get_time_end() { return time_end; };
    int set_id(int id1)
    {
        id = id1;
        return id;
    };
    double set_time_arrive(double time)
    {
        time_arrive = time;
        return time_arrive;
    };
    double set_time_queue(double time)
    {
        time_queue = time;
        return time_queue;
    };
    double set_time_service(double time)
    {
        time_service = time;
        return time_service;
    };
    double set_time_end(double time)
    {
        time_end = time;
        return time_end;
    };
};

double uniform(int, double, double);
void file_output(int, int, FILE *, double, int);

int main()
{
    FILE *fp;
    fp = fopen("temp.txt", "w+");
    double global_time = 0.0;
    double max_time = TIME_MODEL;
    int seed, i = 0, j = 0;

    srand(time(NULL));
    Transaction transact[3600];
    System device[1];
    seed = rand();

    while (1)
    {
        float time_arrival = uniform(seed++, 0, R1 + G1 + B1);
        global_time = global_time + time_arrival;

        if (global_time >= max_time)
            break;

        transact[i] = Transaction(i, global_time, global_time, 0, 0);
        i++;
    }

    device[0] = System(1, 0);
    device[1] = System(2, 0);

    int length1 = 0, length2 = 0;
    float time_serv = 0.0;

    for (int j = 0; j < i; j++)
    {
        srand(seed++);
        global_time = transact[j].get_time_queue();
        file_output(3, -1, fp, global_time, j);
        file_output(4, -1, fp, global_time, j);

        if (global_time >= device[0].get_time_free())
        {
            if (length1 > 0)
                length1--;
            device[0].set_queue_length(length1);
        }
        if (global_time >= device[1].get_time_free())
        {
            if (length2 > 0)
                length2--;
            device[1].set_queue_length(length2);
        }
        if ((global_time < device[0].get_time_free()) && (global_time < device[1].get_time_free()) && (device[0].get_queue_length() * device[1].get_queue_length() != 0))
        {
            if ((device[0].get_queue_length() <= device[1].get_queue_length()))
                global_time = device[0].get_time_free();
            else
                global_time = device[1].get_time_free();
        }

        if ((device[0].get_queue_length() <= device[1].get_queue_length()))
        {
            fprintf(fp, "1.\n");
            length1++;
            device[0].set_queue_length(length1);

            file_output(0, 1, fp, global_time, j);

            time_serv = uniform(seed++, R1, R1 + G1 + B1);
            transact[j].set_time_end(global_time + time_serv);

            if (transact[j].get_time_end() > max_time)
                break;

            device[0].set_time_free(transact[j].get_time_end());

            file_output(1, 1, fp, transact[j].get_time_end(), j);
            file_output(2, -1, fp, transact[j].get_time_end(), j);
        }
        else
        {
            fprintf(fp, "2.\n");
            length2++;
            device[1].set_queue_length(length2);
            time_serv = uniform(seed++, G1, R1 + G1 + B1);
            transact[j].set_time_end(global_time + time_serv);

            file_output(0, 2, fp, global_time, j);

            if (transact[j].get_time_end() > max_time)
                break;

            device[1].set_time_free(transact[j].get_time_end());

            file_output(1, 2, fp, transact[j].get_time_end(), j);
            file_output(2, -1, fp, transact[j].get_time_end(), j);
        }
    }

    fprintf(fp, "Время вышло, обслуживание завершено!\n");
    fclose(fp);
}

double uniform(int seed, double min, double max)
{
    srand(seed);
    return ((double)rand() / RAND_MAX) * (max - min) + min;
}

void file_output(int key, int device_id, FILE *fp, double time_, int ident)
{
    switch (key)
    {
    case 0:
        fprintf(fp, "В момент времени %f транзакт с идентификатором %d занял устройство %d.\n", time_, ident + 1, device_id);
        break;

    case 1:
        fprintf(fp, "В момент времени %f транзакт с идентификатором %d освободил устройство %d.\n", time_, ident + 1, device_id);
        break;

    case 2:
        fprintf(fp, "В момент времени %f транзакт с идентификатором %d покинул модель.\n", time_, ident + 1);
        break;
    case 3:
        fprintf(fp, "В момент времени %f транзакт с идентификатором %d вошел в модель.\n", time_, ident + 1);
        break;
    case 4:
        fprintf(fp, "В момент времени %f транзакт с идентификатором %d встал в очередь ", time_, ident + 1);
        break;
    }
}