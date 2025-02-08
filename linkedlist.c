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
void insertAtEnd(LinkedList* list, Cell* data) {
    ll_Node* newNode = createNode(data);
    if (!newNode) return;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        ll_Node* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to insert a node at a given position
void insertAtPosition(ll_Node* position, Cell* data) {
    if (position == NULL) {
        return;
    }
    ll_Node* newNode = createNode(data);
    if (!newNode) return;

    newNode->next = position->next;
    position->next = newNode;

}


// Function to free the memory of the linked list
void freeLinkedList(LinkedList* list) {
    ll_Node* current = list->head;
    ll_Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    list->head = NULL;
}

// int main() {
//     LinkedList list;
//     list.head = NULL;

//     insertAtEnd(&list, 10);
//     insertAtEnd(&list, 20);
//     insertAtEnd(&list, 30);

//     ll_Node* position = list.head->next; // Insert after the first node
//     insertAtPosition(position, 25);

//     // Free the memory
//     freeLinkedList(&list);

//     return 0;
// }