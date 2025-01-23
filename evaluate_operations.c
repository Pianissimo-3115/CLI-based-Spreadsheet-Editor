#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "cell_operations.h"
#define max(A, B) ((A) > (B) ? (A) : (B))
#define min(A, B) ((A) < (B) ? (A) : (B))

void update_children(Cell** data, Cell* cell) {
    
}
int min_eval(Cell** data, Cell_func* func, int R, int C){         
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int mini = INT_MAX;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            mini = min(mini,(*(data + C*i + j - 1))->value);
        }        
    }
    return mini;
}

int max_eval(Cell** data, Cell_func* func, int R, int C){       
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int maxi = INT_MIN;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            maxi = max(maxi,(*(data + C*i + j - 1))->value);
        }        
    }
    return maxi;
}

int sum_eval(Cell** data, Cell_func* func, int R, int C){
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int sum = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            sum += (*(data + C*i + j - 1))->value;
        }        
    }
    return sum;
}

int avg_eval(Cell** data, Cell_func* func, int R, int C){
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int sum = 0;
    int count = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            sum += (*(data + C*i + j - 1))->value;
            count++;
        }        
    }
    return sum/count;
}

int stdev_eval(Cell** data, Cell_func* func, int R, int C){
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int sum = 0;
    int count = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            sum += (*(data + C*i + j - 1))->value;
            count++;
        }        
    }
    int mean = sum/count;
    int sum_sq = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            sum_sq += pow((*(data + C*i + j - 1))->value - mean, 2);
        }        
    }
    return sqrt(sum_sq/count);
}
void sleep(int seconds) {
    time_t start_time = time(NULL);
    while ((time(NULL) - start_time) < seconds);
}

void evaluate(Cell** data, Cell *cell, int R ,int C) {
    int initial_value = cell->value;
    Cell_func *func = cell->func;
    int val1 = 0, val2 = 0;
    if(func->Cell1 != NULL) val1 = func->Cell1->value;
    if(func->Cell2 != NULL) val1 = func->Cell2->value;
    cell->valid = 1;
    switch (func->op) {
        case FIX: {cell->value = func-> fix_val; break;}
        case ADD: {
            
            cell->value = val1 + val2; 
            func->Cell1->children->root = insert(func->Cell1->children->root, cell->value);
            func->Cell2->children->root = insert(func->Cell2->children->root, cell->value);
            break;
        }
        case SUB: {
            cell->value = val1 - val2; 
            func->Cell1->children->root = insert(func->Cell1->children->root, cell->value);
            func->Cell2->children->root = insert(func->Cell2->children->root, cell->value);
            break;
        }
        case MUL: {
            cell->value = val1*val2; 
            func->Cell1->children->root = insert(func->Cell1->children->root, cell->value);
            func->Cell2->children->root = insert(func->Cell2->children->root, cell->value);
            break;
            }
        case DIV: {
            if(val2 == 0) cell->valid = 0;          //////////////////////////////////////////////////////// TO BE DISCUSSED IF WE HAVE TO PUT IN DEPENDENCY SET IN THIS CASE
            else {
                cell->value = val1/val2;
                func->Cell1->children->root = insert(func->Cell1->children->root, cell->value);
                func->Cell2->children->root = insert(func->Cell2->children->root, cell->value);  
            }
            break;
        }
        case SLEEP: {                       ///////////////////////////////////////////////////////////////// HAVE TO MODIFY THIS: SLEEP CAN ALSO REQUIRE ADDRESS INSTEAD OF FIX VAL. ALSO INSERT IN AVL TREE IN THAT CASE
            sleep(func->fix_val);
            cell->value = val1;
            break;
        }
        ///////////////////////////////////////////// FOR ALL CASES BELOW, NEED A FUNCTION THAT TAKES INPUT AN ADDRESS (eg. A2) AND RETURNS THE POINTER TO THE CORRESPONDING CELL
        case MIN:{ cell->value = min_eval(data, func, R, C); break;}        
        case MAX:{ cell->value = max_eval(data, func, R, C); break;}
        case STDEV:{ cell->value = stdev_eval(data, func, R, C); break;}
        case SUM:{ cell->value = sum_eval(data, func, R, C); break;}
        case AVG:{ cell->value = avg_eval(data, func, R, C); break;}
    }
    if (cell->value != initial_value) {
        update_children(data, cell);            ///////////////////// TO BE IMPLEMENTED
    }
    return;
}

int main(){
    unsigned int R, C;
    scanf("%u %u", &R, &C);
    // Cell** data = calloc(R*C, sizeof(Cell*));
    // display_window(data, 23, 23, R, C);    
}