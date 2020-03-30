// Гусаров Аркадий РК6-13Б 1 курс. Программа вычисляет корни квадратного уравнения.

#include <stdio.h>
#include <math.h>

float Discr(float, float, float);

int main()
{

    float input();
    float a, b, c;

    a = 0;

    printf("Введите коэффициенты квадратного уравнения:\n");

    while(a == 0)			// тк уравнение квадратное, коэффициент a не должен равняться 0
    {	
		a = input();
    }

    b = input();
    c = input();
    
    Discr(a, b, c);
}

float input()
{

    float digit;
    
    printf("Введите параметр: ");

    while(scanf("%f", &digit) == 0)	// проверка (является ли digit типа float)
    {
        printf("Введите заново: ");
        while(getchar()!='\n');
    }   

    return digit;
}

float Discr(float a, float b, float c)
{

    float x_1, x_2;
    double D;

    D = (b*b) - (4*a*c);
    printf("D = %.2f\n", D);

    if (D > 0)
    {
        x_1 = (-b + sqrt(D))/(2*a);
        x_2 = (-b - sqrt(D))/(2*a);
        
        printf("x1 = %.2f\n", x_1);
        printf("x2 = %.2f\n", x_2);
    }

    else if (D == 0)
    {
        x_1 = (-b)/(2*a);
        
        printf("x = %.2f\n", x_1);
    }
    
    else
    {
        x_1 = sqrt(-D)/(2*a);

        printf("x_1 = %.2f + %.2fi\n", -b/(2*a), x_1);
        printf("x_2 = %.2f - %.2fi\n", -b/(2*a), x_1);
    }
    
    return 0;
}
