#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "cell_operations.h"
#define max(A, B) ((A) > (B) ? (A) : (B))
#define min(A, B) ((A) < (B) ? (A) : (B))

int min_eval(Cell** data,Cell* cell, Cell_func* func, int R, int C){         
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int mini = INT_MAX;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            mini = min(mini,(*(data + C*i + j - 1))->value);
            (*(data + C*i + j -1))->children->root=insert((*(data + C*i + j -1))->children->root,cell);
        }        
    }
    return mini;
}

int max_eval(Cell** data, Cell* cell, Cell_func* func, int R, int C){       
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int maxi = INT_MIN;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            maxi = max(maxi,(*(data + C*i + j - 1))->value);
            (*(data + C*i + j -1))->children->root=insert((*(data + C*i + j -1))->children->root,cell);
        }        
    }
    return maxi;
}

int sum_eval(Cell** data, Cell* cell, Cell_func* func, int R, int C){
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int sum = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            sum += (*(data + C*i + j - 1))->value;
            (*(data + C*i + j -1))->children->root=insert((*(data + C*i + j -1))->children->root,cell);
        }        
    }
    return sum;
}

int avg_eval(Cell** data, Cell* cell, Cell_func* func, int R, int C){
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int sum = 0;
    int count = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            sum += (*(data + C*i + j - 1))->value;
            (*(data + C*i + j -1))->children->root=insert((*(data + C*i + j -1))->children->root,cell);
            count++;
        }        
    }
    return sum/count;
}

int stdev_eval(Cell** data, Cell* cell, Cell_func* func, int R, int C){
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int sum = 0;
    int count = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            count++;
            sum += (*(data + C*i + j - 1))->value;
            (*(data + C*i + j -1))->children->root=insert((*(data + C*i + j -1))->children->root,cell);
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

void update_children(Cell** data, Cell* cell) {
    
}

void remove_old_dependencies(Cell** data, Cell_func* old_func, Cell* cell, int R, int C){
    if(old_func->op>5){             // is a range function
        Cell* start=old_func->Cell1;
        Cell* end=old_func->Cell2;
        for (int col = start->col_name; col < end->col_name; col++) {
            for (int row = start->row_num; row < end->row_num ; row++) {
                ((*(data + C*col + row - 1))->children)->root=
                    erase(((*(data + C*col + row - 1))->children)->root, cell);       // erase from non existent (old) dependency
            }
        } 
    }
    // not a range function => either constant value or binary
    // ∃ only two constant functions, SLEEP and FIX | if FIX, simply ignore. For sleep check if sleep for const time or cell address
    else{                   
        if(old_func->op==SLEEP&&old_func->flag1)
            old_func->Cell1->children->root=erase(old_func->Cell1->children->root,cell);

        else if(old_func->op>1){    // is a binary function
            if(old_func->flag1) 
                old_func->Cell1->children->root=erase(old_func->Cell1->children->root,cell);
            if(old_func->flag2)
                old_func->Cell2->children->root=erase(old_func->Cell2->children->root,cell);
        }
    }
    free(old_func);
}
void evaluate(Cell** data, Cell *cell, Cell_func* old_func, int R ,int C) { 
    int initial_value = cell->value;
    Cell_func *func = cell->func;
    int val1 = 0, val2 = 0;
    if(func->flag1) val1 = func->Cell1->value;
    else val1 = func->value1;
    if(func->flag2) val2 = func->Cell2->value;
    else val2 = func->value2;
    cell->valid = 1;
    switch (func->op) {
        case FIX: {cell->value = val1; break;}
        case ADD: {
            cell->value = val1 + val2;
            if(func->flag1) func->Cell1->children->root = insert(func->Cell1->children->root, cell);
            if(func->flag2) func->Cell2->children->root = insert(func->Cell2->children->root, cell);
            break;
        }
        case SUB: {
            cell->value = val1 - val2; 
            if(func->flag1) func->Cell1->children->root = insert(func->Cell1->children->root, cell);
            if(func->flag2) func->Cell2->children->root = insert(func->Cell2->children->root, cell);
            break;
        }
        case MUL: {
            cell->value = val1*val2; 
            if(func->flag1) func->Cell1->children->root = insert(func->Cell1->children->root, cell);
            if(func->flag2) func->Cell2->children->root = insert(func->Cell2->children->root, cell);
            break;
        }
        case DIV: {
            if(val2 == 0) cell->valid = 0;          //////////////////////////////////////////////////////// TO BE DISCUSSED IF WE HAVE TO PUT IN DEPENDENCY SET IN THIS CASE
            else {
                cell->value = val1/val2;
                if(func->flag1) func->Cell1->children->root = insert(func->Cell1->children->root, cell);
                if(func->flag2) func->Cell2->children->root = insert(func->Cell2->children->root, cell);  
            }
            break;
        }
        case SLEEP: {                       ///////////////////////////////////////////////////////////////// HAVE TO MODIFY THIS: SLEEP CAN ALSO REQUIRE ADDRESS INSTEAD OF FIX VAL. ALSO INSERT IN AVL TREE IN THAT CASE
            sleep(val1);
            cell->value = val1;
            if(func->flag1) func->Cell1->children->root = insert(func->Cell1->children->root, cell);
            break;
        }
        case MIN:{ cell->value = min_eval(data, cell, func, R, C); break;}        
        case MAX:{ cell->value = max_eval(data, cell, func, R, C); break;}
        case STDEV:{ cell->value = stdev_eval(data, cell, func, R, C); break;}
        case SUM:{ cell->value = sum_eval(data, cell, func, R, C); break;}
        case AVG:{ cell->value = avg_eval(data, cell, func, R, C); break;}
    }
    remove_old_dependencies(data, old_func, cell, R, C);
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