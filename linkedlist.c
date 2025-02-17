#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

// Function to create a new node
ll_Node* createNode(Cell* data) {
    ll_Node* newNode = (ll_Node*)malloc(sizeof(ll_Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertAtEnd(ll_Node* head, Cell* data) {
    ll_Node* newNode = createNode(data);
    if (!newNode) return;
    if (head == NULL) {
        head = newNode;  
    } 
    else {
        ll_Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void insertAtHead(ll_Node* head, Cell* data) {
    ll_Node* newNode = createNode(data);
    if (!newNode) return;
    newNode->next = head;
    head = newNode;
}

// Function to insert a node after a given position
void insertAtPosition(ll_Node* position, Cell* data) {
    if (position == NULL) {
        return;
    }
    ll_Node* newNode = createNode(data);
    if (!newNode) return;

    newNode->next = position->next;
    position->next = newNode;
}

// Function to free the linked list
void freeLinkedList(ll_Node* head) {
    ll_Node* current = head;
    ll_Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    head = NULL; // Set head to NULL
}

// Function to print the linked list
void printLinkedList(ll_Node* head) {
    ll_Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data->value);
        temp = temp->next;
    }
    printf("NULL\n");
}
// #ifndef MAIN
// int main() {
//     ll_Node* head = NULL;

//     insertAtEnd(head, 10);
//     insertAtEnd(head, 20);
//     insertAtEnd(head, 30);

//     printf("Before inserting at position:\n");
//     printLinkedList(head);

//     // Insert after the first node
//     if (head != NULL) {
//         insertAtPosition(head, 25);
//     }

//     printf("After inserting at position:\n");
//     printLinkedList(head);

//     // Free the memory
//     freeLinkedList(head);

//     return 0;
// }
// #endif
