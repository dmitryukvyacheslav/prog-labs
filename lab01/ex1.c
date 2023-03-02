#include <stdio.h>
#include <stdlib.h>

/*  Было: int* arr, т.е. - принимался NULL по значению.*/ 
void init(int** arr, int n)
{
    /*  Было - arr = malloc... , 
        т.е. - менялось значение переменной arr, локальной
        для функции init.
    */
	*arr = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++)
    {
        /*  Было - arr[i] = i.
            Та же ошибка - arr локален для функции init.
        */
        (*arr)[i] = i;
    }
}

int main(){
	
    int* arr = NULL;
    int n = 10;
    
    /*  Исправлена ошибка: попытка изменить значение по адресу,
        по которому лежит переменная, после её передачи по значению
        Было: init(arr, n)
    */
    init(&arr, n);

    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}
