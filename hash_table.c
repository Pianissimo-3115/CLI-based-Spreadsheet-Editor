#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

#define TABLE_SIZE 503

int hash(Cell* cell, int size) {
    return (cell->col_name+cell->row_num)%size;
}

HashTable* create_table(int size) {
    HashTable *ht = malloc(sizeof(HashTable));
    if (!ht) {
        perror("Failed to allocate hash table");
        exit(EXIT_FAILURE);
    }
    ht->size = size;
    ht->table = (ll_Node**)malloc(sizeof(ll_Node*) * size);
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
    int index = hash(cell, ht->size);
    ll_Node *current = ht->table[index];
    
    while (current != NULL) {
        if (current->data == cell) {
            return;
        }
        current = current->next;
    }
    
    insertAtPosition(current, cell);
}

void hash_remove(HashTable *ht, Cell *cell) {
    if (!ht || !cell)
        return;
    int index = hash(cell, ht->size);
    ll_Node *current = ht->table[index];
    ll_Node *prev = NULL;

    while (current != NULL) {
        if (current->data == cell) {
            if (prev == NULL) {
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
int hash_search(HashTable *ht, Cell* cell) {
    if (!ht)
        return 0;
    int index = hash(cell, ht->size);
    ll_Node *current = ht->table[index];
    while (current != NULL) {
        if (current->data==cell) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void free_table(HashTable *ht) {
    if (!ht)
        return;
    for (int i = 0; i < ht->size; i++) {
        freeLinkedList(*((ht->table)+i));
    }
    free(ht);
}
#ifndef MAIN
int main() {
    HashTable *ht = create_table(TABLE_SIZE);

    Cell cell1 = { .col_name = 1, .row_num = 1 };
    Cell cell2 = { .col_name = 2, .row_num = 2 };
    Cell cell3 = { .col_name = 3, .row_num = 3 };

    hash_insert(ht, &cell1);
    hash_insert(ht, &cell2);
    hash_insert(ht, &cell3);

    printf("Search cell1: %d\n", search(ht, &cell1));
    printf("Search cell2: %d\n", search(ht, &cell2));
    printf("Search cell3: %d\n", search(ht, &cell3));

    hash_remove(ht, &cell2);
    printf("Search cell2 after removal: %d\n", search(ht, &cell2));

    free_table(ht);

    return 0;
}
#endif