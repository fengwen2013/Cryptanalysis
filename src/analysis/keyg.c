#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

void returnHisto(int s[], int len, int total, char t[], int n){
	int buf = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	char plainF[11][26] = {"etoinsarlhdumpbfcywgvkxqjz",
						  "eiatnosdrlchmgpwuyfbvjkzqx",
						  "etnoairshcldmuyfbpwgvxkjzq",
						  "etasinorlhcdpumbwgyfvxkqjz",
						  "etaonisrhmdcluypwgbfvjxzkq",
						  "etaoisrnhcdumpwlfygbvxzqkj",
						  "etnaorsihldcmfpuyvwgbkqxzj",
						  "eitoasnrhdclupfmygbwvkxqzj",
						  "etosnarihldmcuyfpbgwvkxqjz",
						  "etarisnohlcumdygpwfbvqkxjz",
						  "etisoanrhdlcympgbufwkxvqjz",};
	for(i = 0; i < len; i++){
		for(j = 0, buf = s[0], k = 0; j < len; j++){
			if(buf < s[j]){
				buf = s[j];
				k = j;	
			}
		}
		t[k] = plainF[n - 1][i];
		s[k] = -1;
	}
}

void histo(int period, int which, FILE *iFile){
	int count[26];
	int i = 0;
	char s[period];
	int length = 0;
	char t[27];
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
	returnHisto(count, 26, length, t, which);
	t[26] = 0;
	fprintf(stdout, "%s\n", t);
}


void main(int argc, char *argv[]){
	int i = 1;
	FILE *ifp = fopen(argv[1], "r");
	int period = atoi(argv[2]);
	for(i = 1; i <= period; i++){
		fseek(ifp, 0, SEEK_SET);
		histo(period, i, ifp);
	}
}
