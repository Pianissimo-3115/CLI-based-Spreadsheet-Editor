#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "data_structures.h"


int min_eval(Cell** data,Cell* cell, Cell_func* func, int R, int C){         
    Cell* cell1 = func->Cell1;
    Cell* cell2 = func->Cell2;
    int mini = INT_MAX;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            mini = min(mini,(*(data + C*j + i - 1))->value);
            // (*(data + C*i + j -1))->children->root=insert((*(data + C*i + j -1))->children->root,cell);
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
            maxi = max(maxi,(*(data + C*j + i - 1))->value);
            // (*(data + C*i + j -1))->children->root=insert((*(data + C*i + j -1))->children->root,cell);
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
            sum += (*(data + C*j + i - 1))->value;
            // (*(data + C*i + j -1))->children->root=insert((*(data + C*i + j -1))->children->root,cell);
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
            sum += (*(data + C*j + i - 1))->value;
            // (*(data + C*i + j -1))->children->root=insert((*(data + C*i + j -1))->children->root,cell);
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
            sum += (*(data + C*j + i - 1))->value;
            // (*(data + C*i + j -1))->children->root=insert((*(data + C*i + j -1))->children->root,cell);
        }        
    }
    int mean = sum/count;
    int sum_sq = 0;
    for (int i = cell1->col_name; i <=cell2->col_name; i++){
        for (int j = cell1->row_num; j <= cell2->row_num; j++){
            sum_sq += pow((*(data + C*j + i - 1))->value - mean, 2);
        }        
    }
    return sqrt(sum_sq/count);
}
void sleep(int seconds) {
    time_t start_time = time(NULL);
    while ((time(NULL) - start_time) < seconds);
}



// void  update_depth(Cell** data, Cell* cell, int R, int C){
//     int old_depth=cell->depth;
//     Cell_func* func=cell->func;
//     if(func->op>5) {            // is a range function
//         Cell* start=func->Cell1;
//         Cell* end=func->Cell2;
//         for(int col=start->col_name;col<=end->col_name;col++){
//             for(int row=start->row_num;row<=end->row_num;row++){
//                 cell->depth=max(cell->depth,(*(data + C*row + col - 1))->depth+1);
//             }
//         }
//     }
//     else{
//         bool done=false;
//         if(func->flag1) {
//             cell->depth=max(cell->depth,func->Cell1->depth+1);
//             done=true;
//         }
//         if(func->flag2) {
//             cell->depth=max(cell->depth,func->Cell2->depth+1);
//             done=true;
//         }
//         if(!done) cell->depth=0;
//     }
//     return;
// }
void remove_old_dependencies(Cell** data, Cell_func* old_func, Cell* cell, int R, int C){
    if(old_func->op>5){             // is a range function
        Cell* start=old_func->Cell1;
        Cell* end=old_func->Cell2;
        for (int col = start->col_name; col < end->col_name; col++) {
            for (int row = start->row_num; row < end->row_num ; row++) {
                ((*(data + C*row + col - 1))->children)->root=
                    erase(((*(data + C*row + col - 1))->children)->root, cell);       // erase from non existent (old) dependency
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
    free(old_func);
}
void calculate(Cell** data, Cell* cell, int R, int C) {
    int initial_value = cell->value;
    Cell_func *func = cell->func;
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
    switch (func->op) {
        case FIX: 
            cell->value = val1; 
            break;
        case ADD: {
            cell->value = val1 + val2;

            // if(func->flag1) func->Cell1->children->root = insert(func->Cell1->children->root, cell);
            // if(func->flag2) func->Cell2->children->root = insert(func->Cell2->children->root, cell);
            break;
        }
        case SUB: {
            cell->value = val1 - val2; 
            // if(func->flag1) func->Cell1->children->root = insert(func->Cell1->children->root, cell);
            // if(func->flag2) func->Cell2->children->root = insert(func->Cell2->children->root, cell);
            break;
        }
        case MUL: {
            cell->value = val1*val2; 
            // if(func->flag1) func->Cell1->children->root = insert(func->Cell1->children->root, cell);
            // if(func->flag2) func->Cell2->children->root = insert(func->Cell2->children->root, cell);
            break;
        }
        case DIV: {
            if(val2 == 0) cell->valid = 0;          //////////////////////////////////////////////////////// TO BE DISCUSSED IF WE HAVE TO PUT IN DEPENDENCY SET IN THIS CASE
            else {
                cell->value = val1/val2;
                // if(func->flag1) func->Cell1->children->root = insert(func->Cell1->children->root, cell);
                // if(func->flag2) func->Cell2->children->root = insert(func->Cell2->children->root, cell);  
            }
            break;
        }
        case SLEEP: {                       ///////////////////////////////////////////////////////////////// HAVE TO MODIFY THIS: SLEEP CAN ALSO REQUIRE ADDRESS INSTEAD OF FIX VAL. ALSO INSERT IN AVL TREE IN THAT CASE
            sleep(val1);
            cell->value = val1;
            // if(func->flag1) func->Cell1->children->root = insert(func->Cell1->children->root, cell);
            break;
        }
        case MIN:
            cell->value = min_eval(data, cell, func, R, C); 
            break;    
        case MAX:
            cell->value = max_eval(data, cell, func, R, C); 
            break;
        case STDEV:
            cell->value = stdev_eval(data, cell, func, R, C); 
            break;
        case SUM:
            cell->value = sum_eval(data, cell, func, R, C); 
            break;
        case AVG:
            cell->value = avg_eval(data, cell, func, R, C); 
            break;
    }
}
void update_parent_avls(Cell** data, Cell *cell, int R, int C, Cell_func* old_func){
    Cell_func* func=cell->func;
    bool was_range_func;
    if(old_func->op>5) was_range_func=true;
    else was_range_func=false;
    if(func->op>5) {          // is a range function
        Cell* cell1=func->Cell1;
        Cell* cell2=func->Cell2;
        for(int col=cell1->col_name; col<=cell2->col_name; col++){
            for(int row=cell1->row_num; row<=cell2->row_num; row++){
                if(was_range_func && old_func->Cell1->col_name<=col && old_func->Cell2->col_name>=col && old_func->Cell1->row_num<=row && old_func->Cell2->row_num>=row) continue;
                if(!was_range_func && old_func->flag1 && old_func->Cell1->col_name==col && old_func->Cell1->row_num==row) continue;
                if(!was_range_func && old_func->flag2 && old_func->Cell2->col_name==col && old_func->Cell2->row_num==row) continue;
                (*(data + C*row + col -1))->children->root=insert((*(data + C*row + col -1))->children->root,cell);
            }
        }
    }
    else{
        if(func->flag1) {
            if(was_range_func && old_func->Cell1->col_name<=func->Cell1->col_name && old_func->Cell2->col_name>=func->Cell1->col_name && old_func->Cell1->row_num<=func->Cell1->row_num && old_func->Cell2->row_num>=func->Cell1->row_num) goto skip;
            if(!was_range_func && old_func->flag1 && old_func->Cell1->col_name==func->Cell1->col_name && old_func->Cell1->row_num==func->Cell1->row_num) goto skip;
            if(!was_range_func && old_func->flag2 && old_func->Cell2->col_name==func->Cell1->col_name && old_func->Cell2->row_num==func->Cell1->row_num) goto skip;
            func->Cell1->children->root=insert(func->Cell1->children->root,cell);
        }
        skip:
        if(func->flag2) {
            if(was_range_func && old_func->Cell1->col_name<=func->Cell2->col_name && old_func->Cell2->col_name>=func->Cell2->col_name && old_func->Cell1->row_num<=func->Cell2->row_num && old_func->Cell2->row_num>=func->Cell2->row_num) return;
            if(!was_range_func && old_func->flag1 && old_func->Cell1->col_name==func->Cell2->col_name && old_func->Cell1->row_num==func->Cell2->row_num) return;
            if(!was_range_func && old_func->flag2 && old_func->Cell2->col_name==func->Cell2->col_name && old_func->Cell2->row_num==func->Cell2->row_num) return;
            func->Cell2->children->root=insert(func->Cell2->children->root,cell);
        }
    }
}

int dfs(Cell* current_cell, HashTable* visited, HashTable* recStack, Stack *stack) {
    hash_insert(visited, current_cell);
    hash_insert(recStack, current_cell);
    ll_Node* temp = NULL;
    inorder(current_cell->children->root, temp);
    ll_Node*curr = temp;
    while (curr) {
        if (!hash_search(visited, curr->data)) {
            if (dfs(curr->data, visited, recStack, stack)) {
                return 1; 
            }
        } 
        else if (hash_search(recStack, curr->data)) {
            return 1; 
        }
        curr = curr->next; 
    }
    // function to be implemented
    hash_remove(recStack, current_cell); // Remove node from recursion stack
    push(stack, current_cell); 
    while(temp != NULL) {
        ll_Node* temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    return 0;
}

ll_Node* topological_sort(Cell* current_cell){
    HashTable* visited = create_table(TABLE_SIZE);
    HashTable* recStack = create_table(TABLE_SIZE);
    Stack *stack = createStack();
    ll_Node* head = NULL;
    ll_Node* temp = NULL;
    inorder(current_cell->children->root, temp);

    while(temp != NULL){
        if(!hash_search(visited, temp->data)){
            if (dfs(temp->data, visited, recStack, stack)) {
                free(stack);
                return NULL;
            }
        }
        temp = temp->next;
    }

    while(!isEmpty(stack)) {
        insertAtHead(head,pop(stack));
    }
    insertAtHead(head, current_cell);
    freeStack(stack);
    freeLinkedList(temp);
    free_table(visited);
    free_table(recStack);
    return head;
}

int update_children(Cell** data, Cell* cell, int R, int C) {
    ll_Node* head = topological_sort(cell);
    if(head == NULL) return 0;
    while (head != NULL) {
        Cell* element = head->data;
        calculate(data, element, R, C);
        ll_Node* temp = head;
        head = head->next;
        free(temp);
    }
    return 1;
}


int evaluate(Cell** data, Cell *cell, Cell_func* old_func, int R ,int C) { 
    // int initial_value=cell->value;
    if(old_func!=NULL){
        remove_old_dependencies(data, old_func, cell, R, C);
        update_parent_avls(data,cell,R,C,old_func);
    }

    // this func would take care of updating the children of the cell and also detect cycle if any
    return update_children(data, cell, R, C); 
}
#ifndef MAIN
int main(){
    Cell** data = (Cell**)malloc(5 * sizeof(Cell*));
    for (int i = 0; i < 5; i++) {
        data[i] = (Cell*)malloc(5 * sizeof(Cell));
        for (int j = 0; j < 5; j++) {
            data[i][j].value = i * 5 + j;
            data[i][j].col_name = j + 1;
            data[i][j].row_num = i + 1;
            data[i][j].valid = 1;
            data[i][j].func = NULL;
            data[i][j].children = (AVL*)malloc(sizeof(AVL));
            data[i][j].children->root = NULL;
        }
    }
    Cell_func* func = (Cell_func*)malloc(sizeof(Cell_func));
    func->op = ADD;
    func->flag1 = 1;
    func->flag2 = 1;
    func->Cell1 = &data[0][1];
    func->Cell2 = &data[1][0];
    data[0][0].func = func;     // A1 = B1 + A2
    evaluate(data, &data[0][0], NULL, 5, 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", data[i][j].value);
        }
        printf("\n");
    }

    Cell_func* func2 = (Cell_func*)malloc(sizeof(Cell_func));
    func2->op = ADD;
    func2->flag1 = 1;
    func2->flag2 = 1;
    func2->Cell1 = &data[0][0];
    func2->Cell2 = &data[1][1];
    data[1][0].func = func2;     // B1 = A1 + B2
    evaluate(data, &data[0][0], func, 5, 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", data[i][j].value);
        }
        printf("\n");
    }

    Cell_func* func3 = (Cell_func*)malloc(sizeof(Cell_func));
    func3->op = ADD;
    func3->flag1 = 1;
    func3->flag2 = 1;
    func3->Cell1 = &data[0][2];
    func3->Cell2 = &data[1][2];
    data[1][1].func = func3;     // B2 = A2 + B3
    evaluate(data, &data[0][0], func2, 5, 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", data[i][j].value);
        }
        printf("\n");
    }

    Cell_func* func4 = (Cell_func*)malloc(sizeof(Cell_func));
    func4->op = ADD;
    func4->flag1 = 1;
    func4->flag2 = 1;
    func4->Cell1 = &data[0][3];
    func4->Cell2 = &data[1][3];
    data[1][2].func = func4;     // B3 = A3 + B4
    evaluate(data, &data[0][0], func3, 5, 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", data[i][j].value);
        }
        printf("\n");
    }



    printf("\n");
    printf("Done\n");
}
#endif