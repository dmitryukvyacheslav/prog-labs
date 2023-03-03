#include "IntVector.h"

IntVector* int_vector_new(size_t initial_capacity){
	/* Выделяем память под массив чисел и структуру.
	 * Возвращаем NULL, если хотя бы одно не получилось. */
	int* arr = malloc(sizeof(int)*initial_capacity));
	IntVector* iv = malloc(sizeof(IntVector));	
	if (!arr || !iv) return NULL;		
					
	/* Если всё получилось, 
	 * ставим размер вектора и возвращаем адрес на структуру. */
	iv->cap = initial_capacity;
	iv->arr = arr;
	return iv;
}

IntVector* int_vector_copy(const IntVector *v){
	/* Выделяем память под массив чисел и стркутуру копии..
	 * Возвращаем NULL, если хотя бы одно не получилось. */
	int* arr = malloc(sizeof(int)*initial_capacity));
	IntVector* iv = malloc(sizeof(IntVector));	
	if (!arr || !iv) return NULL;		
					
	/* Если всё получилось, 
	 * ставим те же длину и ёмкость, копируем содержимое исходного
	 * вектора в копию и возвращаем адрес копии. */
	iv->cap = v->cap;
	iv->size = v->size;
	memcpy(iv->arr, v->arr, v->size);
	return iv;
}

void int_vector_free(IntVector *v) {
	/* Освобождаем память, выделенную под массив числел 
	 * и под структуру. */
	 free(v->arr);
	 free(v);
}

void __throw_index_OOB_error(size_t index, size_t size){
	/* Выводим ошибку 
	 * и аварийно завершаем программу при выходе за границы */
	int_vector_free(*v)
	//TODO: сделать вывод имени фунции, в которой произошла ошибка, вместе с её параметрами
	printf("Произошла ошибка.\nПопытка обращения к индексу (%d) за границами вектора (макс. индекс - %d).", index, size-1);
	exit(-1);
}

int int_vector_get_item(const IntVector *v, size_t index){
	/* Возвращаем элемент под номером index	 
	 * Advanced: не даём обратиться к элементу за пределами массива */
	if (index<size) return v->arr[index];	
	__throw_index_OOB_error(index, size);
}

void int_vector_set_item(IntVector *v, size_t index, int item){
	/* Ставим элемент под номером index	 
	 * Advanced: не даём обратиться к элементу за пределами массива */
	if (index<size) v->arr[index] = item;
	else __throw_index_OOB_error(index, size);
}

size_t int_vector_get_size(const IntVector *v){
	return v->size;
}

size_t int_vector_get_capacity(const IntVector *v){
	return v->cap;
}

int int_vector_push_back(IntVector *v, int item){
	if
}

