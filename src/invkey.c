#include "hw4.h"

void invkey(FILE *kFile){
	char s[30];
	int i = 0;
	int len = 0;
	char a[27];
	while(1){
		i = 0;
		if(fgets(s, 30, kFile) == NULL){
			break;
		}
		len = strlen(s);
		while(i < len){
			a[s[i] - 'a'] = i + 'a';
			i++;
		}
		a[26] = 0;
		fprintf(stdout, "%s\n", a);
	}
}

