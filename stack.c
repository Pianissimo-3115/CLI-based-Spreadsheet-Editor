#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#define size 503

Stack *createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = size;
    stack->top = -1;
    stack->array = (Cell**)malloc(size * sizeof(Cell*));
    return stack;
}

void push(Stack *stack, Cell* item) {
    stack->array[++stack->top] = item;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

Cell* pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return NULL;
}