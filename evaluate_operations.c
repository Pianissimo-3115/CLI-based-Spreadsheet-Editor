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
    insert(visited, current_cell);
    insert(recStack, current_cell);
    ll_Node* temp = NULL;
    inorder(current_cell->children->root, temp);
    ll_Node*curr = temp;
    while (curr) {
        if (search(visited, curr->data) == NULL) {
            if (dfs(curr, visited, recStack, stack)) {
                return 1; 
            }
        } 
        else if (search(recStack, curr->data)) {
            return 1; 
        }
        curr = curr->next; 
    }
    // function to be implemented
    // remove(recStack, current_cell); // Remove node from recursion stack
    push(stack, current_cell); 
    while(temp != NULL) {
        ll_Node* temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    return 0;
}

ll_Node* topologicalSort(Cell* current_cell){
    HashTable* visited = create_table(TABLE_SIZE);
    HashTable* recStack = create_table(TABLE_SIZE);
    Stack *stack = createStack();
    ll_Node* head = NULL;
    ll_Node* temp = NULL;
    inorder(current_cell->children->root, temp);

    while(temp != NULL){
        if(search(visited, temp->data) == NULL){
            if (dfs(temp->data, visited, recStack, stack)) {
                free(stack->array);
                free(stack);
                return NULL;
            }
        }
        temp = temp->next;
    }

    while(!isEmpty(stack)) {
        insertAtHead(&head,pop(stack));
    }
    insertAtHead(&head, current_cell);
    free(stack->array);
    free(stack);
    free(temp);
    free(visited->table);
    free(recStack->table);
    return head;
}

int update_children(Cell** data, Cell* cell, int R, int C) {
    ll_Node* head = NULL;
    head = topological_sort(cell->children->root);
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
    int initial_value=cell->value;
    remove_old_dependencies(data, old_func, cell, R, C);
    // calculate(data, cell, R, C);
    // update_depth(data, cell, R, C);
    update_parent_avls(data,cell,R,C,old_func);

    // this func would take care of updating the children of the cell and also detect cycle if any
    return update_children(data, cell, R, C); 
}

// int main(){
//     Cell cell1 = { .value = 0, .col_name = 1, .row_num = 1, .valid = 1, .func = NULL, .children = NULL, .depth = 0};
//     Cell cell2 = { .value = 1, .col_name = 2, .row_num = 1, .valid = 1, .func = NULL, .children = NULL, .depth = 1};
//     Cell cell3 = { .value = 2, .col_name = 1, .row_num = 2, .valid = 1, .func = NULL, .children = NULL, .depth = 2};
//     Cell cell4 = { .value = 3, .col_name = 2, .row_num = 2, .valid = 1, .func = NULL, .children = NULL, .depth = 3};
//     Cell cell5 = { .value = 4, .col_name = 3, .row_num = 3, .valid = 1, .func = NULL, .children = NULL, .depth = 4};
//     Cell cell6 = { .value = 5, .col_name = 4, .row_num = 4, .valid = 1, .func = NULL, .children = NULL, .depth = 5};
//     cell1.children = (AVL*)malloc(sizeof(AVL));
//     cell1.children->root = NULL;
//     cell1.children->root = insert(cell1.children->root, &cell2);
//     cell1.children->root = insert(cell1.children->root, &cell3);
//     cell1.children->root = insert(cell1.children->root, &cell4);
//     cell1.children->root = insert(cell1.children->root, &cell5);
//     cell1.children->root = insert(cell1.children->root, &cell6);
//     cell2.children = (AVL*)malloc(sizeof(AVL));
//     cell2.children->root = NULL;
//     cell2.children->root = insert(cell2.children->root, &cell3);
//     cell2.children->root = insert(cell2.children->root, &cell4);
//     cell2.children->root = insert(cell2.children->root, &cell5);
//     cell2.children->root = insert(cell2.children->root, &cell6);
//     cell3.children = (AVL*)malloc(sizeof(AVL));
//     cell3.children->root = NULL;
//     cell3.children->root = insert(cell3.children->root, &cell4);
//     cell3.children->root = insert(cell3.children->root, &cell5);
//     cell3.children->root = insert(cell3.children->root, &cell6);
//     cell4.children = (AVL*)malloc(sizeof(AVL));
//     cell4.children->root = NULL;
//     cell4.children->root = insert(cell4.children->root, &cell5);
//     cell4.children->root = insert(cell4.children->root, &cell6);
//     cell5.children = (AVL*)malloc(sizeof(AVL));
//     cell5.children->root = NULL;
//     cell5.children->root = insert(cell5.children->root, &cell6);
//     LinkedList merged;
//     merged.head = NULL;
//     inorder(cell5.children->root, &merged, merged.head);
//     ll_Node* temp = merged.head;
//     while (temp != NULL) {
//         printf("%d ", temp->data->value);
//         temp = temp->next;
//     }
//     printf("\n");
//     inorder(cell4.children->root, &merged, merged.head);
//     temp = merged.head;
//     while (temp != NULL) {
//         printf("%d ", temp->data->value);
//         temp = temp->next;
//     }
//     printf("\n");
//     inorder(cell3.children->root, &merged, merged.head);
//     temp = merged.head;
//     while (temp != NULL) {
//         printf("%d ", temp->data->value);
//         temp = temp->next;
//     }
//     printf("\n");
//     inorder(cell2.children->root, &merged, merged.head);
//     temp = merged.head;
//     while (temp != NULL) {
//         printf("%d ", temp->data->value);
//         temp = temp->next;
//     }
//     printf("\n");
//     inorder(cell1.children->root, &merged, merged.head);
//     temp = merged.head;
//     while (temp != NULL) {
//         printf("%d ", temp->data->value);
//         temp = temp->next;
//     }
//     printf("\n");
//     printf("Done\n");
// }