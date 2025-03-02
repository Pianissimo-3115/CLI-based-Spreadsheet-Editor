#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

int hash(Cell* cell, int size) {
    return (cell->col_name+cell->row_num-2)%size;
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
    insertAtHead(ht->table+index, cell);

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
        if(*((ht->table)+i)) freeLinkedList(*((ht->table)+i));
    }
    free(ht->table);
    free(ht);
}