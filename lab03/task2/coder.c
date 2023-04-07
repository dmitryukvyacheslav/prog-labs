#include "coder.h"

void printBits(uint8_t num){
    unsigned int size = sizeof(num);
    unsigned int maxPow = 1<<(size*8-1); 
    for(int i=0;i<size*8;++i){
    	// print last bit and shift left.
    	printf("%u",num&maxPow ? 1 : 0);
    	num = num<<1;
	}
}

//	Количество значащих бит кодируемого числа
static const int maxvals[MaxCodeLength] = {256, 2048, 65536, 2097152};
static const int value_bits[MaxCodeLength] = {7, 11, 16, 21};

int encode(uint32_t code_point, CodeUnits *code_units){
	// Нельзя закодировать число больше 2097152 (всего 21 значащий бит)
	if (code_point >= 2097152) return -1;

	// Нахождение количества байт для записи числа
	code_units->length = 1;
	for (int i = 0; i < MaxCodeLength; i++){
		if (code_point >= maxvals[i]) code_units->length++;
		else break;
	}
	
	// Запись числа в кодировке
	int bits_written = 0;
	// Запись единственного байта
	if (code_units->length == 1) {
		bits_written = 7;
		code_units->code[0] = code_point>>1;
		printBits(code_units->code[0]);
		printf("\n");
	}
	// Запись лидирующего и последующих байт
	else {
		for (int i = 0; i < code_units->length; i++){
			if (!i) { 
				// Записать length единиц от начала, пропустить один ноль, записать первые несколько бит числа
				code_units->code[i] = (UINT8_MAX<<(8-(code_units->length))) +
					(code_point>>(value_bits[code_units->length-1]-8+code_units->length+1));
				bits_written = 8-code_units->length-1;
			}
			else {
				// 00000000 00000000 10101000 11001100 
				uint32_t altered_code = code_point;
				// 	<< на количество НЕ значащих бит (32-value_bits[code_units->length-1])
				altered_code<<=(32-value_bits[code_units->length-1]);
				// 10101000 11001100 00000000 00000000
				// 	<< на количество уже прочитанных бит и >> на столько же (занулить их)
				altered_code<<=(bits_written)>>=(bits_written);
				// 00001000 11001100 00000000 00000000
				// 	>> на количество НЕ значащих бит
				// 00000000 00000000 00001000 11001100
				// 	Осталось (значащих-раннее прочитанных) бит от начала
				// 	>> (осталось прочитать - 6)
				// 00000000 00000000 00000000 00100011
				
				code_units->code[i] = 0b10000000 + code // help meeeeeeeee
				bits_written+=6;
			}
			printBits(code_units->code[i]);
			printf(" %d ", bits_written);
		}
		printf("\n");
	}
	return 0;
}
