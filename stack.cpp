// Justin Dupuis ID: 1233344491
#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "stack.h"

void push(pSTACK stack, int value){
	if (stack->top >= stack->size - 1){
		fprintf(stderr, "Error: stackoverflow\n");
		exit(1);
	} else {
		stack->top++;
		stack->items[stack->top] = value;
	}
		
}

int pop(pSTACK stack){
	if (stack->top < 0){
		fprintf(stderr, "Error: stack underflow\n");
		exit(1);
	}
	return stack->items[stack->top--];
}

int isEmpty(pSTACK stack){
	return stack->top == -1;
}
