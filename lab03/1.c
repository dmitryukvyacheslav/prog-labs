#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90) {
        return r % 128;
    }
    if (p < 95) {
        return r % 16384;
    }
    if (p < 99) {
        return r % 2097152;
    }
    return r % 268435455;
}

size_t encode_varint(uint32_t value, uint8_t* buf) {
    assert(buf != NULL);
    uint8_t* cur = buf;
    while (value >= 0x80) {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}

uint32_t decode_varint(const uint8_t** bufp) {
    const uint8_t* cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

int main(void){
	FILE *uncompressed, *compressed;
	uncompressed = fopen("./uncompressed.dat", "w+");
	compressed = fopen("./compressed.dat", "w+");
	for (int i = 0; i < 1000000; i++) {
		uint8_t encode_buf[4];
		size_t encode_len;
		uint32_t random_val = generate_number();
		encode_len = encode_varint(random_val, encode_buf);
		fwrite(encode_buf, encode_len, 1, compressed);
		fwrite(&random_val, sizeof(uint32_t), 1, uncompressed);
	}
	fclose(uncompressed);
	fclose(compressed);
	
	uncompressed = fopen("./uncompressed.dat", "r");
	compressed = fopen("./compressed.dat", "r");
	uint32_t uncomparr[1000000];
	uint32_t comparr[1000000];
	
	// вычитываем весь файл в буфер
	fseek(compressed, 0L, SEEK_END);
	size_t numbytes = ftell(compressed);
	fseek(compressed, 0L, SEEK_SET);
	uint8_t* compfilebuf = malloc(numbytes*sizeof(uint8_t));
	fread(compfilebuf, 1, numbytes, compressed);
	
	for (int i = 0; i < 1000000; i++) {
		uint32_t uncompval, compval;
		fread(&uncompval, sizeof(uint32_t), 1, uncompressed);
		compval = decode_varint(&compfilebuf);
		uncomparr[i] = uncompval;
		comparr[i] = compval;
	}
	printf("Numbers ");
	if (memcmp(uncomparr, comparr, 1000000*sizeof(uint32_t)))
		printf("don't ");
	printf("match\n");
}
