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
bool custom_comparator(Node* element1, Node* element2);
void inorder(Node* root);
void level(Node* root);
void resetTree(AVL* avl);
void deleteTree(Node* root);

#endif