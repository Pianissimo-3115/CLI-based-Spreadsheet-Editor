//gcc -g main.c linkedlist.c AVL.c stack.c hash_table.c evaluate_operations.c IO.c -o sheet.exe
// gdb sheet.exe


#include<stdlib.h>
#include<stdio.h>
// #include<stdbool.h>
#include"data_structures.h"

// void parse_input(char* inp, struct parsedInput* parsed_out, int R, int C, int* errPos);
/*
Create Data Structure
Take input



*/
// void parse_input(char* inp, struct parsedInput* parsed_out, int R, int C, int* errPos);


int main()
{

    bool displayOn = true;
    int displayR = 1;
    int displayC = 1;
    bool lastValid = true;
    float lastTime = 0.0;
    bool quit = false;

    unsigned int R, C;
    char dummy;
    scanf("%u", &R);
    scanf("%u", &C);
    scanf("%c", &dummy);

    Cell** data = (Cell**) calloc(R*C, sizeof(Cell*));



    while (!(quit))
    {

        if (displayOn) display_window(data, displayR, displayC, R, C);
        

        if (lastValid)
        {
            printf("[%f] (ok) > ", lastTime);
        }
        else
        {
            printf("[%f] (skill issue) > ", lastTime);
            
        }
        
        
        char inp[30] = "";
        // fgets(inp, 30, stdin);
        // printf("\nInput#%s#end\n", inp);


        int i = 0;
        int c;
        while ((c = getchar()) != -1 && c != '\n' && i < 30) // -1 is End Of File (EOF)
        {
            inp[i] = c;
            // printf("%c", c);
            i++;
        }
    
        int errPos;
        struct parsedInput parse = {0, 0, 0,0,0,0, 0,0,0,0, 0,0};
        parse_input(&inp[0], &parse, R, C, &errPos);

        if (parse.inpType == Invalid)
        {
            lastValid = false;
        }
        else
        {
            lastValid = true;
            switch (parse.inpType)
            {
            case Movement:
                switch (parse.val1Int)
                {
                    case 0:
                    displayR = max(1, displayR - 10);
                    break;
                    case 1:
                    displayC = max(1, displayC - 10);
                    break;
                    case 2:
                    displayR = min(R, displayR + 10);
                    break;
                    case 3:
                    displayC = min(C, displayC + 10);
                    break;
                    case 4:
                    quit = true;
                    break;
                }
                break;
            case Display:
            switch (parse.operation)
            {
                case 11:
                displayOn = false;
                break;
                case 12:
                displayOn = true;
                break;
                case 13:
                displayC = parse.val1Col;
                displayR = parse.val1Row;
                break;
            }
            break;
            case Assignment:
                Cell* target = *(data + C*(parse.targetRow-1) + parse.targetCol - 1);
                Cell_func* old_func = NULL;
                Cell_func* new_func = NULL;
                if (target == NULL)
                {
                    target = (Cell*)  malloc(sizeof(Cell));
                    *(data + C*(parse.targetRow-1) + parse.targetCol - 1) = target;

                    target -> col_name = parse.targetCol;
                    target -> row_num = parse.targetRow;
                    target -> value = 0;
                    target -> valid = true;
                    target -> children = (AVL* ) malloc(sizeof(AVL));
                    target -> children -> root = NULL;
                    //target -> run_cnt = 0;
                }
                else
                {
                    old_func = target -> func;
                }
                
                new_func = malloc(sizeof(Cell_func));
                new_func -> op = parse.operation;

                if (parse.val1Type == 0)
                {
                    new_func -> flag1 = 0;
                    new_func -> value1 = parse.val1Int;
                }
                else
                {
                    new_func -> flag1 = 1;
                    Cell* val1 = *(data + C*(parse.val1Row-1) + parse.val1Col - 1);
                    if (val1 == NULL)
                    {
                        //Initialise val1
    
                        val1 = (Cell*)  malloc(sizeof(Cell));
                        *(data + C*(parse.val1Row-1) + parse.val1Col - 1) = val1;
                        val1 -> col_name = parse.val1Col;
                        val1 -> row_num = parse.val1Row;
                        val1 -> value = 0;
                        val1 -> valid = true;
                        val1 -> children = (AVL* ) malloc(sizeof(AVL));
                        val1 -> children -> root = NULL;
                        Cell_func* val1_func = NULL;
                        val1->func = val1_func;
                    }
                    new_func -> Cell1 = val1;
                }

                if (parse.val2Type == 0)
                {
                    new_func -> flag2 = 0;
                    new_func -> value2 = parse.val2Int;
                }
                else
                {
                    new_func -> flag2 = 1;
                    Cell* val2 = *(data + C*(parse.val2Row-1) + parse.val2Col - 1);
                    if (val2 == NULL)
                    {
                        //Initialise val2
    
                        val2 = (Cell*)  malloc(sizeof(Cell));
                        *(data + C*(parse.val2Row-1) + parse.val2Col - 1) = val2;
                        val2 -> col_name = parse.val2Col;
                        val2 -> row_num = parse.val2Row;
                        val2 -> value = 0;
                        val2 -> valid = true;
                        val2 -> children = (AVL* ) malloc(sizeof(AVL));
                        val2 -> children -> root = NULL;
                        Cell_func* val2_func = NULL;
                        val2->func = val2_func;
                    }
                    new_func -> Cell2 = val2;
                }

                target -> func = new_func;
                int x=evaluate(data, target, old_func, R, C);
                
                if (x==0)
                {
                    lastValid = false;
                }
                else
                {
                    lastValid = true;
                }


            break;
            default:
                break;
            }
        }

    }
    

    


}