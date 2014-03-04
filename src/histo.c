#include "hw4.h"


void printHisto(int s[], int len, int total){
	int buf = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0; i < len; i++){
		for(j = 0, buf = s[0], k = 0; j < len; j++){
			if(buf < s[j]){
				buf = s[j];
				k = j;	
			}
		}
		fprintf(stdout, "%c: %d (%.2f%%)\n", k + 'a', s[k], s[k] * 100.0 / total);
		s[k] = -1;
	}
}

void histo(int period, int which, FILE *iFile){
	int count[26];
	int i = 0;
	char s[period];
	int length = 0;
	for(; i < 26; i++){
		count[i] = 0;
	}
	
	while(!feof(iFile)){
		fread(s, sizeof(char), period, iFile);
		if(!feof(iFile)){
			if(s[which - 1] >= 'a' && s[which - 1] <= 'z'){
				count[s[which - 1] - 'a']++;
				length++;
			}
		}
	}
	fprintf(stdout, "L=%d\n", length);
	printHisto(count, 26, length);
}
