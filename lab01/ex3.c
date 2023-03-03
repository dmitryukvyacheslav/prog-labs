#include <stdio.h>
/*  Исправлена ошибка - неправильный порядок действий 
    после развёртки макроса
    Было: #define SQR(x) x * x
*/
#define SQR(x) ((x) * (x))
int main()
{
 int y = 5;
 int z = 1 / SQR(y + 1);
 printf("z = %d\n", z);
 return 0;
}   
