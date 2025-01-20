#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include "cell_operations.h"
#define max(A, B) ((A) > (B) ? (A) : (B))
#define min(A, B) ((A) < (B) ? (A) : (B))

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

void evaluate(Cell** data, Cell *cell, int R ,int C) {
    Cell_func *func = cell->func;
    int val1 = 0, val2 = 0;
    if(func->Cell1 != NULL) val1 = func->Cell1->value;
    if(func->Cell2 != NULL) val1 = func->Cell2->value;
    cell->valid = 1;
    switch (func->op) {
        case FIX: {cell->value = func-> fix_val; break;}
        case ADD: {cell->value = val1 + val2; break;}
        case SUB: {cell->value = val1 - val2; break;}
        case MUL: {cell->value = val1*val2; break;}
        case DIV: {
            if(val2 == 0) cell->valid = 0;
            else cell->value = val1/val2;
            break;
        }
        case SLEEP: {
            sleep(func->fix_val);
            cell->value = val1;
            break;
        }
        case MIN:{ cell->value = min_eval(data, func, R, C); break;}        
        case MAX:{ cell->value = max_eval(data, func, R, C); break;}
        case STDEV:{ cell->value = stdev_eval(data, func, R, C); break;}
        case SUM:{ cell->value = sum_eval(data, func, R, C); break;}
        case AVG:{ cell->value = avg_eval(data, func, R, C); break;}
    }
    return;
}

int main(){
    unsigned int R, C;
    scanf("%u %u", &R, &C);
    // Cell** data = calloc(R*C, sizeof(Cell*));
    // display_window(data, 23, 23, R, C);    
}