#include<stdlib.h>
#include<stdio.h>
// #include<stdbool.h>
#include"cell_operations.h"
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
            default:
                break;
            }
        }

    }
    

    


}