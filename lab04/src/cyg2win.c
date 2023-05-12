#include <cyg2win.h>

int input(char* str, int maxlen){
	fgets(str, maxlen+3, stdin);
	if (slen(str) >= 64)
		return -1;
	str[slen(str)-1] = '\0'; 
	printf("read str[%d] OK: %s\n", slen(str), str);
	printf("nothing left, moving on\n");
	return 0;
}

// Returns positive № for strings that are too long
// Returns negative (symbol index) for first invalid symbol
int check(char* delim, char* paths){
	// Do both strings even exist?
	if (delim == NULL || paths == NULL) return -41205;
	char* ptr[MAX_PATH_LEN];
	int errsym_index;
	// Are there any individual paths longer than 260 symbols?
	int cnt = stok(paths, delim, paths);
	for (int i = 0; i < cnt; i++) {
		if (slen(ptr[i]) > MAX_PATH_LEN) return i+1;
		// Does it contain forbidden symbols?
		int forbidden_pos = sspn(ptr[i], FORBIDDEN_SYMBOLS);
		if (forbidden_pos) return -(errsym_index+forbidden_pos);
		errsym_index += slen(ptr[i]);
	}
	suntok(paths, delim, ptr, cnt); 
}
