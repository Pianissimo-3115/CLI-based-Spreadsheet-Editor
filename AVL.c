#include <stdio.h>
#include <stdlib.h>
#include "cell_operations.h"
#include "data_structures.h"
#include <stdbool.h>


bool custom_comparator(Cell* element1, Cell* element2) {
    if (element1->col_name == element2->col_name) {
        return element1->row_num < element2->row_num;
    }
    return element1->col_name < element2->col_name;
}
Node* create_node(Cell* element) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->element = element;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(Node* node) {
    return node ? node->height : 0;
}

int height_diff(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* right_rotate(Node* z) {
    Node* y = z->left;
    z->left = y->right;
    y->right = z;

    z->height = 1 + (height(z->left) > height(z->right) ? height(z->left) : height(z->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

Node* left_rotate(Node* z) {
    Node* y = z->right;
    z->right = y->left;
    y->left = z;

    z->height = 1 + (height(z->left) > height(z->right) ? height(z->left) : height(z->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

Node* insert(Node* root, Cell* element) {
    if (root == NULL) return create_node(element);

    if (custom_comparator(element, root->element))
        root->left = insert(root->left, element);
    else if (custom_comparator(root->element, element))
        root->right = insert(root->right, element);
    else
        return root;

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    int difference = height_diff(root);

    if (difference > 1 && custom_comparator(element, root->left->element)) return right_rotate(root);
    if (difference < -1 && custom_comparator(root->right->element, element)) return left_rotate(root);
    if (difference > 1 && custom_comparator(root->left->element, element)) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (difference < -1 && custom_comparator(element, root->right->element)) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

Node* min_value_node(Node* node) {
    Node* current = node;
    while (current->left != NULL) current = current->left;
    return current;
}

void deleteTree(Node* node) {
    if (node == NULL) return;
    
    deleteTree(node->left);
    deleteTree(node->right);
    
    free(node);
}

void resetTree(AVL* avl) {
    deleteTree(avl->root);
    avl->root = NULL;
}

Node* erase(Node* root, Cell* element) {
    if (root == NULL) return root;

    if (custom_comparator(element, root->element))
        root->left = erase(root->left, element);
    else if (custom_comparator(root->element, element))
        root->right = erase(root->right, element);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            if(temp) free(temp);
        } else {
            Node* temp = min_value_node(root->right);
            root->element = temp->element;
            root->right = erase(root->right, temp->element);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    int difference = height_diff(root);

    if (difference > 1 && height_diff(root->left) >= 0) return right_rotate(root);
    if (difference > 1 && height_diff(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (difference < -1 && height_diff(root->right) <= 0) return left_rotate(root);
    if (difference < -1 && height_diff(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void inorder(Node * root, ll_Node** head){
    if(root == NULL) {
        return;
    }
    inorder(root->left, head);
    insertAtHead(head, root->element);
    inorder(root->right, head);
}