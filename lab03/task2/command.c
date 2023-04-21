#include "command.h"
#include <stdlib.h>
int encode_file(const char *in_file_name, const char *out_file_name){
    FILE* input = fopen(in_file_name, "r");
    FILE* output = fopen(out_file_name, "w");

    if (!input){
        printf("Cannot open input file %s\n", in_file_name);
        return -1;
    }
    if (!output){
        printf("Cannot open output file %s\n", out_file_name);
        return -1;
    }
    
    while (!feof(input)){
        char hexstr[7];
        CodeUnits cu;
        fgets(hexstr, 7, input);
        if (!strcmp(hexstr, "\n")) break;
        printf("%s", hexstr);
        
        uint32_t number = (uint32_t) strtol(hexstr, NULL, 16);
        if (encode(number, &cu)) {
            printf("encode failed!\n");
            printf("number: %d\n", number);
            return -1;
        }
        write_code_unit(output, &cu);
    }
    fclose(input);
    fclose(output);
    return 0;
}
int decode_file(const char *in_file_name, const char *out_file_name){
    FILE* input = fopen(in_file_name, "r");
    FILE* output = fopen(out_file_name, "w");
    if (!input){
        printf("Cannot open input file %s\n", in_file_name);
        return -1;	
    }
    if (!output){
        printf("Cannot open output file %s\n", out_file_name);
        return -1;
    }
    while (!feof(input)){
        CodeUnits cu;
        int ret = read_next_code_unit(input, &cu);
        if (!ret) {
			uint32_t val = decode(&cu);
			char hexstr[16];
			sprintf(hexstr, "%x", val);
			fputs(hexstr, output);
			fputs("\n", output);
		}
    }
    fclose(input);
    fclose(output);
    return 0;
}
