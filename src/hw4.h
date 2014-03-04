#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "time.h"

void keygenCommand(char *argv[], int argc);
void cryptCommand(char *argv[], int argc);
void invkeyCommand(char *argv[], int argc);
void histoCommand(char *argv[], int argc);
void solveCommand(char *argv[], int argc);

void keygen(int period);
void crypt(FILE *keyfile, FILE *iFile);
void invkey(FILE *kFile);
void histo(int period, int which, FILE *iFile);
void solve(int max_t, FILE *iFile);
FILE* openFile(char *fileName);
int optionCheck(char *option, char *check);
int isValidKeyfile(FILE *keyfile, char *a[], int max_period);
