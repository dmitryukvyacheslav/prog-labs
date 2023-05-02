#include <cyg2win.h>
#define MAX_DELIM_SIZE 64
#define MAX_PATHSTR_SIZE 2048
int main(void){
    char delim[MAX_DELIM_SIZE];
    char pathstr[MAX_PATHSTR_SIZE];
    input(delim, pathstr);
    check(delim, pathstr);
    process(delim, pathstr);
    output(pathstr);
}