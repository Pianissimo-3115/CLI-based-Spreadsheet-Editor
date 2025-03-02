#ifndef CELL_OPERATIONS_H
#define CELL_OPERATIONS_H

#include <stdbool.h>

#define windowWidth  10
#define windowHeight 10
#define max(A, B) ((A) > (B) ? (A) : (B))
#define min(A, B) ((A) < (B) ? (A) : (B))

typedef struct AVL AVL;
typedef struct Cell Cell;
typedef struct Cell_func Cell_func;


typedef enum ops { 
    FIX, SLEEP, ADD, SUB, MUL, DIV, MIN, MAX, 
    STDEV, SUM, AVG, DISABLE_OUT, ENABLE_OUT, SCROLL
} ops;


struct Cell {
    int col_name: 8;           
    int row_num: 8;
    int value; 
    int valid: 16;                      
    Cell_func *func;
    AVL* children;
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
    bool flag1, flag2;              // FOR BOTH FLAGS: 0 MEANS VALUE, 1 MEANS CELL      IF NOT USING TWO VALUES (SLEEP OR FIX) IDLE SHOULD BE 0
    ops op;        
};


typedef enum inputType {Invalid, Movement, Assignment, Display} inputType;
struct parsedInput
{
    inputType inpType;

    ops operation;

    bool val1Type; // 1 if address, 0 if int
    int val1Col;
    int val1Row;
    int val1Int;

    bool val2Type;
    int val2Col;
    int val2Row;
    int val2Int;

    int targetCol;
    int targetRow;

};
void parse_input(char* inp, struct parsedInput* parsed_out, int R, int C);
void display_window(Cell** data, int currR, int currC, int R, int C);
int evaluate(Cell** data, Cell *cell, Cell_func* old_func, int R ,int C);

#endif