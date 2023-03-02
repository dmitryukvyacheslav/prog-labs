#include <stdio.h>

typedef struct
{
	/*	Исправлена ошибка: переполнение массива приводило к перезаписи
		следующего за ним числа 
		Было: char str[3]
	*/
	char str[5];
	int num;
} NumberRepr;

void format(NumberRepr* number)
{
	sprintf(number->str, "%3d", number->num);
}
int main()
{
	NumberRepr number = { .num = 1025 };
	format(&number);
	printf("str: %s\n", number.str);
	printf("num: %d\n", number.num);
	return 0;
}