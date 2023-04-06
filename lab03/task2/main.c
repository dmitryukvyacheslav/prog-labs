#include "coder.h"

void showHelp() {
    printf("Usage:\n\
coder encode <in-file-name> <out-file-name>\n\
coder decode <in-file-name> <out-file-name>\n");
}

int main(void){
    CodeUnits cu;
    encode(0xa8cc, &cu);
    return 0;
}
