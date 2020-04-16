// Гусаров Аркадий РК6-13Б 1 курс. Программа выводит на экран значение текущего времени в формате чч.мм.cc.

#include <stdio.h>
#include <time.h>

int main()
{
    int time_ = time(NULL) + 10800;
    
    int time_s = time_ % (24*3600);
    
    int h = time_s / 3600;
    
    time_s = time_s % 3600;
    
    int m = time_s / 60;                    
    int s = time_s % 60;                   
    
    printf("%02d:%02d:%02d\n", h, m, s);
}
