#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../data_structures.h"

void test_createStack() {
    Stack* stack = createStack();
    assert(stack != NULL);
    assert(stack->top == NULL);
    freeStack(stack);
    printf("test_createStack passed\n");
}

void test_pushAndPop() {
    Stack* stack = createStack();
    Cell cell1 = {1, 1, 10, 1, NULL, NULL};
    Cell cell2 = {2, 2, 20, 1, NULL, NULL};
    
    push(stack, &cell1);
    push(stack, &cell2);
    
    Cell* popped = pop(stack);
    assert(popped == &cell2);
    
    popped = pop(stack);
    assert(popped == &cell1);
    
    assert(isEmpty(stack));
    
    freeStack(stack);
    printf("test_pushAndPop passed\n");
}

void test_isEmpty() {
    Stack* stack = createStack();
    assert(isEmpty(stack));
    
    Cell cell = {1, 1, 10, 1, NULL, NULL};
    push(stack, &cell);
    assert(!isEmpty(stack));
    
    pop(stack);
    assert(isEmpty(stack));
    
    freeStack(stack);
    printf("test_isEmpty passed\n");
}

void test_popEmptyStack() {
    Stack* stack = createStack();
    Cell* popped = pop(stack);
    assert(popped == NULL);
    freeStack(stack);
    printf("test_popEmptyStack passed\n");
}

int main() {
    test_createStack();
    test_pushAndPop();
    test_isEmpty();
    test_popEmptyStack();
    
    printf("All stack tests passed successfully!\n");
    return 0;
}
