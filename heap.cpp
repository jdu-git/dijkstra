// Justin Dupuis ID: 1233344491
#include <stdio.h>
#include <stdlib.h>
#include <cfloat>
#include "heap.h"
#include "data_structures.h"

void buildHeap(pHEAP heap, pVERTEX *V){
	for (int i = heap->size/2; i >= 1; i--){
		minHeapify(heap, V, i);
	}
}

void minHeapify(pHEAP heap, pVERTEX *V, int i){
	int l = 2*i;
	int r = 2*i + 1;
	int smallest;

	if (l <= heap->size and heap->H[l]->key < heap->H[i]->key){
		smallest = l;
	} else {
		smallest = i;
	}
	if (r <= heap->size and heap->H[r]->key < heap->H[smallest]->key){
		smallest = r;
	}
	if (smallest != i){
		// swap H[i] and H[smallest]
		pVERTEX temp = heap->H[i];
		heap->H[i] = heap->H[smallest];
		heap->H[smallest] = temp;

		// update position in heap
		heap->H[i]->position = i;
		heap->H[smallest]->position = smallest;
		// recursively move up the tree
		minHeapify(heap, V, smallest);
	}	
}

void decreaseKey(pHEAP heap, pVERTEX *V, pVERTEX v, double newKey){
	// set i to position first
	int i = v->position;
	int parent = i/2;
	
	// check for NULLS
	if (!heap || !v || i <= 0 || i > heap->size){
		fprintf(stderr, "Error: invalid input can not decrease key\n");
		return;
	}
	if (newKey > heap->H[i]->key){
		fprintf(stderr, "New key is bigger than current key\n");
		return;
	}
	heap->H[i]->key = newKey;
	
	// swap v and H[parent} if necessary
	while (i > 1 and v->key < heap->H[parent]->key){
		pVERTEX temp = heap->H[i];
		heap->H[i] = heap->H[parent];
		heap->H[parent] = temp;
		// update positions as well
		heap->H[i]->position = i;
		heap->H[parent]->position = parent;

		i = parent;
	}
}

void insertHeap(pHEAP heap, pVERTEX *V, pVERTEX u){
	if (heap->size == heap->capacity){
		fprintf(stderr, "Heap overflow\n");
		return;
	}
	heap->size++;
	
	double k = u->key;
	
	u->key = DBL_MAX;
	heap->H[heap->size] = u;
	u->position = heap->size;

	decreaseKey(heap, V, u, k);

}
pVERTEX minHeapMin(pHEAP heap){
	if (heap->size < 1){
		fprintf(stderr, "Error: heap underflow");
		return NULL;
	}
	return heap->H[1];
}
pVERTEX extractMin(pHEAP heap, pVERTEX *V){
	if (heap->size < 1){
		fprintf(stderr, "Error: heap underflow\n");
		return NULL;
	}
	// swap 1 and last
	pVERTEX min = heap->H[1];
	heap->H[1] = heap->H[heap->size];
	heap->H[1]->position = 1;
	heap->size--;
	
	minHeapify(heap, V, 1);

	min->position = 0;
	return min;
}
