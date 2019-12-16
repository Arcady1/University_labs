// Гусаров Аркадий РК6-13Б 1 курс. Вводится радиус круга R. Определить, сколько точек с целочисленными
// координатами попадают в круг заданного радиуса с центром в начале координат.

#include <stdio.h>
#include <math.h>

float Count(float);
int gip(int, int);

int main()
{
    float input();
    float r;

    r = 0.;

    while (r <= 0.)
    {
        printf("Введите радиус окружности: ");
        r = input();
    }
    Count(r);
    
    return 0;
}

float input(void)
{
    float R;
    
    while(scanf("%f", &R) == 0)
    {
        printf("Введите радиус окружности: ");
        while(getchar() != '\n');
    }
    
    return R;
}

float Count(float r)
{
    float R;
    int r_, x, y, k, gip_;
    
    R = r;
    r_ = (int)R;
    k = (4*r_) + 1;
    
    for (int x = -r_; x < 0; x ++)
    {
        for (int y = -r_; y < 0; y ++)
        {
            gip_ = gip(x, y);
            
            if (gip_ <= R*R)
            {
                k += 4;
            }
        }
    }
    
    printf("Кол-во точек: %d\n", k);
    
    return 0;
}

int gip(int x, int y)
{
    int gipot;
    
    gipot = (x*x) + (y*y);      // не беру корень, поскольку при переводе в десятичную дробь
                                // будет потеря точности (если она бесконечная) => буду сравнивать с r_^2
    return gipot;
}