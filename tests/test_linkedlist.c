#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../data_structures.h"
#include "../cell_operations.h"

void test_createNode() {
    Cell cell = {1, 1, 10, 1, NULL, NULL};
    ll_Node* node = createNode(&cell);
    assert(node != NULL);
    assert(node->data == &cell);
    assert(node->next == NULL);
    free(node);
    printf("test_createNode passed\n");
}

void test_insertAtEnd() {
    Cell cell1 = {1, 1, 10, 1, NULL, NULL};
    Cell cell2 = {1, 2, 20, 1, NULL, NULL};
    ll_Node* head = createNode(&cell1);
    
    insertAtEnd(head, &cell2);
    
    assert(head->data == &cell1);
    assert(head->next != NULL);
    assert(head->next->data == &cell2);
    assert(head->next->next == NULL);
    
    freeLinkedList(head);
    printf("test_insertAtEnd passed\n");
}

void test_insertAtHead() {
    Cell cell1 = {1, 1, 10, 1, NULL, NULL};
    Cell cell2 = {1, 2, 20, 1, NULL, NULL};
    ll_Node* head = createNode(&cell1);
    
    insertAtHead(&head, &cell2);
    
    assert(head->data == &cell2);
    assert(head->next != NULL);
    assert(head->next->data == &cell1);
    assert(head->next->next == NULL);
    
    freeLinkedList(head);
    printf("test_insertAtHead passed\n");
}

void test_insertAtPosition() {
    Cell cell1 = {1, 1, 10, 1, NULL, NULL};
    Cell cell2 = {1, 2, 20, 1, NULL, NULL};
    Cell cell3 = {1, 3, 30, 1, NULL, NULL};
    ll_Node* head = createNode(&cell1);
    insertAtEnd(head, &cell3);
    
    insertAtPosition(head, &cell2);
    
    assert(head->data == &cell1);
    assert(head->next != NULL);
    assert(head->next->data == &cell2);
    assert(head->next->next != NULL);
    assert(head->next->next->data == &cell3);
    assert(head->next->next->next == NULL);
    
    freeLinkedList(head);
    printf("test_insertAtPosition passed\n");
}

int main() {
    test_createNode();
    test_insertAtEnd();
    test_insertAtHead();
    test_insertAtPosition();
    
    printf("All tests passed successfully!\n");
    return 0;
}
