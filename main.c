//gcc -g main.c linkedlist.c AVL.c stack.c hash_table.c evaluate_operations.c IO.c -o sheet.exe
// gdb sheet.exe


#include<stdlib.h>
#include<stdio.h>
// #include<stdbool.h>
#include"data_structures.h"
#include<time.h>

// void parse_input(char* inp, struct parsedInput* parsed_out, int R, int C, int* errPos);
/*
Create Data Structure
Take input



*/
// void parse_input(char* inp, struct parsedInput* parsed_out, int R, int C, int* errPos);


int main(int argc, char* argv[])
{
    FILE* output = fopen("output.txt", "a");
    if (argc != 3){
        fprintf(output, "ERROR: Input should be of the form  > executable_name.exe [num_cols] [num_rows]\n");
        return 0;
    }

    bool displayOn = true;
    int displayR = 1;
    int displayC = 1;
    bool lastValid = true;
    char errorText[50] = "";
    time_t lastTime = 0;
    bool quit = false;
    // int* errPos=malloc(sizeof(int));
    // *errPos = 0;
    int R, C;
    // scanf("%u", &R);
    // scanf("%u", &C);
    // scanf("%c", &dummy);
    R = atoi(argv[argc-2]);
    C = atoi(argv[argc-1]);

    
    if (R < 1 || R > 999) {
        fprintf(output, "ERROR: Row must be between 1 and 999\n");
        return 0;
    }
    if (C < 1 || C > 18278) {
        fprintf(output, "ERROR: Col must be between 1 and 18278\n");
        return 0;
    }

    Cell** data = (Cell**) calloc(R*C, sizeof(Cell*));



    while (!(quit))
    {

        if (displayOn) display_window(data, displayR, displayC, R, C);
        

        if (lastValid)
        {
            fprintf(output, "[%lld.0] (ok) > \n", (long long int)lastTime);
        }
        else
        {
            fprintf(output, "[%lld.0] (skill issue: %s) > \n", (long long int)lastTime, errorText);
            break;
            
        }
        
        
        char inp[30] = "";
        // fgets(inp, 30, stdin);
        // printf("\nInput#%s#end\n", inp);


        int i = 0;
        int c;
        while ((c = getchar()) != -1 && c != '\n' && c != '\0' && i < 30) // -1 is End Of File (EOF)
        {
            inp[i] = c;
            // printf("%c", c);
            i++;
        }
    
        time_t start_time;
        time(&start_time);



        struct parsedInput parse = {0, 0, 0,0,0,0, 0,0,0,0, 0,0};
        fprintf(output, "\n%s\n", inp);
        parse_input(&inp[0], &parse, R, C);

        if (parse.inpType == Invalid)
        {
            lastValid = false;
            switch (parse.val1Int)
            {
                case 0: 
                sprintf(errorText, "Invalid syntax at pos %d", parse.val2Int);
                break;
                case 1: 
                sprintf(errorText, "Addr out of range at pos %d", parse.val2Int);
                break;
                case 2: 
                sprintf(errorText, "Range End is lesser than Range Start at pos %d", parse.val2Int);
                break;
                default:
                break;
            }
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
                    displayR = max(min(R - windowHeight + 1, displayR + 10), 1);
                    break;
                    case 3:
                    displayC = max(min(C - windowWidth + 1, displayC + 10), 1);
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
                default:
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

                if (parse.operation>5){
                    for (int i = parse.val1Row; i <= parse.val2Row; i++)
                    {
                        for (int j = parse.val1Col; j <= parse.val2Col; j++)
                        {
                            Cell* val = *(data + C*(i-1) + j - 1);
                            if (val == NULL)
                            {
                                //Initialise val1
            
                                val = (Cell*)  malloc(sizeof(Cell));
                                *(data + C*(i-1) + j - 1) = val;
                                val -> col_name = j;
                                val -> row_num = i;
                                val -> value = 0;
                                val -> valid = true;
                                val -> children = (AVL* ) malloc(sizeof(AVL));
                                val -> children -> root = NULL;
                                // Cell_func* val_func = NULL;
                                val->func = NULL;
                            }
                        }
                        
                    }
                    
                }
                /* else */ {
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
                            // Cell_func* val1_func = NULL;
                            val1->func = NULL;
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
                            // Cell_func* val2_func = NULL;
                            val2->func = NULL;
                        }
                        new_func -> Cell2 = val2;
                    }
                }

                target -> func = new_func;
                int x=evaluate(data, target, old_func, R, C);

                if (x==0)
                {
                    lastValid = false;
                    sprintf(errorText, "Loop detected, all chagnes reverted");
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
        time(&lastTime);
        lastTime-=start_time;
        // lastTime = (float)time(NULL) - start_time;
        // printf("%f\n", start_time);
    }
    
    // free(errPos);
    Cell** temp=data;
    for (int i = 0; i < R*C; i++)
    {
        if (*temp)
        {
            if((*temp)->children) {
                deleteTree((*temp)->children->root);
                free((*temp)->children);
            }
            if((*temp)->func) free((*temp)->func);
            free(*temp);
        }
        temp++;
    }
    free(data);
    // output.close();


}