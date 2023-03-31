#include "coder.h"
enum {
    MaxCodeLength = 4
};

typedef struct {
    uint8_t code[MaxCodeLength];
    size_t length;
} CodeUnits;

// макс. значение - 2^21
int encode(uint32_t code_point, CodeUnits *code_units){
	code_units->length = 1;
	if (code_point > 0xFF>>1)	length++;
	if (code_point > 0xFFFF>>5) length++;
	if (code_point > 0xFFFFFF>>8) length++;
	if (code_point > 0xFFFFFFFF>>11) return -1;
		
	for
}
