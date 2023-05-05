#include <cyg2win.h>

int input(char* str, int maxlen){
	if (!fgets(str, maxlen, stdin)){
		if (ferror()) return -1;
		if (feof()) return -2;
		return -3;	// unknown error
	}
	return 0;
}

// Returns positive № for strings that are too long
// Returns negative (symbol index) for first invalid symbol
int check(char* delim, char* paths){
	// Do both strings even exist?
	if (delim == NULL || paths == NULL) return -41205;
	
	int errsym_index;
	// Are there any individual paths longer than 260 symbols?
	int cnt = stok(paths, delim, paths);
	for (int i = 0; i < cnt; i++) {
		if (slen(ptr[i])) > MAX_PATH_LEN return i+1;
		// Does it contain forbidden symbols?
		int forbidden_pos = sspn(ptr[i], FORBIDDEN_SYMBOLS);
		if (forbidden_pos) return -(errsym_index+forbidden_pos);
		errsym_index += slen(ptr[i]);
	}
	suntok(paths, delim, ptr, cnt); 
}
