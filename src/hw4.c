#include "hw4.h"

int main(int argc, char *argv[]){
	if(argc < 2){
		fprintf(stderr, "Error: Too few arguments\n");
		return 0;
	}
	
	if(strcmp(argv[1], "keygen") == 0){
		keygenCommand(argv, argc);
	}
	else{
		if(strcmp(argv[1], "crypt") == 0){
			cryptCommand(argv, argc);
		}
		else{
			if(strcmp(argv[1], "invkey") == 0){
				invkeyCommand(argv, argc);
			}
			else{
				if(strcmp(argv[1], "histo") == 0){
					histoCommand(argv, argc);
				}
				else{
					if(strcmp(argv[1], "solve") == 0){
						solveCommand(argv, argc);
					}
					else{
						fprintf(stderr, "Error: First argument should be (keygen | crypt | invkey | histo | solve!\n)");
						return 0;
					}
				}
			}
		}
	}
	return 0;
}
	

void keygenCommand(char *argv[], int argc){
	int peroid = 0;
	if(argc != 3){
		fprintf(stderr, "Wrong number of arguments for keygen command\n");
		return;
	}
	else{
		if(optionCheck(argv[2], "-t=") == -1){
				return;
		}
		else{
			if(sscanf(argv[2] + 3, "%d", &peroid) == EOF){
				fprintf(stdout, "Can't convert %s into integer", argv[2] + 3);
				return;
			}
			keygen(peroid);
		}
	}
}

void cryptCommand(char *argv[], int argc){
	FILE *ifp = stdin;
	FILE *kfp = NULL;

	if(argc < 3 || argc > 4){
		fprintf(stderr, "Error: Wrong number of arguments for crypt command\n");
		return;
	}
	else{
		if(optionCheck(argv[2], "-k=") == -1){
				return;
		}
		if((kfp = openFile(argv[2] + 3)) == NULL){
			return;
		}
		
		if(argc == 4){
			if((ifp = openFile(argv[3])) == NULL){
				return;	
			}
		}
		crypt(kfp, ifp);
	}
}

void invkeyCommand(char *argv[], int argc){
	FILE *kfp = NULL;
	if(argc != 3){
		fprintf(stderr, "Error: Wrong number of arguments for invkey command\n");
		return;
	}
	
	if((kfp = openFile(argv[2])) == NULL){
		return;
	}
	
	invkey(kfp);
}

void histoCommand(char *argv[], int argc){
	int which = 0;
	int period = 0;
	FILE *ifp = stdin;
	int i = 0;
	char c = 0;

	if((argc < 4) || (argc > 5)){
		fprintf(stderr, "Error: Wrong number of arguments for crypt command\n");
		return;
	}
	else{
		while(i < 2){
			if((c = argv[i+2][0]) != '-'){
				fprintf(stderr, "Error: Lack of hyphen\n");
				return;
			}
			else{
				c = argv[i+2][1];
				switch(c){
				case 't': 
						if(optionCheck(argv[i+2], "-t=") == -1){
							return;
						}
						if(sscanf(argv[i+2] + 3, "%d", &period) == EOF){
							fprintf(stdout, "Can't convert %s into integer", argv[i+2] + 3);
							return;
						}
						break;
				case 'i':
						if(optionCheck(argv[i+2], "-i=") == -1){
							return;
						}
						if(sscanf(argv[i+2] + 3, "%d", &which) == EOF){
							fprintf(stdout, "Can't convert %s into integer", argv[i+2] + 3);
							return;
						}
						break;
				default:
						fprintf(stderr, "Error: invalid commandoption!\n");
						return;
				}				
			}
			i++;
		}
		
		if(argc == 5){
			if((ifp = openFile(argv[4])) == NULL){
				return;
			}
		}
		
		histo(period, which, ifp);
	}
}
void solveCommand(char *argv[], int argc){
	FILE *ifp = NULL;
	int max_t = 0;
	if(argc != 4){
		fprintf(stderr, "Error: Wrong number of arguments for invkey command\n");
		return;
	}
	else{
		if(optionCheck(argv[2], "-l=") == -1){
				return;
		}
		else{ 
			if(sscanf(argv[2] + 3, "%d", &max_t) == EOF){
				fprintf(stdout, "Can't convert %s into integer", argv[2] + 3);
				return;
			}
			
			if((ifp = openFile(argv[3])) == NULL){
				return;	
			}
			solve(max_t, ifp);
		}
	}
}

int optionCheck(char *option, char *check){
	int clen = strlen(check);
	int olen = strlen(option); 
	int i = 0;
	
	if(olen < clen){
		fprintf(stderr, "Error: Wrong option, should be '%soption_value'\n", check);
		return -1;
	}
	while(i < clen){
		if(option[i] != check[i]){
			fprintf(stderr, "Error: Wrong option, should be '%soption_value'\n", check);
			return -1;
		}
		i++;
	}
	return 1;
}

FILE* openFile(char *fileName){
	FILE *ifp = NULL;
	char *mode = "r";
	if(access(fileName, F_OK) == -1){
		fprintf(stderr, "File %s doesn't exsit!\n", fileName);
		return NULL;
	}
	else{
		ifp = fopen(fileName, mode);
		if(ifp == NULL){
			fprintf(stderr, "Error: Can't open %s", fileName);
		}
		return ifp;
	}
}


