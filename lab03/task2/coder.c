#include <stdio.h>
#include <string.h>
#include <unistd.h>

void showHelp() {
    printf("Usage:\n\
coder encode <in-file-name> <out-file-name>\n\
coder decode <in-file-name> <out-file-name>\n");
}

int main(int argc, char* argv[]){
    FILE* input_file = fopen(argv[2], "r");
    FILE* output_file = fopen(argv[3], "w");

    /*  Проверка аргументов: их трое, тип верный,
        входной и выходной файлы открылись */
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

    /* Читаем первый байт
    char bytebuf[4];
    char valid_first_byte = 0;
    char byte_count = 0;
    while (!valid_first_byte || !feof(input_file)) {
        fread(bytebuf[0], 1, 1, input_file);
        
        // Подходит шаблону первого бита?
        if ((bytebuf[0]>>7)&1) {
            for (int i = 1; i < 4; i++) 
                if (bytebuf>>7-i)
        }
    }
    */
}