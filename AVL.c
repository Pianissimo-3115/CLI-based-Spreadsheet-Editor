#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include <stdbool.h>
bool custom_comparator(int element1, int element2){
    return element1<element2;                           /////////////////////////////////////////////////// THIS HAS TO BE MODIFIED ACCORDING TO USE CASE (MOSTLY GOING TO BE USED AS "DEPTH" MEMBER OF THE STRUCT "CELL")
}

Node* create_node(int element) {
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

Node* insert(Node* root, int element) {
    if (root == NULL) return create_node(element);

    if (element < root->element)
        root->left = insert(root->left, element);
    else if (element > root->element)
        root->right = insert(root->right, element);
    else
        return root;

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    int difference = height_diff(root);

    if (difference > 1 && element < root->left->element) return right_rotate(root);
    if (difference < -1 && element > root->right->element) return left_rotate(root);
    if (difference > 1 && element > root->left->element) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (difference < -1 && element < root->right->element) {
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

Node* erase(Node* root, int element) {
    if (root == NULL) return root;

    if (element < root->element)
        root->left = erase(root->left, element);
    else if (element > root->element)
        root->right = erase(root->right, element);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
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

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->element);
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->element);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->element);
}

void level(Node* root) {
    if (root == NULL) return;

    Node* queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = root;
    queue[rear++] = NULL;

    while (front < rear) {
        Node* temp = queue[front++];
        if (temp == NULL) {
            if (front < rear) queue[rear++] = NULL;
            printf("\n");
        } else {
            printf("%d ", temp->element);
            if (temp->left) queue[rear++] = temp->left;
            if (temp->right) queue[rear++] = temp->right;
        }
    }
}

int main() {
    AVL avl;
    avl.root = NULL;

    avl.root = insert(avl.root, 10);
    printf("Level order traversal: \n");
    level(avl.root);
    avl.root = insert(avl.root, 20);
    printf("Level order traversal: \n");
    level(avl.root);
    avl.root = insert(avl.root, 30);
    printf("Level order traversal: \n");
    level(avl.root);
    avl.root = insert(avl.root, 40);
    printf("Level order traversal: \n");
    level(avl.root);
    avl.root = insert(avl.root, 50);
    printf("Level order traversal: \n");
    level(avl.root);
    avl.root = insert(avl.root, 25);
    printf("Level order traversal: \n");
    level(avl.root);

    printf("Inorder traversal: ");
    inorder(avl.root);
    printf("\n");

    printf("Level order traversal: \n");
    level(avl.root);

    avl.root = erase(avl.root, 10);

    printf("\nInorder traversal after deletion: ");
    inorder(avl.root);
    printf("\n");

    return 0;
}