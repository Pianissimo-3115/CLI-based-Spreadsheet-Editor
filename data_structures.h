#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdbool.h>
#include "cell_operations.h"

// AVL tree structures
typedef struct Node Node;
typedef struct AVL AVL;
typedef struct ll_Node ll_Node;
typedef struct LinkedList LinkedList;
struct Node {
    Cell* element;            
    struct Node* left;
    struct Node* right;
    int height;
};

struct AVL {
    Node* root;
};



// AVL tree operations
Node* create_node(Cell* element);
Node* insert(Node* root, Cell* element);
Node* erase(Node* root, Cell* element);
bool custom_comparator(Cell* element1, Cell* element2);
ll_Node* inorder(Node* root, LinkedList* merged, ll_Node* head);
void level(Node* root);
void resetTree(AVL* avl);
void deleteTree(Node* root);






// Linked list operations
// Define the node structure
struct ll_Node {
    Cell* data;
    struct ll_Node* next;
};

// Define the linked list structure
// struct LinkedList {
//     ll_Node* head;
// };

ll_Node* createNode(Cell* data);
void insertAtEnd(LinkedList* list, Cell* data);
void insertAtPosition(ll_Node* position, Cell* data);
void freeLinkedList(LinkedList* list);
#endif