#include <stddef.h>

size_t slen(const char *str);
int *stok(char *string, const char *delim, char *ptr[]);
int suntok(char str[], char delim, char *ptr[], int cnt);
size_t sspn (const char *str, const char *sym);
int scmp( const char * string1, const char * string2 );
char *scpy (char *dst, const char *src);