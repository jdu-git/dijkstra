#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "util.h"

int nextInstruction(char *Word, int *s, int *t){
	
	int returnV;
	
	fscanf(stdin, "%s", Word);
	
	if (strcmp(Word, "Stop")==0){
		return 1;
	}

	if (strcmp(Word, "PrintADJ")==0){
		return 1;
	}
	
	if (strcmp(Word, "SinglePair")==0){
		returnV = fscanf(stdin, "%d %d", s, t);
		if (returnV == 2){
			return 1;
		} else {
			fprintf(stderr, "Error: invalid input\n");
			return 0;
		}
	}
		    
	if (strcmp(Word, "SingleSource")==0){
		returnV = fscanf(stdin, "%d", s);
		if (returnV == 1){
			*t = -1;
			return 1;
		} else {
			fprintf(stderr, "Error: invalid input\n");
			return 0;
		}	
	}
	
	if (strcmp(Word, "PrintLength")==0){
		returnV = fscanf(stdin, "%d %d", s, t);
		if (returnV == 2){
			return 1;
		} else {
			fprintf(stderr, "Error: can not print length\n");
			return 0;
		}
	}

	if (strcmp(Word, "PrintPath")==0){
		returnV = fscanf(stdin, "%d %d", s, t);
		if (returnV == 2){
			return 1;
		} else {
			fprintf(stderr, "Error: can not print path\n");
			return 0;
		}
	}
	return 0;
}

