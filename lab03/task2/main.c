#include <stdio.h>
#include <string.h>
#include <unistd.h>

void showHelp() {
    printf("Usage:\n\
coder encode <in-file-name> <out-file-name>\n\
coder decode <in-file-name> <out-file-name>\n");
}

int main(int argc, char* argv[]){
    /* FILE* input_file = fopen(argv[2], "r");
    FILE* output_file = fopen(argv[3], "w");

    if (argc != 4 ||
        (strcmp(argv[1], "decode") &&
            strcmp(argv[1], "encode")) ||
        !input_file ||
        !output_file) 
    {
        showHelp();
        remove(argv[3]);
        return -1;
    }
    */
    printf("%llu\n", 0xFFFFFFFF>>11);
}
