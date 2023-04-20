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

// LUT
static const int maxvals[MaxCodeLength] = {128, 2048, 65536, 2097152};
static const int value_bits[MaxCodeLength] = {7, 11, 16, 21};
static const int first_byte_masks[MaxCodeLength] = {0b01111111, 0b00011111, 0b00001111, 0b00000111};
static const int header_masks[MaxCodeLength] = {0b01111111, 0b11011111, 0b11101111, 0b11110111};


int encode(uint32_t code_point, CodeUnits *code_units){
	if (code_point >= 2097152) return -1;

	code_units->length = 1;
	for (int i = 0; i < MaxCodeLength; i++){
		if (code_point >= maxvals[i]) code_units->length++;
		else break;
	}										
	
	int bits_written = 0;
	if (code_units->length == 1) {
		bits_written = 7;
		code_units->code[0] = code_point>>1;
		printBits(code_units->code[0]);
		printf("\n");
	}
	else {
		int len = code_units->length;
		int valbits = value_bits[code_units->length-1];	//  
		for (int i = 0; i < code_units->length; i++){
			if (!i) { 
				code_units->code[i] = (UINT8_MAX<<(8-len)) +
					(code_point>>(valbits-8+len+1));
				bits_written = 8-len-1;
			}
			else {
				code_units->code[i] = (uint8_t) 
					(0b00111111 & (code_point >> (valbits-bits_written-6)))
					+ 0b10000000;
				bits_written += 6;
			}
			//printBits(code_units->code[i]);
			//printf(" %d ", bits_written);
		}
		//printf("\n");
	}
	return 0;
}

uint32_t decode(const CodeUnits *code_unit) {
	int shift = 0;
	uint32_t ret = 0;
	int len = code_unit->length;
	for (int i = len-1; i>=0; i--){
		if (!i) {
			ret += ((code_unit->code[i] & first_byte_masks[len-1]) << shift);
			break;
		}
		ret += ((code_unit->code[i] & 0b00111111) << shift);
		shift+=6;
	}
	return ret;
} 

int read_next_code_unit(FILE *in, CodeUnits *code_units){
	int is_byte_correct = 0;
	int len = 0;
	uint8_t code[4];
	while(!is_byte_correct){
		if (!fread(&code, sizeof(uint8_t), 1, in)) return -1; // EOF
		for (int i = 0; i < MaxCodeLength; i++){
			if (code[0] == (code[0]&header_masks[i])) {
				len = i+1;
				is_byte_correct = 1;
				break;
			}
		}
	}
	if (code_units->length == 1){
		memcpy(code_units->code, code, len*sizeof(uint8_t));
		return 0;
	}
	// read next bytes
	int bytes_left = code_units->length-1;
	for (int i = 1; i <= bytes_left; i++){
		if (!fread(code+i, sizeof(uint8_t), 1, in)) return -1; // EOF
		if (code[i] != (code[i] & 0b10111111)) return -1; // data lost
	}
	code_units->length = len;
	memcpy(code_units->code, code, len*sizeof(uint8_t));
	return 0;
}

 int write_code_unit(FILE *out, const CodeUnits *code_unit){
	return (fwrite(code_unit->code, sizeof(uint8_t), code_unit->length, out) 
		== code_unit->length) ? 0 : -1;
 }

