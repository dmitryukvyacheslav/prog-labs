#include <cyg2win.h>

// maxlen - сколько символов может быть
// не забыть про:
// - признак конца строки
// - канарейку от переполнения
// - грязный хак для удаления переноса строки
int input(char* str, int maxlen){
	fgets(str, maxlen+3, stdin); //
	if (slen(str) >= maxlen+2)
		return -1;
	str[slen(str)-1] = '\0'; 
	return 0;
}

// returns index+1by of the  first invalid symbol

// this is super broken
int check(char* delim, char* paths){
	// Do both strings even exist?
	if (delim == NULL || paths == NULL) return -1;
	char* ptr[MAX_PATH_LEN];
	int errsym_index;
	// Are there any individual paths longer than 260 symbols?
	int cnt = stok(paths, *delim, ptr);
	for (int i = 0; i < cnt; i++) {
		if (slen(ptr[i]) > MAX_PATH_LEN) return i+1;
		// Does it contain forbidden symbols?
		int forbidden_pos = sspn(ptr[i], FORBIDDEN_SYMBOLS);
		if (forbidden_pos) return -(errsym_index+forbidden_pos);
		errsym_index += slen(ptr[i]);
	}
	suntok(paths, *delim, ptr, cnt); 
	return 0;
}
