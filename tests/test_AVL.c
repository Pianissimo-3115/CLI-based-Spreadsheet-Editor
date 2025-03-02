#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../cell_operations.h"
#include "../data_structures.h"

// Test helper function to verify AVL property
int is_balanced(Node* node) {
    if (node == NULL) return 1;
    
    int balance = height_diff(node);
    if (balance > 1 || balance < -1) return 0;
    
    return is_balanced(node->left) && is_balanced(node->right);
}

// Test helper to verify BST property
int is_bst(Node* node) {
    if (node == NULL) return 1;
    
    // Check left subtree
    if (node->left != NULL && !custom_comparator(node->left->element, node->element))
        return 0;
    
    // Check right subtree
    if (node->right != NULL && !custom_comparator(node->element, node->right->element))
        return 0;
    
    // Recursively check subtrees
    return is_bst(node->left) && is_bst(node->right);
}

// Test helper to count nodes
int count_nodes(Node* node) {
    if (node == NULL) return 0;
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

// Test helper to find a node
int find_node(Node* node, Cell* element) {
    if (node == NULL) return 0;
    
    if (!custom_comparator(node->element, element) && !custom_comparator(element, node->element))
        return 1;
    
    if (custom_comparator(element, node->element))
        return find_node(node->left, element);
    else
        return find_node(node->right, element);
}

// Test helper to verify height property
int verify_height(Node* node) {
    if (node == NULL) return 1;
    
    int left_height = height(node->left);
    int right_height = height(node->right);
    int expected_height = 1 + (left_height > right_height ? left_height : right_height);
    
    if (node->height != expected_height) return 0;
    
    return verify_height(node->left) && verify_height(node->right);
}

// Create test cells
Cell* create_test_cell(int col, int row, int value) {
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    cell->col_name = col;
    cell->row_num = row;
    cell->value = value;
    cell->valid = 1;
    cell->func = NULL;
    cell->children = NULL;
    return cell;
}

// Test cases
void test_insert() {
    printf("Testing insert...\n");
    AVL avl;
    avl.root = NULL;
    
    // Create test cells with different column/row combinations
    Cell* cell1 = create_test_cell(1, 1, 10);
    Cell* cell2 = create_test_cell(1, 2, 20);
    Cell* cell3 = create_test_cell(2, 1, 30);
    Cell* cell4 = create_test_cell(2, 2, 40);
    Cell* cell5 = create_test_cell(3, 1, 50);
    
    // Insert cells into the AVL tree
    avl.root = insert(avl.root, cell1);
    assert(count_nodes(avl.root) == 1);
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    
    avl.root = insert(avl.root, cell2);
    assert(count_nodes(avl.root) == 2);
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    
    avl.root = insert(avl.root, cell3);
    assert(count_nodes(avl.root) == 3);
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    
    avl.root = insert(avl.root, cell4);
    assert(count_nodes(avl.root) == 4);
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    
    avl.root = insert(avl.root, cell5);
    assert(count_nodes(avl.root) == 5);
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    
    // Verify heights are correctly maintained
    assert(verify_height(avl.root));
    
    // Test duplicate insertion (should not change the tree)
    avl.root = insert(avl.root, cell1);
    assert(count_nodes(avl.root) == 5);
    
    // Clean up
    free(cell1);
    free(cell2);
    free(cell3);
    free(cell4);
    free(cell5);
    deleteTree(avl.root);
    printf("Insert test passed!\n");
}

void test_erase() {
    printf("Testing erase...\n");
    AVL avl;
    avl.root = NULL;
    
    // Create test cells
    Cell* cell1 = create_test_cell(1, 1, 10);
    Cell* cell2 = create_test_cell(1, 2, 20);
    Cell* cell3 = create_test_cell(2, 1, 30);
    Cell* cell4 = create_test_cell(2, 2, 40);
    Cell* cell5 = create_test_cell(3, 1, 50);
    
    // Insert cells
    avl.root = insert(avl.root, cell1);
    avl.root = insert(avl.root, cell2);
    avl.root = insert(avl.root, cell3);
    avl.root = insert(avl.root, cell4);
    avl.root = insert(avl.root, cell5);
    
    assert(count_nodes(avl.root) == 5);
    
    // Test erasing a leaf node
    avl.root = erase(avl.root, cell5);
    assert(count_nodes(avl.root) == 4);
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    assert(!find_node(avl.root, cell5));
    
    // Test erasing a node with one child
    avl.root = erase(avl.root, cell2);
    assert(count_nodes(avl.root) == 3);
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    assert(!find_node(avl.root, cell2));
    
    // Test erasing a node with two children
    avl.root = erase(avl.root, cell3);
    assert(count_nodes(avl.root) == 2);
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    assert(!find_node(avl.root, cell3));
    
    // Verify heights after deletion
    assert(verify_height(avl.root));
    
    // Delete the rest of the nodes
    avl.root = erase(avl.root, cell1);
    avl.root = erase(avl.root, cell4);
    assert(avl.root == NULL);
    
    // Clean up
    free(cell1);
    free(cell2);
    free(cell3);
    free(cell4);
    free(cell5);
    printf("Erase test passed!\n");
}

void test_rotations() {
    printf("Testing rotations...\n");
    AVL avl;
    avl.root = NULL;
    
    // Create cells that will force rotations
    // Left-left case
    Cell* cell1 = create_test_cell(3, 1, 30);
    Cell* cell2 = create_test_cell(2, 1, 20);
    Cell* cell3 = create_test_cell(1, 1, 10);
    
    // Insert to create left-left imbalance
    avl.root = insert(avl.root, cell1);
    avl.root = insert(avl.root, cell2);
    avl.root = insert(avl.root, cell3);
    
    // Tree should be balanced after rotations
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    assert(verify_height(avl.root));
    
    // Clean up
    deleteTree(avl.root);
    avl.root = NULL;
    
    // Right-right case
    Cell* cell4 = create_test_cell(1, 1, 10);
    Cell* cell5 = create_test_cell(2, 1, 20);
    Cell* cell6 = create_test_cell(3, 1, 30);
    
    avl.root = insert(avl.root, cell4);
    avl.root = insert(avl.root, cell5);
    avl.root = insert(avl.root, cell6);
    
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    assert(verify_height(avl.root));
    
    // Clean up
    deleteTree(avl.root);
    avl.root = NULL;
    
    // Left-right case
    Cell* cell7 = create_test_cell(3, 1, 30);
    Cell* cell8 = create_test_cell(1, 1, 10);
    Cell* cell9 = create_test_cell(2, 1, 20);
    
    avl.root = insert(avl.root, cell7);
    avl.root = insert(avl.root, cell8);
    avl.root = insert(avl.root, cell9);
    
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    assert(verify_height(avl.root));
    
    // Clean up
    deleteTree(avl.root);
    avl.root = NULL;
    
    // Right-left case
    Cell* cell10 = create_test_cell(1, 1, 10);
    Cell* cell11 = create_test_cell(3, 1, 30);
    Cell* cell12 = create_test_cell(2, 1, 20);
    
    avl.root = insert(avl.root, cell10);
    avl.root = insert(avl.root, cell11);
    avl.root = insert(avl.root, cell12);
    
    assert(is_balanced(avl.root));
    assert(is_bst(avl.root));
    assert(verify_height(avl.root));
    
    // Clean up
    free(cell1);
    free(cell2);
    free(cell3);
    free(cell4);
    free(cell5);
    free(cell6);
    free(cell7);
    free(cell8);
    free(cell9);
    free(cell10);
    free(cell11);
    free(cell12);
    deleteTree(avl.root);
    printf("Rotation test passed!\n");
}

void test_resetTree() {
    printf("Testing resetTree...\n");
    AVL avl;
    avl.root = NULL;
    
    // Create and insert test cells
    Cell* cell1 = create_test_cell(1, 1, 10);
    Cell* cell2 = create_test_cell(2, 1, 20);
    Cell* cell3 = create_test_cell(3, 1, 30);
    
    avl.root = insert(avl.root, cell1);
    avl.root = insert(avl.root, cell2);
    avl.root = insert(avl.root, cell3);
    
    assert(count_nodes(avl.root) == 3);
    
    // Reset the tree
    resetTree(&avl);
    
    // Verify tree is empty
    assert(avl.root == NULL);
    
    // Clean up
    free(cell1);
    free(cell2);
    free(cell3);
    printf("ResetTree test passed!\n");
}

void test_inorder() {
    printf("Testing inorder traversal...\n");
    AVL avl;
    avl.root = NULL;
    
    // Create test cells with different column/row combinations to ensure proper sorting
    Cell* cell1 = create_test_cell(2, 2, 40);
    Cell* cell2 = create_test_cell(1, 2, 20);
    Cell* cell3 = create_test_cell(3, 1, 50);
    Cell* cell4 = create_test_cell(1, 1, 10);
    Cell* cell5 = create_test_cell(2, 1, 30);
    
    // Insert cells in random order
    avl.root = insert(avl.root, cell1);
    avl.root = insert(avl.root, cell2);
    avl.root = insert(avl.root, cell3);
    avl.root = insert(avl.root, cell4);
    avl.root = insert(avl.root, cell5);
    
    // Perform inorder traversal
    ll_Node* head = NULL;
    inorder(avl.root, &head);
    
    // Verify that the linked list is in correct order based on the custom comparator
    assert(head != NULL);
    
    // Expected order: cell4 (1,1), cell2 (1,2), cell5 (2,1), cell1 (2,2), cell3 (3,1)
    ll_Node* current = head;
    assert(current->data->col_name == 3 && current->data->row_num == 1);
    current = current->next;
    assert(current->data->col_name == 2 && current->data->row_num == 2);
    current = current->next;
    assert(current->data->col_name == 2 && current->data->row_num == 1);
    current = current->next;
    assert(current->data->col_name == 1 && current->data->row_num == 2);
    current = current->next;
    assert(current->data->col_name == 1 && current->data->row_num == 1);
    assert(current->next == NULL);
    
    // Clean up
    freeLinkedList(head);
    free(cell1);
    free(cell2);
    free(cell3);
    free(cell4);
    free(cell5);
    deleteTree(avl.root);
    printf("Inorder traversal test passed!\n");
}

void test_custom_comparator() {
    printf("Testing custom_comparator...\n");
    
    // Create test cells
    Cell* cell1 = create_test_cell(1, 1, 10);
    Cell* cell2 = create_test_cell(1, 2, 20);
    Cell* cell3 = create_test_cell(2, 1, 30);
    
    // Test column comparison
    assert(custom_comparator(cell1, cell3) == true);
    assert(custom_comparator(cell3, cell1) == false);
    
    // Test row comparison when columns are the same
    assert(custom_comparator(cell1, cell2) == true);
    assert(custom_comparator(cell2, cell1) == false);
    
    // Test equality case
    Cell* cell4 = create_test_cell(1, 1, 100); // Different value, same col/row
    assert(custom_comparator(cell1, cell4) == false);
    assert(custom_comparator(cell4, cell1) == false);
    
    // Clean up
    free(cell1);
    free(cell2);
    free(cell3);
    free(cell4);
    printf("Custom comparator test passed!\n");
}

int main() {
    printf("Running AVL Tree unit tests...\n");
    
    test_custom_comparator();
    test_insert();
    test_erase();
    test_rotations();
    test_resetTree();
    test_inorder();
    
    printf("All tests passed!\n");
    return 0;
}