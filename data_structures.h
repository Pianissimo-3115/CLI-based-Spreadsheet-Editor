#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdbool.h>
#include "cell_operations.h"

// AVL tree structures
typedef struct Node Node;
typedef struct AVL AVL;

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
int inorder(Node* root, Cell** arr);
void level(Node* root);
void resetTree(AVL* avl);
void deleteTree(Node* root);

#endif