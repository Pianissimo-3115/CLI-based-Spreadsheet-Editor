#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../data_structures.h"

void test_create_table() {
    HashTable* ht = create_table(TABLE_SIZE);
    assert(ht != NULL);
    assert(ht->size == TABLE_SIZE);
    assert(ht->table != NULL);
    free_table(ht);
    printf("test_create_table passed\n");
}

void test_hash_insert_and_search() {
    HashTable* ht = create_table(TABLE_SIZE);
    Cell cell1 = {1, 1, 10, 1, NULL, NULL};
    Cell cell2 = {2, 2, 20, 1, NULL, NULL};
    
    hash_insert(ht, &cell1);
    hash_insert(ht, &cell2);
    
    assert(hash_search(ht, &cell1) == 1);
    assert(hash_search(ht, &cell2) == 1);
    
    Cell cell3 = {3, 3, 30, 1, NULL, NULL};
    assert(hash_search(ht, &cell3) == 0);
    
    free_table(ht);
    printf("test_hash_insert_and_search passed\n");
}

void test_hash_remove() {
    HashTable* ht = create_table(TABLE_SIZE);
    Cell cell1 = {1, 1, 10, 1, NULL, NULL};
    Cell cell2 = {2, 2, 20, 1, NULL, NULL};
    
    hash_insert(ht, &cell1);
    hash_insert(ht, &cell2);
    
    hash_remove(ht, &cell1);
    assert(hash_search(ht, &cell1) == 0);
    assert(hash_search(ht, &cell2) == 1);
    
    free_table(ht);
    printf("test_hash_remove passed\n");
}

void test_hash_collision() {
    HashTable* ht = create_table(TABLE_SIZE);
    Cell cell1 = {1, 1, 10, 1, NULL, NULL};
    Cell cell2 = {1 + TABLE_SIZE, 1, 20, 1, NULL, NULL};  // This should hash to the same index as cell1
    
    hash_insert(ht, &cell1);
    hash_insert(ht, &cell2);
    
    assert(hash_search(ht, &cell1) == 1);
    assert(hash_search(ht, &cell2) == 1);
    
    hash_remove(ht, &cell1);
    assert(hash_search(ht, &cell1) == 0);
    assert(hash_search(ht, &cell2) == 1);
    
    free_table(ht);
    printf("test_hash_collision passed\n");
}

int main() {
    test_create_table();
    test_hash_insert_and_search();
    test_hash_remove();
    test_hash_collision();
    
    printf("All hash table tests passed successfully!\n");
    return 0;
}
