// Justin Dupuis ID: 1233344491
#include <stdio.h>
#include <stdlib.h>
#include <cfloat>
#include "data_structures.h"
#include "heap.h"
#include "stack.h"
#include "graph.h"

void Dijkstra(pVERTEX *V, pNODE *ADJ, pHEAP heap, int s, int t, int n){
	for (int v = 1; v <= n; v++){
		V[v]->index = v;
		V[v]->key = DBL_MAX;
		V[v]->pi = -1;
		V[v]->color = WHITE;
		V[v]->position = 0;
	}
	// s is discovered, insert into heap
	V[s]->key = 0;
	V[s]->color = GRAY;
	heap->size = 0;
	insertHeap(heap, V, V[s]);
	
	while (heap->size > 0) {
		pVERTEX u = extractMin(heap, V);
		if (t != -1 and u->index == t){
			return;
		}

		pNODE neighbor = ADJ[u->index];
		while (neighbor != NULL){
			int vIndex = neighbor->v;
			pVERTEX v = V[vIndex];
			double weight = neighbor->w;

			if (v->color == WHITE){
				v->color = GRAY;
				v->key = u->key + weight;
				v->pi = u->index;
				insertHeap(heap, V, v);
			} else if (v->color == GRAY and u->key + weight < v->key){
				v->pi = u->index;
				decreaseKey(heap, V, v, u->key + weight);
			}
			
			neighbor = neighbor->next;
		}
		u->color = BLACK;
	}
				
}
