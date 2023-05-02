#include <mystring.h>

size_t slen(const char *str){
    int i = 0;
    while(str[i] != '\0') i++;
    return i;
};

// I'm not sure of it
int *stok(char *string, const char *delim, char *ptr[]) {
    char* lexem = string;
    ptr[0] = string;
    int j = 0;
    for (int i = 0; i < slen(string); i++) {
        if (lexem[i] == delim) lexem[i] = '\0';
        lexem = lexem + i + 1;
        ptr[j] = lexem;
        j++;
    }
    return j;
}

int suntok(char str[], char delim, char *ptr[], int cnt) {
    int i;
    for(i = 1; i < cnt; i++) {
        *(ptr[i] - 1) = delim;
    }
    return i;
}

size_t sspn(const char *str, const char *sym) {
    size_t len = 0;
    for(int i = 0; i < slen(str); i++){
        size_t tlen = len;
        for (int k = 0; k < slen(sym); k++) {
            if (str[i] == sym[k]){
                len++;
                break;
            }
        }
        if (tlen == len) return len;
    }
    return len;
}

int scmp( const char * string1, const char * string2 ){
    int i = 0;
    while (string1[i] == string2[i] && string1[i] != '\0' && string2[i] != '\0') 
        i++;
    return string1[i]-string2[i];
}

char *scpy (char *dst, const char *src) {
    for (int i = 0; i < slen(src); i++)
        dst[i] = src[i];
    return dst;
}