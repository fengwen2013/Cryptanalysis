#include "hw4.h"


int isAlphabetArray(char *s1){
	int i = 0;
	for(; i < strlen(s1); i++){
		if(s1[i] < 'a' || s1[i] > 'z')
			return -1;
	}
	return 0;
}

void formatFloat(char s[]){
	int i = strlen(s);
	for(; i >= 0; i--){
		if(s[i - 1] != '0'){
			s[i] = 0;
			break;
		}
	}
}

void printCount(int max_t, FILE *iFile){
	int t = 1;
	char base = 0;
	char test = 0;
	int count = 0;
	int lenOfFile = 0;
	fseek(iFile, 0, SEEK_END);
	lenOfFile = ftell(iFile);
	int i = 0;
	for(t = 1; t <= max_t; t++){
		for(i = 0, count = 0; i < lenOfFile - t; i++){
			fseek(iFile, i, SEEK_SET);
			fread(&base, sizeof(char), 1, iFile);
			fseek(iFile, i + t, SEEK_SET);
			fread(&test, sizeof(char), 1, iFile);
			if(base == test && base <= 'z' && base >= 'a'){
				count++;
			}
		}
		fprintf(stdout, "t=%d, count=%d\n", t, count);
	}

	fprintf(stdout, "\n");
}

void printFrequency(int count[], FILE *iFile, int *len){
	int i = 0;
	char cipherText = 0;
	int length = 0;
	for(i = 0; i < 26; i++){
		count[i] = 0;
	}
	fseek(iFile, 0, SEEK_SET);
	
	while(!feof(iFile)){
		fread(&cipherText, sizeof(char), 1, iFile);
		if(!feof(iFile)){
			if(cipherText >= 'a' && cipherText <= 'z'){
				length++;
				count[cipherText - 'a']++;
			}
			
		}
	}
	*len = length;
	fprintf(stdout, "L=%d\n", *len);

	for(i = 0; i < 26; i++){
		fprintf(stdout, "f('%c')=%d\n", i + 'a', count[i]);
	}
}

void solve(int max_t, FILE *iFile){
	char *base = NULL;
	char *test = NULL;
	int len = 4;
	int lenOfFile = 0;
	fseek(iFile, 0, SEEK_END);
	lenOfFile = ftell(iFile);
	fseek(iFile, 0, SEEK_SET);
	int i = 0;
	int j = 0;
	int eFlag = 1;
	int count[26];
	int L = 0;
	double IC = 0;
	double E_IC = 0;
	double kp = 0.0658;
	fprintf(stdout, "Kasiski Method\n==============\n");
	char sFloat[20];
	while(1){
		eFlag = 1;
		base = (char *)malloc(sizeof(char) * (len + 1));
		test = (char *)malloc(sizeof(char) * (len + 1));
		for(i = 0; i < lenOfFile - len;i++){
			fseek(iFile, i, SEEK_SET);
			fread(base, sizeof(char), len, iFile);
			base[len] = 0;
			if(isAlphabetArray(base) == 0){
				for(j = i + 1; j <= lenOfFile - len; j++){
					fseek(iFile, j, SEEK_SET);
					fread(test, sizeof(char), len, iFile);
					test[len] = 0;
					if(strcmp(base, test) == 0){
						fprintf(stdout, "len=%d, i=%d, j=%d, j-i=%d, %s\n", len, i, j, j - i, test);
						eFlag = 0;
					}
				}
			}
		}
		
		if(eFlag){
			fprintf(stdout, "len=%d, no more matches\n", len);
			break;
		}
		len++;
	}
	fprintf(stdout, "\nAverage Index of Coincidence\n============================\n");
		
	printFrequency(count, iFile, &L);
	
	for(i = 0, j = 0; i < 26; i++){
		j += count[i] * (count[i] - 1);
	}
	
	IC = j * 1.0 / (L * (L - 1));
	sprintf(sFloat, "%.9f", IC);
	formatFloat(sFloat);
	fprintf(stdout, "IC=%s\n", sFloat);
	
	for(i = 1; i <= max_t; i++){
		E_IC = (L - i) * kp / (i * (L - 1)) + 1.0 * (i - 1) * L / (26 * i * (L - 1));
		sprintf(sFloat, "%.9f", E_IC);
		formatFloat(sFloat);
		fprintf(stdout, "t=%d, E(IC)=%s\n", i, sFloat);
	}
	
	fprintf(stdout, "\nAuto-correlation Method\n=======================\n");
	printCount(max_t, iFile);
	
	
}
