#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "data_structures.h"


int min_eval(Cell** data, Cell_func* func, int C){         
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int mini = INT_MAX;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            if((*(data + C*(j-1) + i - 1))->valid == 0) {
                return INT_MIN;
            }
            mini = min(mini,(*(data + C*(j-1) + i - 1))->value);
        }        
    }
    return mini;
}

int max_eval(Cell** data, Cell_func* func, int C){       
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int maxi = INT_MIN;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            if((*(data + C*(j-1) + i - 1))->valid == 0) {
                return INT_MIN;
            }
            maxi = max(maxi,(*(data + C*(j-1) + i - 1))->value);
        }        
    }
    return maxi;
}

int sum_eval(Cell** data, Cell_func* func, int C){
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int sum = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            if((*(data + C*(j-1) + i - 1))->valid == 0) {
                return INT_MIN;
            }
            sum += (*(data + C*(j - 1) + i - 1))->value;
        }        
    }
    return sum;
}

int avg_eval(Cell** data, Cell_func* func, int C){
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int sum = 0;
    int count = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            if((*(data + C*(j-1) + i - 1))->valid == 0) {
                return INT_MIN;
            }
            sum += (*(data + C*(j - 1) + i - 1))->value;
            count++;
        }        
    }
    return sum/count;
}

int stdev_eval(Cell** data, Cell_func* func, int C){
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int sum = 0;
    int count = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            if((*(data + C*(j-1) + i - 1))->valid == 0) {
                return INT_MIN;
            }
            count++;
            sum += (*(data + C*(j - 1) + i - 1))->value;
        }        
    }
    long double mean = sum/count;
    long double sum_sq = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            sum_sq += pow((*(data + C*(j - 1) + i - 1))->value - mean, 2);
        }        
    }
    return sqrt(sum_sq/count);
}
void sleep(int seconds) {
    time_t start_time = time(NULL);
    while ((time(NULL) - start_time) < seconds);
}

void remove_old_dependencies(Cell** data, Cell_func* old_func, Cell* cell, int C){
    if(old_func->op>5){             // is a range function
        Cell* start=old_func->Cell1;
        Cell* end=old_func->Cell2;
        for (int col = start->col_name; col < end->col_name; col++) {
            for (int row = start->row_num; row < end->row_num ; row++) {
                ((*(data + C*(row - 1) + col - 1))->children)->root=
                    erase(((*(data + C*(row - 1) + col - 1))->children)->root, cell);       // erase from non existent (old) dependency
            }
        } 
    }
    else{        
        if(old_func->flag1) {
            old_func->Cell1->children->root=erase(old_func->Cell1->children->root,cell);
        }
        if(old_func->flag2) {
            old_func->Cell2->children->root=erase(old_func->Cell2->children->root,cell);
        }
    }
}
void calculate(Cell** data, Cell* cell, int C) {
    Cell_func *func = cell->func;
    if(cell->func == NULL) {
        cell->value=0;
        return;
    }
    int val1 = 0, val2 = 0;
    if(func->flag1) 
        val1 = func->Cell1->value;
    else 
        val1 = func->value1;
    if(func->flag2) 
        val2 = func->Cell2->value;
    else 
        val2 = func->value2;
    cell->valid = 1;
    int val = 0;
    switch (func->op) {
        case FIX: 
            cell->value = val1; 
            break;
        case ADD: {
            if((func->flag1 && (func->Cell1->valid == 0)) || (func->flag2 && (func->Cell2->valid == 0))) cell->valid = 0;
            else cell->value = val1 + val2;
            break;
        }
        case SUB: {
            if((func->flag1 && (func->Cell1->valid == 0)) || (func->flag2 && (func->Cell2->valid == 0))) cell->valid = 0;
            else cell->value = val1 - val2; 
            break;
        }
        case MUL: {
            if((func->flag1 && (func->Cell1->valid == 0)) || (func->flag2 && (func->Cell2->valid == 0))) cell->valid = 0;
            else cell->value = val1*val2; 
            break;
        }
        case DIV: {
            if((func->flag1 && (func->Cell1->valid == 0)) || (func->flag2 && (func->Cell2->valid == 0))) {
                cell->valid = 0; 
                break;
            }
            if(val2 == 0) cell->valid = 0;          
            else {
                cell->value = val1/val2;
            }            
            break;
        }
        case SLEEP: {        
            if((func->flag1 && (func->Cell1->valid == 0)) || (func->flag2 && (func->Cell2->valid == 0))) {
                cell->valid = 0; 
                break;
            }
            sleep(val1);
            cell->value = val1;
            break;
        }
        case MIN:
            val = min_eval(data, func, C);
            if(val == INT_MIN) cell->valid = 0;
            else cell->value = val;
            break;    
        case MAX:
            val = max_eval(data, func, C);
            if(val == INT_MIN) cell->valid = 0;
            else cell->value = val;
            break;
        case STDEV:
            val = stdev_eval(data, func, C);
            if(val == INT_MIN) cell->valid = 0;
            else cell->value = val;
            break;
        case SUM:
            val = sum_eval(data, func, C);
            if(val == INT_MIN) cell->valid = 0;
            else cell->value = val;
            break;
        case AVG:
            val = avg_eval(data, func, C);
            if(val == INT_MIN) cell->valid = 0;
            else cell->value = val;
            break;
        default:
            break;
    }
}
void update_parent_avls(Cell** data, Cell *cell, int C){
    Cell_func* func=cell->func;
    if(func==NULL) return;
    if(func->op>5) {          // is a range function
        Cell* cell1=func->Cell1;
        Cell* cell2=func->Cell2;
        for(int col=cell1->col_name; col<=cell2->col_name; col++){
            for(int row=cell1->row_num; row<=cell2->row_num; row++){
                (*(data + C*(row - 1) + col -1))->children->root=insert((*(data + C*(row - 1) + col -1))->children->root,cell);
            }
        }
    }
    else{
        if(func->flag1) {
            func->Cell1->children->root=insert(func->Cell1->children->root,cell);
        }
        if(func->flag2) {
            func->Cell2->children->root=insert(func->Cell2->children->root,cell);
        }
    }
}

int dfs(Cell* current_cell, HashTable* visited, HashTable* recStack, Stack *stack) {
    hash_insert(recStack, current_cell);
    ll_Node** temp = (ll_Node**)malloc(sizeof(ll_Node*));
    *temp = NULL;
    inorder(current_cell->children->root, temp);
    ll_Node* curr = *temp;
    while (curr) {
        if (hash_search(recStack, curr->data)) {
            ll_Node** old_temp=temp;
            if(temp!=NULL) while(*temp != NULL) {              // this frees the linkedlist
                ll_Node* temp2 = *temp;
                *temp = (*temp)->next;
                free(temp2);
            }
            if(old_temp!=NULL) free(old_temp);
            return 1; 
        } 
        else if (!hash_search(visited, curr->data)) {
            if (dfs(curr->data, visited, recStack, stack)) {

                ll_Node** old_temp=temp;
                if(temp!=NULL) while(*temp != NULL) {              // this frees the linkedlist
                    ll_Node* temp2 = *temp;
                    *temp = (*temp)->next;
                    free(temp2);
                }
                if(old_temp!=NULL) free(old_temp);
                return 1; 
            }
        }
        curr = curr->next; 
    }
    hash_insert(visited, current_cell);
    hash_remove(recStack, current_cell); // Remove node from recursion stack
    push(stack, current_cell); 
    ll_Node** old_temp=temp;
    if(temp!=NULL) while(*temp != NULL) {              // this frees the linkedlist
        ll_Node* temp2 = *temp;
        *temp = (*temp)->next;
        free(temp2);
    }
    if(old_temp!=NULL) free(old_temp);
    return 0;
}

ll_Node* topological_sort(Cell* current_cell){
    HashTable* visited = create_table(TABLE_SIZE);
    HashTable* recStack = create_table(TABLE_SIZE);
    Stack *stack = createStack();
    if (dfs(current_cell, visited, recStack, stack)) {
        freeStack(stack);
        free_table(visited);
        free_table(recStack);
        if(stack) free(stack);
        return NULL;
    }
    free_table(visited);
    free_table(recStack);
    ll_Node* ret=stack->top;
    if(stack) free(stack);
    return ret;
}

int update_children(Cell** data, Cell* cell, int C) {
    ll_Node* head = topological_sort(cell);
    if(head == NULL) return 0;
    bool negative_in_sleep = false;
    while (head != NULL) {
        Cell* element = head->data;
        if(element->func != NULL && element->func->op == SLEEP) {
            if(element->func->flag1 && element->func->Cell1->value < 0) {
                negative_in_sleep = true;
            }
            else if(element->func->flag2 && element->func->Cell2->value < 0) {
                negative_in_sleep = true;
            }
            else if(element->func->value1 < 0) {
                negative_in_sleep = true;
            }
        }
        if(!negative_in_sleep) {
            calculate(data, element, C);    
        }
        ll_Node* temp = head;
        head = head->next;
        free(temp);
    }
    if(negative_in_sleep) {
        return 0;
    }
    return 1;
}


int evaluate(Cell** data, Cell *cell, Cell_func* old_func, int R ,int C) { 
    if(old_func!=NULL){
        remove_old_dependencies(data, old_func, cell, C);
    }
    update_parent_avls(data,cell,C);
    // this func would take care of updating the children of the cell and also detect cycle if any
    int x = update_children(data, cell, C); 

    if(x == 0) {
        Cell_func* func=cell->func;
        cell->func=old_func;
        evaluate(data,cell,func,R,C);
        return 0;
    }
    if(old_func!=NULL) free(old_func);
    return x;
}