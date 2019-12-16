// Гусаров Аркадий РК6-13Б 1 курс. Программа  вводит целое положительное число в промежутке от 1 до 100. В соответствии с этим числом сформировать записи трех видов:
// "Ваш возраст 1 год", "Ваш возраст 22 года", "Ваш возраст 75 лет"
// "Вам до совершеннолетия 17 лет", "Вы совершеннолетний 4 года", "Вы совершеннолетний 57 лет"
// "Вам до пенсии 59 лет", "Вам до пенсии 48 лет", "Вы на пенсии 15 лет"

#include <stdio.h>

char* treatment(int);
void str_2(int);
void str_3(int);
int input(void);

int main()
{
	int age;
	
	age = input();
	
	printf("Ваш возраст %d %s\n", age, treatment(age));
    
	str_2(age);
	str_3(age);
	
	return 0;
}

int input(void)		// проверка введенного числа на корректность; ф-ия возвращает проверенное число
{
    int a;
    
    a = 0;
    
    while ((a < 1) | (a > 100))
    {
        printf("Введите возраст: ");
        
        while(scanf("%d", &a) == 0)
        {
            printf("Введите возраст: ");
            while (getchar() != '\n');
        }
    }
    
    return a;
}

void str_2(int age)			// ф-ия формирует вторую строку, которая будет выведена
{
    if (age == 18)
        printf("Вы совершеннолетний\n");
    
    else if (age < 18)
        printf("Вам до совершеннолетия %d %s\n", 18 - age, treatment(18 - age));
        
    else if (age > 18)
        printf("Вы совершеннолетний %d %s\n", age - 18, treatment(age - 18));
}

void str_3(int age)
{
    if (age == 60)
        printf("Вы пенсионер\n");	// ф-ия формирует третью строку, которая будет выведена
        
    else if (age < 60)
        printf("Вам до пенсии %d %s\n", 60 - age, treatment(60 - age));
    
    else if (age > 60)
        printf("Вы на пенсии %d %s\n", age - 60, treatment(age - 60));
}

char* treatment(int age)	// ф-ия получает значение возраста, а возвращает одно из слов "лет", "год", "года"
{
    if ((age % 100 >= 11) & (age % 100 <= 19))
        return "лет";
    
    else
    {
        switch(age % 10)
        {
            case 2:
            case 3:
            case 4:
                return "года";
            case 1:
                return "год";
            default:
                return "лет";
        }
    }
}