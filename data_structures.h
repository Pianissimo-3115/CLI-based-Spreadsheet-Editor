#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
    #include<stdbool.h>
    typedef struct Cell Cell;
    typedef struct Node {
        Cell* element;            ///////////////////////////////// THIS HAS TO BE CHANGED ACCORDING TO USE CASE (MOSTLY WILL BE USED ON DATA TYPE "CELL")
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

    bool custom_comparator(Node* element1, Node* element2){
        if(element1->element->depth==element2->element->depth){
            if(element1->element->col_name==element2->element->col_name){
                return element1->element->row_num<element2->element->row_num;
            }
            return element1->element->col_name<element2->element->col_name;
        }
        return element1->element->depth<element2->element->depth;
    }

    void inorder(Node* root);               // INORDER TRAVERSAL OF THE SUBTREE ROOTED AT *root

    void level(Node* root);                 //DEPTH OF THE GIVEN NODE

    void resetTree(AVL* avl);                 //RESET THE WHOLE TREE

    void deleteTree(Node* root);            //DELETE THE WHOLE TREE

#endif

