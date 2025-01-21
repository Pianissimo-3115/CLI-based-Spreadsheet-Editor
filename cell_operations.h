#ifndef cell_operations
#define cell_operations

    #define windowWidth  10
    #define windowHeight 10
    
    typedef enum ops { FIX, ADD, SUB, MUL, DIV, MIN, MAX, STDEV, SUM, AVG, SLEEP} ops;
    typedef struct Cell_func Cell_func;

    typedef struct {
        int col_name;
        int row_num;
        int value; 
        int valid; 
        Cell_func *func;    
    } Cell;

    struct Cell_func {
        Cell* Cell1;
        Cell* Cell2;
        ops op;
        int fix_val;
    };
        
    void evaluate(Cell** data, Cell *cell, int R ,int C);



#endif