#ifndef cell_operations
#define cell_operations

    #define windowWidth  10
    #define windowHeight 10
    #include<stdbool.h>

    // #include "data_structures.h"
    
    typedef enum ops { FIX, SLEEP, ADD, SUB, MUL, DIV, MIN, MAX, STDEV, SUM, AVG, DISABLE_OUT, ENABLE_OUT, SCROLL} ops;
    typedef struct Cell_func Cell_func;
    typedef struct AVL AVL;

    typedef struct {
        int col_name;           
        int row_num;
        int value; 
        int valid;                      
        Cell_func *func;
        AVL* children;
        int depth;
        
    } Cell;

    struct Cell_func {      ////////////////// TO PREVENT BUG, we can keep a rule that in a unary operation, everything should be set to NULL except Cell1 or value1. In binary operations, either of Cell1 and Value1 should be NULL and either of Cell2 and Value2 should be NULL 
        union{
            int value1;
            Cell* Cell1;
        };
        union{
            int value2;
            Cell* Cell2;
        };
        bool flag1,flag2;       ////////////// THESE FLAGS SHOULD BE TRUE IF CELL IS USED AND FALSE IF FIX VALUE IS USED
        ops op;        
    };
        
    void evaluate(Cell** data, Cell *cell, int R ,int C);


#endif