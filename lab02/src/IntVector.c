#include "IntVector.h"

IntVector *int_vector_new(size_t initial_capacity) {
  /* Выделяем память под массив чисел и структуру.
   * Возвращает:
   * 	указатель на вектор. */
  int* arr = (int *) malloc(sizeof(int) * initial_capacity);
  IntVector *iv = (IntVector *)malloc(sizeof(IntVector));

  if (arr == (int *)NULL || iv == (IntVector *)NULL)
    return (IntVector *)NULL;

  /* Если всё получилось,
   * ставим размер вектора и возвращаем адрес на структуру. */
  iv->size = 0;
  iv->cap = initial_capacity;
  iv->arr = arr;
  return iv;
}

IntVector *int_vector_copy(const IntVector *v) {
  /* Выделяем память под массив чисел и стркутуру копии..
   * Возвращаем NULL, если не получилось. */
  IntVector* iv = int_vector_new(v->cap); 
  if (iv == NULL) return (IntVector*) NULL;
    
  /* Если всё получилось,
   * ставим те же длину и ёмкость, копируем содержимое исходного
   * вектора в копию и возвращаем адрес копии. */
  memcpy(iv->arr, v->arr, v->size);
  iv->cap = v->cap;
  iv->size = v->size;
  return iv;
}

void int_vector_free(IntVector *v) {
  /* Освобождаем память, выделенную под массив числел
   * и под структуру. */
  free(v->arr);
  free(v);
}

static void __throw_index_OOB_error(size_t index, size_t size) {
  /* Выводим ошибку
   * и аварийно завершаем программу при выходе за границы */
  // TODO: сделать вывод имени фунции, в которой произошла ошибка, вместе с её
  // параметрами
  printf("[IV] Guru meditaton.\n\tAttempted to access index (%zu) that is out "
         "of bounds (max index is %zu).",
         index, size - 1);
  exit(-1);
}

int int_vector_get_item(const IntVector *v, size_t index) {
  /* Возвращаем элемент под номером index
   * Advanced: не даём обратиться к элементу за пределами массива */
  if (index < v->size)
    return v->arr[index];
  __throw_index_OOB_error(index, v->size);
  return 0;
}

void int_vector_set_item(IntVector *v, size_t index, int item) {
  /* Ставим элемент под номером index
   * Advanced: не даём обратиться к элементу за пределами массива */
  if (index < v->size)
    v->arr[index] = item;
  else
    __throw_index_OOB_error(index, v->size);
  return;
}

size_t int_vector_get_size(const IntVector *v) {
  // Просто возвращаем размер
  return v->size;
}

size_t int_vector_get_capacity(const IntVector *v) {
  // Просто возвращаем ёмкость
  return v->cap;
}
int int_vector_reserve(IntVector *v, size_t new_capacity) {
  // Ёмкость не растёт в другую сторону
  if (new_capacity <= v->cap)
    return 0;

  // Проверяем, сможем ли мы выделить больше памяти
  // убился головой об стену когда 3 дня не мог отдебажить забытый множитель
  // sizeof(int)
  //int* old_arr = v->arr;
  int* newarr = (int*) realloc(v->arr, new_capacity*sizeof(int));
  if (!newarr)
    return -1; // не можем :(
  v->arr = newarr;
  v->cap = new_capacity;
  return 0;
}

int int_vector_resize(IntVector *v, size_t new_size) {
  // Размер МОЖЕТ расти в другую сторону
  // но перевыделения памяти не происходит - просто уменьшаем размер
  if (new_size <= v->size) {
    v->size = new_size;
    return 0;
  }
  
  // Увеличиваем ёмкость, если новому размеру её не хватает
  if (new_size > v->cap)
    if (int_vector_reserve(v, v->cap + (new_size-(v->cap))))
      return -1; // не получилось

  // инициализация новых ячеек
  size_t old_size = v->size;
  v->size = new_size;
  for (; old_size < v->size; old_size ++){
    int_vector_set_item(v, old_size, 0);
  }

  return 0;
}

int int_vector_push_back(IntVector *v, int item) {
  // увеличиваем ёмкость, если нам её не хватает
  if (int_vector_get_size(v) == int_vector_get_capacity(v)){; 
    if (int_vector_reserve(v, v->cap*2+1))
      return -1;
  }
  v->arr[v->size] = item;
  v->size+=1;
  return 0;
}

void int_vector_pop_back(IntVector *v) {
  // Нет эффекта, если размер равен нулю
  if (v->size <= 0)
    return;
  // Занулить последний элемент и уменьшить размер
  int_vector_set_item(v, v->size-1, 0);
  v->size--;
  return;
}

int int_vector_shrink_to_fit(IntVector *v) {
  // Если размер и ёмкость равны, нет смысла что-то делать
  if (v->size >= v->cap)
    return 0;

  // Выделяем новую память
  // если размер 0 просто освобождаем массив
  if (v->size != 0){ 
    int* newarr = (int *)realloc(v->arr, v->size*sizeof(int));
    if (!newarr) return -1; // не получилось
    v->arr = newarr;
    v->cap = v->size;
  }
  else {
    free(v->arr);
    v->arr = NULL;
  }
  return 0;
}
 