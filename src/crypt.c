#include "hw4.h"

void copyKey(char *k, char *s){
	int i = 0;
	for(i = 0; i < 26; i++){
		k[i] = s[i];
	}
}


int isValidKeyfile(FILE *keyfile, char *a[], int max_period){
	char s[30];
	int i = 0;
	int pi = 0;
	while(!feof(keyfile)){
		fgets(s, 29, keyfile);
		if(!feof(keyfile)){
			if(strlen(s) != 27){
				fprintf(stderr, "Error: Invalid Key File\n");
				return -1;
			} 
			for(i = 0; i < 26; i++){
				if(s[i] < 'a' || s[i] > 'z'){
					break;
				}
			}
			if(s[i + 1] != 0 && s[i] != '\n'){
				fprintf(stderr, "Error: Invalid Key File\n");
				return -1;
			}
			if(pi < max_period){
				a[pi] = malloc(sizeof(char) * 26);
				copyKey(a[pi], s);				
				pi++;
			}
			
		}
		
	}
	return pi;
}

void crypt(FILE *keyfile, FILE *iFile){
	char *a[300];
	int period = 0;
	int pi = 0;
	char plainText = 0;
	if((period = isValidKeyfile(keyfile, a, 300)) == -1){
		return;
	}
	
	while(!feof(iFile)){
		fread(&plainText, sizeof(char), 1, iFile);
		if(!feof(iFile)){
			if(plainText == '\n'){
				putchar(plainText);
				return;
			}
			else{
				if(plainText < 0x20 || plainText > 0x7e){
					fprintf(stderr, "Error: Unprintable Character discovered");
					return;
				}
				if(pi >= period){
						pi = 0;
				}
				if(plainText >= 'a' && plainText <= 'z'){
					
					putchar(a[pi][plainText - 'a']);
					
				}
				else{
					putchar(plainText);
				}
				pi++;
				
			}
		}
	}
	
}

