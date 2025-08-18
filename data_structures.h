// Justin Dupuis ID: 1233344491
#ifndef _DATA_STRUCTURES_H
#define _DATA_STRUCTURES_H 1
#include <stdio.h>
#include <stdlib.h>

// white = 0 gray = 1 black = 2
typedef enum TAG_COLOR {
	WHITE,
       	GRAY, 
	BLACK 
} COLOR;

typedef struct TAG_VERTEX {
	int index;
	COLOR color;
	double key; // length of current best path
	int pi;
	int position;
} VERTEX;
typedef VERTEX *pVERTEX;
typedef VERTEX ELEMENT;

typedef ELEMENT *pELEMENT;

typedef struct TAG_HEAP{
	int capacity;
	int size;
	pELEMENT *H;
} HEAP; 
typedef HEAP *pHEAP;

typedef struct TAG_NODE {
	int index;
	int u;
	int v;
	double w;
	struct TAG_NODE *next;
}NODE;
typedef NODE *pNODE;

#endif
