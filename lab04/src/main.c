#include <cyg2win.h>

int main(void){
	printf("Cyg2win - convert Cygwin-style Windows paths to original format\n");
    char delim[MAX_DELIM_SIZE];
    printf("delim: ");
    if (input(delim, MAX_DELIM_SIZE) return -1;
    
    char pathstr[MAX_PATHSTR_SIZE];
    printf("paths: ")
    if (input(delim, MAX_PATHSTR_SIZE)) return -1;   
    
    if (!check(delim, pathstr)) return -1;	
    process(delim, pathstr);
    output(pathstr);
}
