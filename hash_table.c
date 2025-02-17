#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

#define TABLE_SIZE 503

typedef struct {
    ll_Node **table;
    int size;
} HashTable;

int hash(int key, int size) {
    return key % size;
}

HashTable* create_table(int size) {
    HashTable *ht = malloc(sizeof(HashTable));
    if (!ht) {
        perror("Failed to allocate hash table");
        exit(EXIT_FAILURE);
    }
    ht->size = size;
    ht->table = malloc(sizeof(ll_Node*) * size);
    if (!ht->table) {
        perror("Failed to allocate table buckets");
        free(ht);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void hash_insert(HashTable *ht, Cell *cell) {
    if (!ht || !cell)
        return;
    int index = hash(cell->col_name, ht->size);
    ll_Node *current = ht->table[index];
    
    while (current != NULL) {
        if (current->data->col_name == cell->col_name) {
            current->data->row_num = cell->row_num;
            current->data->value   = cell->value;
            current->data->valid   = cell->valid;
            return;
        }
        current = current->next;
    }
    
    insertAtEnd((ht->table+index), cell);
}

Cell* search(HashTable *ht, int col_name) {
    if (!ht)
        return NULL;
    int index = hash(col_name, ht->size);
    ll_Node *current = ht->table[index];
    while (current != NULL) {
        if (current->data->col_name == col_name) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

void free_table(HashTable *ht) {
    if (!ht)
        return;
    for (int i = 0; i < ht->size; i++) {
        freeLinkedList(((ht->table)+i));
    }
    free(ht->table);
    free(ht);
}

#ifndef TEST_HASH_TABLE
int main() {
    HashTable *ht = create_table(TABLE_SIZE);

    Cell *cell1 = malloc(sizeof(Cell));
    cell1->col_name = 10;
    cell1->row_num  = 1;
    cell1->value    = 100;
    cell1->valid    = 1;
    cell1->func     = NULL;
    cell1->children = NULL;
    cell1->run_cnt  = 0;

    Cell *cell2 = malloc(sizeof(Cell));
    cell2->col_name = 21;
    cell2->row_num  = 2;
    cell2->value    = 200;
    cell2->valid    = 1;
    cell2->func     = NULL;
    cell2->children = NULL;
    cell2->run_cnt  = 0;

    Cell *cell3 = malloc(sizeof(Cell));
    cell3->col_name = 32;
    cell3->row_num  = 3;
    cell3->value    = 300;
    cell3->valid    = 1;
    cell3->func     = NULL;
    cell3->children = NULL;
    cell3->run_cnt  = 0;

    hash_insert(ht, cell1);
    hash_insert(ht, cell2);
    hash_insert(ht, cell3);

    Cell* found = search(ht, 21);
    if (found) {
        printf("Found cell: col_name = %d, row_num = %d, value = %d\n",
               found->col_name, found->row_num, found->value);
    } else {
        printf("Cell with col_name 21 not found.\n");
    }

    free_table(ht);
    return 0;
}
#endif
