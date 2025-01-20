#include<stdio.h>
#include<stdlib.h>
#include "cell_operations.h"
#include<stdbool.h>
// #include<string.h>

// #define dtype struct cell
typedef enum {Invalid, Movement, Assignment} inputType;

// bool { true = 1, false = 0};

// struct addr /*  Not Done/Temp  */
// {
//     int col;
//     int row;
// };

// struct cell /*  Not Done/Temp  */
// {
//     struct addr address;
//     int val;
// };

// emptycell = (struct cell) {0,0};

void mainloop(int* data, int R, int C) /*  Not Done/Temp  */
{
    char cmd[50];
    scanf("%s", cmd);

}

bool check_chars_equal(char* str1, char* str2, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
    }
    return true;
    
} 

int row_int_from_chars(char* chars)
{
    int out = 0;
    for (int i = 0; i < 3; i++)
    {
        if (*(chars+i) != '\0')
        {
            out = out*10 + *(chars+i)-'0';
        }
    }
    return out;
}

int col_int_from_chars(char* chars)
{
    int out = 0;
    for (int i = 0; i < 3; i++)
    {
        if (*(chars+i) != '\0')
        {
            out = out*26 + *(chars+i)-'A'+1;
        }
    }
    return out;
}

void col_chars_from_int(int col, char* out)
{
    if (col <= 26)
    {
        out[2] = '\0';
        out[1] = '\0';
        out[0] = 'A' + col - 1;
    }
    else if (col <= 702) //26*26 + 26
    {
        out[2] = '\0';
        out[1] = 'A' + col%26 - 1;
        col/=26;
        out[0] = 'A' + col - 1;
    }
    else if (col <= 18278) //26*26*26 + 26*26 + 26
    {
        out[2] = 'A' + col%26 - 1;
        col/=26;
        out[1] = 'A' + col%26 - 1;
        col/=26;
        out[0] = 'A' + col - 1;
    }
    //Wrong input
}

struct parsedInput
{
    inputType inpType;

    ops operation;

    bool val1Type; // 1 if address, 0 if int
    int val1Col;
    int val1Row;
    int val1Int;
    // char val1Addr[6];

    bool val2Type;
    int val2Col;
    int val2Row;
    int val2Int;
    // char val2Addr[6];

    int targetCol;
    int targetRow;
    // char target[6];

};

/* ERRORS:
0 : Invalid input
1 : Address out of range
2 : Range is invalid (opposite order)
*/


void parse_input(char* inp, struct parsedInput* parsed_out, int R, int C) /*  Not Done/Temp  */
{


    if ( inp[1] == '\0' ) //Input has only one character => Must be movement
    {
        printf("Only has one character.\n");
        if ( inp[0] == 'w' )
        {
            (*parsed_out).inpType = Movement;
            (*parsed_out).val1Int = 0;
        }
        else if ( inp[0] == 'a' )
        {
            (*parsed_out).inpType = Movement;
            (*parsed_out).val1Int = 1;
        }
        else if ( inp[0] == 's' )
        {
            (*parsed_out).inpType = Movement;
            (*parsed_out).val1Int = 2;
        }
        else if ( inp[0] == 'd' )
        {
            (*parsed_out).inpType = Movement;
            (*parsed_out).val1Int = 3;
        }
        else
        {
            (*parsed_out).inpType = Invalid;
            (*parsed_out).val1Int = 0; //Invalid syntax
        }
        return;
        
    }
    else if ( 'Z' >= inp[0] && 'A' <= inp[0]) //Input has more than one character => Must be an assignment
    {
        printf("Has more than one character.\n");
        //Parse target address
        char* currCharPtr = inp;
        char targetColChar[3];
        int targetCol = inp[0] - 'A' + 1;
        int targetRow;

        //Parse target column
        int i = 1;
        while (i < 3)
        {
            if ('Z' >= inp[i] && 'A' <= inp[i])
            {
                targetCol = 26*targetCol + (inp[i] - 'A' + 1);
                i++;
            }
            else if ('9' >= inp[i] && '0' <= inp[i])
            {
                break;
            }
            else
            {
                (*parsed_out).inpType = Invalid;
                (*parsed_out).val1Int = 0; //Invalid syntax
                return;
            }
        }

        //Parse target row
        targetRow = inp[i] - '0';
        int j = 1;
        while (j < 3)
        {

            if ('9' >= inp[i+j] && '0' <= inp[i+j])
            {
                targetRow = 10*targetRow + (inp[i+j] - '0');
                j++;
            }
            else if (inp[i+j] == '=')
            {
                break;
            }
            else
            {
                (*parsed_out).inpType = Invalid;
                (*parsed_out).val1Int = 0; //Invalid syntax
                return;
            }
        }

        if (inp[i+j] != '=') //Must be followed by an assignment operator
        {
            (*parsed_out).inpType = Invalid;
            (*parsed_out).val1Int = 0; //Invalid syntax
            return;
        }

        if (targetCol > C || targetRow > R) //Must be in range
        {
            (*parsed_out).inpType = Invalid;
            (*parsed_out).val1Int = 1; //Address out of range
            return;
        }

        // printf("targetCol.\n");


        //Target parsed successfully
        parsed_out->targetCol = targetCol;
        parsed_out->targetRow = targetRow;

        int exprStart = i+j+1; //expression starts here

        //Check if it is a function
        int rangeStart;
        char checkMIN[4] = "MIN(";
        char checkMAX[4] = "MAX(";
        char checkAVG[4] = "AVG(";
        char checkSUM[4] = "SUM(";
        char checkSTDEV[6] = "STDEV(";
        char checkSLEEP[6] = "SLEEP(";
        bool isFunc;

        if (check_chars_equal(inp + exprStart, checkMIN, 4))
        {
            isFunc = true;
            parsed_out -> operation = MIN;
            rangeStart = exprStart + 4;
        }
        else if (check_chars_equal(inp + exprStart, checkMAX, 4))
        {
            isFunc = true;
            parsed_out -> operation = MAX;
            rangeStart = exprStart + 4;

        }
        else if (check_chars_equal(inp + exprStart, checkAVG, 4))
        {
            isFunc = true;
            parsed_out -> operation = AVG;
            rangeStart = exprStart + 4;

        }
        else if (check_chars_equal(inp + exprStart, checkSUM, 4))
        {
            isFunc = true;
            parsed_out -> operation = SUM;
            rangeStart = exprStart + 4;

        }
        else if (check_chars_equal(inp + exprStart, checkSTDEV, 6))
        {
            isFunc = true;
            parsed_out -> operation = STDEV;
            rangeStart = exprStart + 6;

        }
        else if (check_chars_equal(inp + exprStart, checkSLEEP, 6))
        {
            isFunc = true;
            parsed_out -> operation = SLEEP;
            rangeStart = exprStart + 6;

        }

        if (isFunc) //It is a function => Parse Range
        {
            //Parse range start
            int val1Col = 0;
            int val1Row = 0;
            int i = 0;
            while (i < 3)
            {
                if ('Z' >= inp[rangeStart + i] && 'A' <= inp[rangeStart + i])
                {
                    val1Col = 26*val1Col + (inp[rangeStart + i] - 'A' + 1);
                    i++;
                }
                else if ('9' >= inp[rangeStart + i] && '0' <= inp[rangeStart + i])
                {
                    if (i == 0)
                    {
                        (*parsed_out).inpType = Invalid;
                        (*parsed_out).val1Int = 0; //Invalid syntax
                        return;
                    }
                    break;
                }
                else
                {
                    (*parsed_out).inpType = Invalid;
                    (*parsed_out).val1Int = 0; //Invalid syntax
                    return;
                }
            }

            val1Row = inp[rangeStart + i] - '0';
            int j = 1;
            while (j < 3)
            {

                if ('9' >= inp[rangeStart + i+j] && '0' <= inp[rangeStart + i+j])
                {
                    val1Row = 10*val1Row + (inp[rangeStart + i+j] - '0');
                    j++;
                }
                else if (inp[rangeStart + i+j] == ':')
                {
                    break;
                }
                else
                {
                    (*parsed_out).inpType = Invalid;
                    (*parsed_out).val1Int = 0; //Invalid syntax
                    return;
                }
            }


            if (inp[rangeStart + i+j] != ':')
            {
                (*parsed_out).inpType = Invalid;
                (*parsed_out).val1Int = 0; //Invalid syntax
                return;
            }

            if (val1Col > C || val1Row > R)
            {
                (*parsed_out).inpType = Invalid;
                (*parsed_out).val1Int = 1; //Address out of range
                return;
            }

            int rangeEnd = rangeStart + i+j+1;

            //Parse range end
            int val2Col = 0;
            int val2Row = 0;
            i = 0;
            while (i < 3)
            {
                if ('Z' >= inp[rangeEnd + i] && 'A' <= inp[rangeEnd + i])
                {
                    val2Col = 26*val2Col + (inp[rangeEnd + i] - 'A' + 1);
                    i++;
                }
                else if ('9' >= inp[rangeEnd + i] && '0' <= inp[rangeEnd + i])
                {
                    if (i == 0)
                    {
                        (*parsed_out).inpType = Invalid;
                        (*parsed_out).val1Int = 0; //Invalid syntax
                        return;
                    }
                    break;
                }
                else
                {
                    (*parsed_out).inpType = Invalid;
                    (*parsed_out).val1Int = 0; //Invalid syntax
                    return;
                }
            }

            val2Row = inp[rangeEnd + i] - '0';
            j = 1;
            while (j < 3)
            {

                if ('9' >= inp[rangeEnd + i+j] && '0' <= inp[rangeEnd + i+j])
                {
                    val2Row = 10*val2Row + (inp[rangeEnd + i+j] - '0');
                    j++;
                }
                else if (inp[rangeEnd + i+j] == ')')
                {
                    break;
                }
                else
                {
                    (*parsed_out).inpType = Invalid;
                    (*parsed_out).val1Int = 0; //Invalid syntax
                    return;
                }

            }


            if (inp[rangeEnd + i+j] != ')')
            {
                (*parsed_out).inpType = Invalid;
                (*parsed_out).val1Int = 0; //Invalid syntax
                return;
            }

            if (val2Col > C || val2Row > R)
            {
                (*parsed_out).inpType = Invalid;
                (*parsed_out).val1Int = 1; //Address out of range
                return;
            }

            if (val1Col > val2Col || val1Row > val2Row)
            {
                (*parsed_out).inpType = Invalid;
                (*parsed_out).val1Int = 2; //Range is opposite;
                return;
            }

            parsed_out->inpType = Assignment;
            parsed_out->val1Type = true;
            parsed_out->val1Col = val1Col;
            parsed_out->val1Row = val1Row;
            parsed_out->val2Type = true;
            parsed_out->val2Col = val2Col;
            parsed_out->val2Row = val2Row;

        }
        else //It is not a function => Must be number or address
        {
            
        }

        

        
    }
    else //Input had more than one character and first character was not alphabet (beginning of address) => Invalid
    {
            (*parsed_out).inpType = Invalid;
            (*parsed_out).val1Int = 0; //Invalid syntax
            return;
    }
    

    // while (1)
    // {
    //     if ('Z' >= inp && inp >= 'A')
    //     {
    //         targetCol
    //     }
    // }
    
}


int display_window(Cell** data, int currR, int currC, int R, int C)
{

    char colChars[3];
    printf("          ");
    for (int i = currC; i < currC + windowWidth && i <= C; i++)
    {
        col_chars_from_int(i, colChars);
        printf("%10s", colChars);

    }
    printf("\n");

    Cell** runningPtr = data;
    for (int i = currR; i < currR + windowHeight && i <= R; i++)
    {
        printf("%10d", i);
        for (int j = currC; j < currC + windowWidth && i <= C; j++)
        {
            if (*(data + C*i + j - 1) == NULL)
            {
                printf("%10d", 0);
            }
            else
            {
                printf("%10d", (**(data + C*i + j - 1)).value);
            }
        }
        printf("\n");
        
    }
    
    // printf("done");
}

// struct addr addr_to_cell(char* addr, int addr_len, int R, int C)
// {
//     int col = 0;
//     int row = 0;
//     for (int i = 0; i < addr_len; i++)
//     {
//         char currchr = *addr;
//         if ((currchr >= 'A') && (currchr <= 'Z'))
//         {
//             col = 26*col + (currchr-'A'+1);
//         }
//         else if (currchr >= '0' && currchr<='1')
//         {
//             row = 10*row + (currchr-'0'+1);
//         }

//         addr++;
//     }
//     return (struct addr) {col, row};
// }


int main()
{

    // unsigned int R, C;
    // scanf("%u %u", &R, &C);
    
    // Cell** data = calloc(R*C, sizeof(Cell*));

    // display_window(data, 23, 23, R, C);

    int R = 50;
    int C = 50;
    char inp[30];

    scanf("%s", inp);
    struct parsedInput parse = {0, 0, 0,0,0,0, 0,0,0,0, 0,0};
    parse_input(inp, &parse, R, C);

    printf("%i\n", parse.inpType);

    printf("%i\n", parse.operation);

    printf("%i\n", parse.val1Type);
    printf("%i\n", parse.val1Col);
    printf("%i\n", parse.val1Row);
    printf("%i\n", parse.val1Int);

    printf("%i\n", parse.val2Type);
    printf("%i\n", parse.val2Col);
    printf("%i\n", parse.val2Row);
    printf("%i\n", parse.val2Int);

    printf("%i\n", parse.targetCol);
    printf("%i\n", parse.targetRow);
    
}