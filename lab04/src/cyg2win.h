#include <mystring.h>
#include <stdio.h>
#include <errno.h>

#define MAX_DELIM_SIZE 64
#define MAX_PATHSTR_SIZE 2048
#define MAX_PATHS 260
#define MAX_PATH_LEN 260
#define FORBIDDEN_SYMBOLS ":\\*?«<\">|"
int input(char* str, int maxlen);
int check(char* delim, char* pathstr);
int process(char* delim, char* pathstr);
int output(char* pathstr);
