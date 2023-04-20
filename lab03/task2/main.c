#include <stdio.h>
#include "command.h"

void showHelp() {
    printf("Usage:\n\
coder encode <in-file-name> <out-file-name>\n\
coder decode <in-file-name> <out-file-name>\n");
}

int main(int argc, char* argv[]){
    if (argc != 4 || (strcmp(argv[1], "decode") && strcmp(argv[1], "encode"))) {
        showHelp();
        return -1;
    }
    if (!strcmp(argv[1], "encode"))
        encode_file(argv[2], argv[3]);
    else
        decode_file(argv[2], argv[3]);
    return 0;
}
