#include "hw4.h"

void reorderArray(char a[]){
	int r1 = 0;
	int r2 = 0;
	int len = strlen(a);
	int i = 0;
	
	for(; i < len * 20; i++){
		r1 = rand() % 26;
		r2 = rand() % 26;
		
		if(r1 != r2){
			a[r1] = a[r2] + a[r1];
			a[r2] = a[r1] - a[r2];
			a[r1] = a[r1] - a[r2];
		}
	}
	
}

void keygen(int period){
	int i = 0;

	char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
	srand(time(NULL));
	for(; i < period; i++){
		reorderArray(alphabet);
		fprintf(stdout, "%s\n", alphabet);
	}
}

