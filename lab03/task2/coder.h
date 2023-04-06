#include <stdint.h>
#include <stdio.h>

enum {
    MaxCodeLength = 4
};

/**
 *  Запись числа в кодировке UTF-8.
 *      code — закодированные байты, в порядке от старшего к младшему.
 *      length — количество байт в закодированном представлении.
*/
typedef struct {
    uint8_t code[MaxCodeLength];
    size_t length;
} CodeUnits;

/**
 *  Представить число в кодировке UTF-8.
 *  Параметры:	
 *      code_point – число, которое необходимо закодировать
 *      code_unit – выходной параметр, результат кодирования
 *  Результат:	
 *      0, если кодирование успешно, -1 иначе
 */
int encode(uint32_t code_point, CodeUnits *code_units);

/**
 *  Раскодировать число из UTF-8
 *  Допущение: code_unit - корректный код, полученный с помощью функции read_next_code_unit.
 *  Параметры:	
 *      code_unit – закодированное представление числа
 *  Результат:
 *      code_point - результат декодирования
*/
uint32_t decode(const CodeUnits *code_units);

/**
 *  Считывает последовательность code_units из потока in. 
 *  Implementation note: если считываемый code_unit битый, 
 *  то функция пропускает байты до тех пор, 
 *  пока не найдет корректный лидирующий байт.
 *  Результат:	
 *      0 в случае успеха, -1 в случае ошибки или EOF
 */
int read_next_code_unit(FILE *in, CodeUnits *code_units);

/**
 *  Записывает последовательность code_units в поток out. 
 *  Implementation note: если считываемый code_unit битый, 
 *  то функция пропускает байты до тех пор, 
 *  пока не найдет корректный лидирующий байт.
 *  Результат:	
 *      0 в случае успеха, -1 в случае ошибки или EOF
 */
int write_code_unit(FILE *out, const CodeUnits *code_units);
