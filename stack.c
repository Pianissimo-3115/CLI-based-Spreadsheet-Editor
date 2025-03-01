#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"


// Function to create a new stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// Function to push an element onto the stack
void push(Stack* stack, Cell* item) {
    ll_Node* newNode = (ll_Node*)malloc(sizeof(ll_Node));
    if (!newNode) return;
    newNode->data = item;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to pop an element from the stack
Cell* pop(Stack* stack) {
    if (isEmpty(stack)) return NULL;
    ll_Node* temp = stack->top;
    Cell* poppedData = temp->data;
    stack->top = stack->top->next;
    if(temp) free(temp);
    return poppedData;
}

// Function to free the stack
void freeStack(Stack* stack) {
    ll_Node* current = stack->top;
    ll_Node* nextNode;

    // Traverse and free each node
    while (current) {
        nextNode = current->next;
        free(current);        // Free the node itself
        current = nextNode;
    }

    // free(stack);  // Free the stack structure
}
void testStack() {
    printf("Running Stack Test...\n");

    // Step 1: Create stack
    Stack* stack = createStack();
    if (!stack) {
        printf("Stack creation failed!\n");
        return;
    }
    printf("Stack created successfully.\n");

    // Step 2: Push elements onto the stack
    Cell* cell1 = (Cell*)malloc(sizeof(Cell));
    Cell* cell2 = (Cell*)malloc(sizeof(Cell));
    Cell* cell3 = (Cell*)malloc(sizeof(Cell));

    cell1->value = 10;  // Assuming Cell has an integer 'value' field
    cell2->value = 20;
    cell3->value = 30;

    push(stack, cell1);
    push(stack, cell2);
    push(stack, cell3);
    printf("Pushed values: 10, 20, 30 onto the stack.\n");

    // Step 3: Pop elements and check LIFO order
    Cell* popped = pop(stack);
    if (popped->value == 30)
        printf("Pop successful: 30\n");
    else
        printf("Pop failed! Expected 30, got %d\n", popped->value);
    free(popped);  // Free memory after popping

    popped = pop(stack);
    if (popped->value == 20)
        printf("Pop successful: 20\n");
    else
        printf("Pop failed! Expected 20, got %d\n", popped->value);
    free(popped);  // Free memory after popping

    popped = pop(stack);
    if (popped->value == 10)
        printf("Pop successful: 10\n");
    else
        printf("Pop failed! Expected 10, got %d\n", popped->value);
    free(popped);  // Free memory after popping

    // Step 4: Try popping from an empty stack
    popped = pop(stack);
    if (popped == NULL)
        printf("Pop from empty stack returned NULL (Correct behavior).\n");
    else
        printf("Pop from empty stack failed! Expected NULL.\n");

    // Step 5: Cleanup - Free the stack
    freeStack(stack);

    printf("Stack test completed successfully.\n");
}
// #ifndef MAIN
// // Main function to run the test case
// int main() {
//     testStack();
//     return 0;
// }
// #endif