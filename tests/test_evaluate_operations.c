#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../data_structures.h"
#include "../cell_operations.h"

// Function prototypes
int min_eval(Cell** data, Cell_func* func, int C);
int max_eval(Cell** data, Cell_func* func, int C);
int sum_eval(Cell** data, Cell_func* func, int C);
int avg_eval(Cell** data, Cell_func* func, int C);
int stdev_eval(Cell** data, Cell_func* func, int C);
void calculate(Cell** data, Cell* cell, int C);
int evaluate(Cell** data, Cell *cell, Cell_func* old_func, int R, int C);

void free_test_cell(Cell* cell) {
    free(cell->func);
    free(cell->children);
    free(cell);
}
// Helper function to create a test cell
Cell* create_test_cell(int col, int row, int value) {
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    cell->func=(Cell_func*)malloc(sizeof(Cell_func));
    cell->children=(AVL*)malloc(sizeof(AVL));
    cell->children->root=NULL;
    cell->func->Cell1=NULL;
    cell->func->Cell2=NULL;
    cell->func->flag1=0;
    cell->func->flag2=0;
    cell->col_name = col;
    cell->row_num = row;
    cell->value = value;
    cell->valid = 1;
    return cell;
}
// Test for min_eval function
void test_min_eval() {
    Cell** data = (Cell**)malloc(4 * sizeof(Cell*));
    for (int i = 0; i < 4; i++) {
        data[i] = create_test_cell(i+1, 1, (i+1)*10);
    }
    
    Cell_func func;
    func.Cell1 = data[0];
    func.Cell2 = data[3];
    
    int result = min_eval(data, &func, 4);
    assert(result == 10);
    
    // Free allocated memory
    for (int i = 0; i < 4; i++) {
        free_test_cell(data[i]);
    }
    free(data);
    
    printf("min_eval test passed\n");
}

// Test for max_eval function
void test_max_eval() {
    Cell** data = (Cell**)malloc(4 * sizeof(Cell*));
    for (int i = 0; i < 4; i++) {
        data[i] = create_test_cell(i+1, 1, (i+1)*10);
    }
    
    Cell_func func;
    func.Cell1 = data[0];
    func.Cell2 = data[3];
    
    int result = max_eval(data, &func, 4);
    assert(result == 40);
    
    // Free allocated memory
    for (int i = 0; i < 4; i++) {
        free_test_cell(data[i]);
    }
    free(data);
    
    printf("max_eval test passed\n");
}

// Test for sum_eval function
void test_sum_eval() {
    Cell** data = (Cell**)malloc(4 * sizeof(Cell*));
    for (int i = 0; i < 4; i++) {
        data[i] = create_test_cell(i+1, 1, (i+1)*10);
    }
    
    Cell_func func;
    func.Cell1 = data[0];
    func.Cell2 = data[3];
    
    int result = sum_eval(data, &func, 4);
    assert(result == 100);
    
    // Free allocated memory
    for (int i = 0; i < 4; i++) {
        free_test_cell(data[i]);
    }
    free(data);
    
    printf("sum_eval test passed\n");
}

// Test for avg_eval function
void test_avg_eval() {
    Cell** data = (Cell**)malloc(4 * sizeof(Cell*));
    for (int i = 0; i < 4; i++) {
        data[i] = create_test_cell(i+1, 1, (i+1)*10);
    }
    
    Cell_func func;
    func.Cell1 = data[0];
    func.Cell2 = data[3];
    
    int result = avg_eval(data, &func, 4);
    assert(result == 25);
    
    // Free allocated memory
    for (int i = 0; i < 4; i++) {
        free_test_cell(data[i]);
    }
    free(data);
    
    printf("avg_eval test passed\n");
}

// Test for stdev_eval function
void test_stdev_eval() {
    Cell** data = (Cell**)malloc(4 * sizeof(Cell*));
    for (int i = 0; i < 4; i++) {
        data[i] = create_test_cell(i+1, 1, (i+1)*10);
    }
    
    Cell_func func;
    func.Cell1 = data[0];
    func.Cell2 = data[3];
    
    int result = stdev_eval(data, &func, 4);
    assert(result == 11); // Result that matches the function template provided on piazza
    
    // Free allocated memory
    for (int i = 0; i < 4; i++) {
        free_test_cell(data[i]);
    }
    free(data);
    
    printf("stdev_eval test passed\n");
}

// Test for calculate function
void test_calculate() {
    Cell** data = (Cell**)malloc(2 * sizeof(Cell*));
    data[0] = create_test_cell(1, 1, 10);
    data[1] = create_test_cell(2, 1, 20);
    
    Cell* cell = create_test_cell(3, 1, 0);
    cell->func = (Cell_func*)malloc(sizeof(Cell_func));
    cell->func->op = ADD;
    cell->func->flag1 = 1;
    cell->func->flag2 = 1;
    cell->func->Cell1 = data[0];
    cell->func->Cell2 = data[1];
    
    calculate(data, cell, 2);
    assert(cell->value == 30);
    
    // Free allocated memory
    free_test_cell(data[0]);
    free_test_cell(data[1]);
    free_test_cell(cell);
    free(data);
    
    printf("calculate test passed\n");
}

// Test for evaluate function
void test_evaluate() {
    Cell** data = (Cell**)malloc(4 * sizeof(Cell*));
    data[0] = create_test_cell(1, 1, 10);
    data[1] = create_test_cell(2, 1, 20);
    data[2] = create_test_cell(3, 1, 0);
    data[3] = create_test_cell(4, 1, 0);

    // Test ADD operation
    Cell* cell1 = data[2];
    cell1->func = (Cell_func*)malloc(sizeof(Cell_func));
    cell1->func->op = ADD;
    cell1->func->flag1 = 1;
    cell1->func->flag2 = 1;
    cell1->func->Cell1 = data[0];
    cell1->func->Cell2 = data[1];

    int result = evaluate(data, cell1, NULL, 1, 4);
    assert(result == 1);
    assert(cell1->value == 30);
    printf("1st op passed\n");
    // Test complex operation: STDEV
    Cell* cell2 = data[3];
    cell2->func = (Cell_func*)malloc(sizeof(Cell_func));
    cell2->func->op = STDEV;
    cell2->func->flag1 = 1;
    cell2->func->flag2 = 1;
    cell2->func->Cell1 = data[0];
    cell2->func->Cell2 = data[1];

    result = evaluate(data, cell2, NULL, 1, 4);
    assert(result == 1);
    assert(cell2->value == 5); // Expected standard deviation of 10 and 20
    printf("2nd op passed\n");
    // Test cyclic dependency
    Cell_func* old_func = cell1->func;
    cell1->func = (Cell_func*)malloc(sizeof(Cell_func));
    cell1->func->op = ADD;
    cell1->func->flag1 = 1;
    cell1->func->flag2 = 1;
    cell1->func->Cell1 = data[2];
    cell1->func->Cell2 = data[1];

    result = evaluate(data, data[0], old_func, 1, 4);
    assert(result == 0); // Should detect cycle and return 0
    printf("3rd op passed\n");
    // Test SLEEP operation
    cell1->func->op = SLEEP;
    cell1->func->flag1 = 0;
    cell1->func->value1 = 1; // Sleep for 1 second

    time_t start = time(NULL);
    result = evaluate(data, cell1, NULL, 1, 4);
    time_t end = time(NULL);
    assert(result == 1);
    assert((end - start) >= 1); // Ensure at least 1 second has passed
    printf("4th op passed\n");
    // Free allocated memory
    for (int i = 0; i < 4; i++) {
        free(data[i]->func);
        free_test_cell(data[i]);
    }
    free(data);
    free(old_func);

    printf("evaluate test passed\n");
}

int main() {
    test_min_eval();
    test_max_eval();
    test_sum_eval();
    test_avg_eval();
    test_stdev_eval();
    test_calculate();
    test_evaluate();
    
    printf("All tests passed successfully!\n");
    return 0;
}
