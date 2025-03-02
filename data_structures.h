#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdbool.h>
#include "cell_operations.h"

// AVL tree structures
typedef struct Node Node;
typedef struct AVL AVL;
typedef struct ll_Node ll_Node;
typedef struct Stack Stack;
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
void inorder(Node* root,ll_Node** head);
void resetTree(AVL* avl);
void deleteTree(Node* root);
int height(Node* node);
int height_diff(Node* node);







// Linked list operations
// Define the node structure
typedef struct ll_Node {
    Cell* data;
    struct ll_Node* next;
} ll_Node;

// Linked list functions
ll_Node* createNode(Cell* data);
void insertAtEnd(ll_Node* head, Cell* data);
void insertAtHead(ll_Node** head, Cell* data);
void insertAtPosition(ll_Node* position, Cell* data);
void freeLinkedList(ll_Node* head);
void printLinkedList(ll_Node* head);

typedef struct {
    ll_Node **table;
    int size;
} HashTable;
#define TABLE_SIZE 293
int hash(Cell* cell, int size);
HashTable* create_table(int size);
void hash_insert(HashTable *ht, Cell *cell);
void hash_remove(HashTable *ht, Cell *cell);
int hash_search(HashTable *ht, Cell* cell);
void free_table(HashTable *ht);

// Stack operations
typedef struct Stack {
    ll_Node* top;
} Stack;

Stack* createStack();
void push(Stack* stack, Cell* item);
Cell* pop(Stack* stack);
int isEmpty(Stack* stack);
void freeStack(Stack* stack);

#endif