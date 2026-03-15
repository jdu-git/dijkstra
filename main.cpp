#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cfloat>
#include "data_structures.h"
#include "util.h"
#include "stack.h"
#include "graph.h"
#include "heap.h"
#include "main.h"

int main(int argc, char **argv){
	FILE *fp1;
	FILE *fp2;
	pVERTEX *V;
	pNODE *ADJ;
	pHEAP heap;	
	int returnV, flag, n, m;
	int s, t, source, destination;
	char Word[100];	

	// check command line arguments
	if (argc != 4){
		fprintf(stderr, "Usage: %s <InputFile> <GraphType> <Flag>\n", argv[0]);
		exit(1);
	}
       
	if (strcmp(argv[2], "DirectedGraph") != 0 and (strcmp(argv[2], "UndirectedGraph") != 0)){
		fprintf(stderr, "Usage: %s <InputFile> <GraphType> <Flag>\n", argv[0]);
		exit(1);
	}

	flag = atoi(argv[3]);

	if (flag < 0 or flag > 1){
		fprintf(stderr, "Usage: %s <InputFile> <GraphType> <Flag>\n", argv[0]);
		exit(1);
	}
	
	V = NULL;
	ADJ = NULL;
	source = -1;
	destination = -1;
	fp1 = NULL;
	fp2 = NULL;

	// read from the file
	fp1 = fopen(argv[1], "r");
	if (!fp1){
		fprintf(stderr, "Error: can not open file %s\n", argv[1]);
		exit(1);
	}

	if (fscanf(fp1, "%d %d", &n, &m) != 2){
		fprintf(stderr, "Error reading n and m.\n");
		exit(1);
	}
	
	// pointer to vertices array
	V = (pVERTEX*)calloc(n + 1, sizeof(pVERTEX));
	for (int i = 1; i <= n; i++){
		V[i] = (pVERTEX)calloc(1, sizeof(VERTEX)); // populate vertices array
		V[i]->index = i; // permanent location
	}
	
	// ----- ADJACENCY LIST ------
	// initialize and scan adj list node data
	ADJ = (pNODE*)calloc(n + 1, sizeof(pNODE));
	int edgeIndex, u, v;
	double w;
	
	for (int i = 1; i <= m; i++){

		if (fscanf(fp1, "%d %d %d %lf", &edgeIndex, &u, &v, &w) != 4){
			fprintf(stderr, "Error: can not populate adjacency list\n");
			exit(1);
		}

		//initialize newNODE from file data
		pNODE newNODE = (pNODE)calloc(1, sizeof(NODE));
		
		newNODE->index = edgeIndex;
		newNODE->u = u;
		newNODE->v = v;
		newNODE->w= w;
		
		// directed graph insert at rear or head of ADJ[u]
		if (strcmp(argv[2], "DirectedGraph")==0){ 
			if (flag == 1) {
				if (ADJ[u] == NULL){
					ADJ[u] = newNODE;
				} else {
					pNODE current = ADJ[u];
					while (current->next != NULL){
						current = current->next;
					}
				current->next = newNODE;
				}
			} else {
				newNODE->next = ADJ[u];
				ADJ[u] = newNODE;
			}	
		}
		// initialize second node for ADJ[v];
		pNODE vnewNODE = (pNODE)calloc(1, sizeof(NODE));

		vnewNODE->index = edgeIndex;
		vnewNODE->u = v;
		vnewNODE->v = u;
		vnewNODE->w = w;
		// undirected graph at rear and head of ADJ[u] AND ADJ[v]
		if (strcmp(argv[2], "UndirectedGraph")==0){
			if (flag == 1){
				//insert for u
				if (ADJ[u] == NULL){
					ADJ[u] = newNODE;
				} else {
					pNODE current = ADJ[u];
					while (current->next != NULL){
						current = current->next;
					}
					current->next = newNODE;
				}
				
				// insert for v
				if (ADJ[v] == NULL){
					ADJ[v] = vnewNODE;
				} else {
					pNODE current = ADJ[v];
					while (current->next != NULL){
						current = current->next;
					}
					current->next = vnewNODE;
				}
				//insert at head
			} else {
				newNODE->next = ADJ[u];
				ADJ[u] = newNODE;
				
				vnewNODE->next = ADJ[v];
				ADJ[v] =vnewNODE;
			}
		}
	}
	fclose(fp1);

	// initialize priority queue and stack
	heap = (pHEAP)calloc(1, sizeof(HEAP));
	heap->capacity = n;
	heap->size = 0;
	heap->H = (pELEMENT*)calloc(n + 1, sizeof(pELEMENT));

	pSTACK stack = (pSTACK)calloc(1, sizeof(STACK));
	stack->items = (int*)calloc(n, sizeof(int));
	stack->top = -1;
	stack->size = n;

	if (!stack){
		fprintf(stderr, "Error: can not allocate memory for stack\n");
		exit(1);
	}

	// loop over instructions
	while (1){

		returnV = nextInstruction(Word, &s, &t);
		
		if (returnV == 0){
			fprintf(stderr, "Invalid instruction\n");
			continue;
		}
		if (strcmp(Word, "Stop")==0){
			if (fp2){
				fclose(fp2);
			}
			return 0;
		}
		
		if (strcmp(Word, "PrintADJ")==0){
			for (int i = 1; i <= n; i++){
				fprintf(stdout, "ADJ[%d]:", i);
				pNODE current = ADJ[i];
				while (current != NULL){
					fprintf(stdout,"-->[%d %d: %.2f]", i, current->v, current->w);
					current = current->next;
				}
				fprintf(stdout, "\n");
			}
		}
		
		if (strcmp(Word, "SinglePair")==0 || strcmp(Word, "SingleSource")==0){
			Dijkstra(V, ADJ, heap, s, t, n);
			source = s;
			destination = t;
			// singleSource = (t == -1) ? 1 : 0;
		}

		if (strcmp(Word, "PrintLength")==0){
			if (s != source){
				continue;
			}

			if (s != source || (destination != -1 and t != destination)) {
				fprintf(stdout, "There is no path from %d to %d.\n", s, t);
			} else if (V[t]->key == DBL_MAX){
				fprintf(stdout, "There is no path from %d to %d.\n", s, t);
			} else {
				fprintf(stdout, "The length of the shortest path from %d to %d is: %8.2f\n", s, t, V[t]->key);
			}
		}
		if (strcmp(Word, "PrintPath")==0){
			if (s != source){
				continue;
			}
			
			// reset stack pointer
			stack->top = -1;

			if (s != source || (destination != -1 and t != destination)){
				fprintf(stdout, "There is no path from %d to %d.\n", s, t);
			} else if (V[t]->key == DBL_MAX || (V[t]->pi == -1 and t != s)){
				fprintf(stdout, "There is no path from %d to %d.\n", s, t);
			} else {
				int current = t;
				while (current != s and current != -1){
					push(stack, current);
					current = V[current]->pi;
				}
				fprintf(stdout, "The shortest path from %d to %d is:\n", s, t);
				fprintf(stdout, "[%d:%8.2f]", s, V[s]->key);
				while(!isEmpty(stack)){
					int node = pop(stack);
					fprintf(stdout, "-->[%d: %7.2f]", node, V[node]->key);
				}
				fprintf(stdout, ".\n");
			}
		}
	}
	cleanup(heap, V, ADJ, stack, n);
}

// free memory function
void cleanup(pHEAP heap, pVERTEX *V, pNODE *ADJ, pSTACK stack, int n){
	if (V != NULL){
		for (int i = 1; i <= n; i++){
			if (V[i] != NULL){
				free(V[i]);
			}
		}
		free(V);
	}
	
	if (ADJ != NULL){
		for (int i = 1; i <= n; i++){
			pNODE current = ADJ[i];
			while (current != NULL){
				pNODE next = current->next;
				free(current);
				current = next;
			}
		}
		free(ADJ);
	}

	if(heap != NULL){
		if (heap->H != NULL){
			free(heap->H);
		}
		free(heap);
	}

	if (stack != NULL){
		if (stack->items != NULL){
			free(stack->items);
		}
		free(stack);
	}
}
