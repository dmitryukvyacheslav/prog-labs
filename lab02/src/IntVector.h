#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct intVector {
  size_t size; // длина массива, она же размер
  size_t cap;  // ёмкость массива
  int *arr;    // массив чисел
} IntVector;

/*
 * Создает массив нулевого размера.
 * Параметры:	initial_capacity (size_t) – исходная емкость массива
 * Результат:	указатель на IntVector, если удалось выделить память. Иначе
 * NULL.
 */
IntVector *int_vector_new(size_t initial_capacity);

/* Результат:	Указатель на копию вектора v. NULL, если не удалось выделить
 * память. */
IntVector *int_vector_copy(const IntVector *v);

/* Освобождает память, выделенную для вектора v. */
void int_vector_free(IntVector *v);

/* Результат:	элемент под номером index.
 * В случае выхода за границы массива поведение не определено. */
int int_vector_get_item(const IntVector *v, size_t index);

/* Присваивает элементу под номером index значение item.
 * В случае выхода за границы массива поведение не определено. */
void int_vector_set_item(IntVector *v, size_t index, int item);

/* Результат:	размер вектора. */
size_t int_vector_get_size(const IntVector *v);

/* Результат:	емкость вектора. */
size_t int_vector_get_capacity(const IntVector *v);

/*
 * Добавляет элемент в конец массива.
 * При необходимости увеличивает емкость массива.
 * Результат:	0 в случае успешного добавления элемента, -1 в случае ошибки.
 */
int int_vector_push_back(IntVector *v, int item);

/* Удаляет последний элемент из массива. Нет эффекта, если размер массива равен
 * 0. */
void int_vector_pop_back(IntVector *v);

/* Уменьшает емкость массива до его размера.
 * Результат:	0 в случае успешного изменения емкости, -1 в случае ошибки. */
int int_vector_shrink_to_fit(IntVector *v);

/*
 * Изменяет размер массива.
 * Если новый размер массива больше исходного, то добавленные элементы
 * заполняются нулями. Результат:	0 в случае успеха, -1 в случае ошибки.
 * Если не удалось изменить размер, массив остается в исходном состоянии.
 */
int int_vector_resize(IntVector *v, size_t new_size);

/* Изменить емкость массива.
 * Нет эффекта, если новая емкость меньше либо равна исходной.
 * Результат:	0 в случае успеха, -1 в случае ошибки.
 * Если не удалось изменить емкость, массив остается в исходном состоянии.
 */
int int_vector_reserve(IntVector *v, size_t new_capacity);
