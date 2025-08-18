// Justin Dupuis ID: 1233344491
#ifndef _heap_h
#define _heap_h 1
#include <stdio.h>
#include "data_structures.h"

void buildHeap(pHEAP heap, pVERTEX *V);
void minHeapify(pHEAP heap, pVERTEX *V, int i);
void insertHeap(pHEAP heap, pVERTEX *V, pVERTEX v);
pVERTEX extractMin(pHEAP heap, pVERTEX *V);
pVERTEX minHeapMin(pHEAP heap);
void decreaseKey(pHEAP heap, pVERTEX *V, pVERTEX v, double newKey);




#endif
