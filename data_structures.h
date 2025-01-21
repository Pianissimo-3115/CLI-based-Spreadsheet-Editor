#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct Node {
    int element;            ///////////////////////////////// THIS HAS TO BE CHANGED ACCORDING TO USE CASE (MOSTLY WILL BE USED ON DATA TYPE "CELL")
    struct Node* left;
    struct Node* right;
    int height;
} Node;

typedef struct AVL {
    Node* root;
} AVL;

Node* create_node(int element);

Node* insert(Node* root, int element);

Node* erase(Node* root, int element);   // REMOVE ELEMENT FROM THE SUBTREE ROOTED AT *root

void inorder(Node* root);               // INORDER TRAVERSAL OF THE SUBTREE ROOTED AT *root

void level(Node* root);                 //DEPTH OF THE GIVEN NODE

#endif

