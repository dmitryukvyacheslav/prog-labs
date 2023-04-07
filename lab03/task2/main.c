#include "coder.h"

void showHelp() {
    printf("Usage:\n\
coder encode <in-file-name> <out-file-name>\n\
coder decode <in-file-name> <out-file-name>\n");
}

int linear_f(int x){
	int k = 1;
	int b = 1;
	x = k*x+b;
	return x;
}
int main(void){
    CodeUnits cu;
    encode(0xa8cc, &cu);
    
    return 0;
}
