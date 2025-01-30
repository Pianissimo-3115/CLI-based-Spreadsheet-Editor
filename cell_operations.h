#ifndef CELL_OPERATIONS_H
#define CELL_OPERATIONS_H

#include <stdbool.h>

#define windowWidth  10
#define windowHeight 10

typedef struct AVL AVL;
typedef struct Cell Cell;
typedef struct Cell_func Cell_func;


typedef enum ops { 
    FIX, SLEEP, ADD, SUB, MUL, DIV, MIN, MAX, 
    STDEV, SUM, AVG, DISABLE_OUT, ENABLE_OUT, SCROLL
} ops;


struct Cell {
    int col_name;           
    int row_num;
    int value; 
    int valid;                      
    Cell_func *func;
    AVL* children;
    int depth;
};

struct Cell_func {
    union {
        int value1;
        Cell* Cell1;
    };
    union {
        int value2;
        Cell* Cell2;
    };
    bool flag1, flag2;
    ops op;        
};


void evaluate(Cell** data, Cell *cell, int R, int C);

#endif