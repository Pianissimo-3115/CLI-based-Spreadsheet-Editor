#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int size;
    int capacity;
    bool (*compare)(int, int);
} Heap;

Heap* createHeap(int capacity, bool (*compare)(int, int)) {
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->compare = compare;
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void upheap(Heap *heap, int index) {
    int parent = (index - 1) / 2;
    if (index > 0 && heap->compare(heap->data[index], heap->data[parent])) {
        swap(&heap->data[index], &heap->data[parent]);
        upheap(heap, parent);
    }
}

void downheap(Heap *heap, int index) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int smallest = index;

    if (left_child < heap->size && heap->compare(heap->data[left_child], heap->data[smallest])) {
        smallest = left_child;
    }
    if (right_child < heap->size && heap->compare(heap->data[right_child], heap->data[smallest])) {
        smallest = right_child;
    }
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        downheap(heap, smallest);
    }
}

void insert(Heap *heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (int*)realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size++] = value;
    upheap(heap, heap->size - 1);
}

int extract(Heap *heap) {
    if (heap->size == 0) return -1; // Return -1 for an empty heap
    if (heap->size == 1) return heap->data[--heap->size];
    
    int top_value = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    downheap(heap, 0);
    return top_value;
}

int top(Heap *heap) {
    return (heap->size == 0) ? -1 : heap->data[0];
}

void freeHeap(Heap *heap) {
    free(heap->data);
    free(heap);
}

// comparison function for a min-heap
bool minHeapCompare(int a, int b) {
    return a < b;
}
// comparison function for a max-heap
bool maxHeapCompare(int a, int b) {
    return a > b;
}


void testMinHeap() {
    printf("Testing Min Heap:\n");
    Heap *minHeap = createHeap(5, minHeapCompare);

    insert(minHeap, 10);
    insert(minHeap, 20);
    insert(minHeap, 5);
    insert(minHeap, 30);
    insert(minHeap, 3);
    
    printf("Top element (should be 3): %d\n", top(minHeap));
    printf("Extracted element (should be 3): %d\n", extract(minHeap));
    printf("Top element after extraction (should be 5): %d\n", top(minHeap));

    insert(minHeap, 1);
    printf("Top element after inserting 1 (should be 1): %d\n", top(minHeap));

    while (minHeap->size > 0) {
        printf("Extracting: %d\n", extract(minHeap));
    }

    freeHeap(minHeap);
}

void testMaxHeap() {
    printf("\nTesting Max Heap:\n");
    Heap *maxHeap = createHeap(5, maxHeapCompare);

    insert(maxHeap, 10);
    insert(maxHeap, 20);
    insert(maxHeap, 5);
    insert(maxHeap, 30);
    insert(maxHeap, 3);
    
    printf("Top element (should be 30): %d\n", top(maxHeap));
    printf("Extracted element (should be 30): %d\n", extract(maxHeap));
    printf("Top element after extraction (should be 20): %d\n", top(maxHeap));

    insert(maxHeap, 40);
    printf("Top element after inserting 40 (should be 40): %d\n", top(maxHeap));

    while (maxHeap->size > 0) {
        printf("Extracting: %d\n", extract(maxHeap));
    }

    freeHeap(maxHeap);
}

int main() {
    testMinHeap();
    testMaxHeap();
    return 0;
}
