// Justin Dupuis ID: 1233344491
#ifndef _STACK_H
#define _STACK_H 1
#include <stdio.h>
#include <stdlib.h>

typedef struct TAG_STACK {
	int top;
	int size;
	int *items;
} STACK;
typedef STACK *pSTACK;

pSTACK createStack(int capacity);
void push(pSTACK s, int value);
int pop(pSTACK s);
int isEmpty(pSTACK s);
void freeStack(pSTACK s);

#endif
