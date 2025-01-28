#include<stdio.h>
#include"stdlib.h"
#include "cell_operations.h"
#include<stdbool.h>
// #include<string.h>

// #define dtype struct cell
typedef enum inputType {Invalid, Movement, Assignment, Display} inputType;

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


void parse_input(char* inp, struct parsedInput* parsed_out, int R, int C, int* errPos) /*  Not Done/Temp  */
{

    char checkdisable[15] = "disable_output\0";
    char checkenable[14] = "enable_output\0";
    char checkgoto[10] = "scroll_to ";

    if (check_chars_equal(inp, checkdisable, 15))
    {
        parsed_out -> inpType = Display;
        parsed_out -> operation = DISABLE_OUT;
        return;
    }
    if (check_chars_equal(inp, checkenable, 14))
    {
        parsed_out -> inpType = Display;
        parsed_out -> operation = ENABLE_OUT;
        return;
    }
    if (check_chars_equal(inp, checkdisable, 10))
    {
        parsed_out -> inpType = Display;
        parsed_out -> operation = SCROLL;
        
        int rangeStart = 10;

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
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    return;
                }
                break;
            }
            else
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
            }
        }

        if (!('9' >= inp[rangeStart + i] && '0' <= inp[rangeStart + i]))
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 0; //Invalid syntax
            return;
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
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
            }
        }


        if (inp[rangeStart + i+j] != '\0')
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 0; //Invalid syntax
            return;
        }

        if (val1Col > C || val1Row > R || val1Row <= 0)
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 1; //Address out of range
            return;
        }

        return;

    }
    

    if ( inp[1] == '\0' ) //Input has only one character => Must be movement
    {
        printf("Only has one character.\n");
        if ( inp[0] == 'w' )
        {
            parsed_out -> inpType = Movement;
            parsed_out -> val1Int = 0;
        }
        else if ( inp[0] == 'a' )
        {
            parsed_out -> inpType = Movement;
            parsed_out -> val1Int = 1;
        }
        else if ( inp[0] == 's' )
        {
            parsed_out -> inpType = Movement;
            parsed_out -> val1Int = 2;
        }
        else if ( inp[0] == 'd' )
        {
            parsed_out -> inpType = Movement;
            parsed_out -> val1Int = 3;
        }
        else if ( inp[0] == 'q' ) //Quit
        {
            parsed_out -> inpType = Movement;
            parsed_out -> val1Int = 4;
        }
        else
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 0; //Invalid syntax
        } 
        return;
        
    }
    else if ( 'Z' >= inp[0] && 'A' <= inp[0]) //Input has more than one character => Must be an assignment
    {
        printf("Has more than one character.\n");
        //Parse target address
        
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
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
            }
        }

        if (!('9' >= inp[i] && '0' <= inp[i]))
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 0; //Invalid syntax
            return;
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
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
            }
        }

        if (inp[i+j] != '=') //Must be followed by an assignment operator
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 0; //Invalid syntax
            return;
        }


        if (targetCol > C || targetRow > R || targetRow <= 0) //Must be in range
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 1; //Address out of range
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
        else if (check_chars_equal(inp + exprStart, checkSLEEP, 6)) //Sleep does not take a range so has different logic
        {
            // isFunc = true;
            parsed_out -> operation = SLEEP;
            rangeStart = exprStart + 6;

            if ('9' >= inp[rangeStart] && '0' <= inp[rangeStart]) //val1 is an integer
            {
                int val1Int = 0;
                i = 0;
                j = 0;
                while ('9' >= inp[rangeStart+i] && '0' <= inp[rangeStart+i])
                {
                    val1Int = val1Int*10 + inp[rangeStart+i] - '0';
                    i++;
                }
                parsed_out -> val1Type = 0; 
                parsed_out -> val1Int = val1Int;
            }
            else if ('Z' >= inp[rangeStart] && 'A' <= inp[rangeStart]) //val1 is an address
            {

                //Get address column (max three characters)
                i = 0;
                int val1Col = 0;
                while ('Z' >= inp[rangeStart + i] && 'A' <= inp[rangeStart + i] && i<3)
                {
                    val1Col = val1Col*26 + inp[rangeStart + i] - 'A' + 1;
                    i++;
                }

                if (!('9' >= inp[rangeStart+i] && '0' <= inp[rangeStart+i])) //Column letters must be followed by a number
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    return;                    
                }

                //Get address row (max three characters)
                j = 0;
                int val1Row = 0;
                while ('9' >= inp[rangeStart + i + j] && '0' <= inp[rangeStart + i + j] && j<3)
                {
                    val1Row = val1Row*10 + inp[rangeStart + i + j] - '0';
                    j++;
                }

                if (val1Col > C || val1Row > R || val1Row <= 0) //Must be within bounds
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 1; //Address out of range
                    return;
                }
                
                parsed_out -> val1Type = 1;
                parsed_out -> val1Col = val1Col;
                parsed_out -> val1Row = val1Row;
                
            }
            else //Value is neither address nor value
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
            }

            if (inp[rangeStart + i + j] != ')')
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
            }

            if (inp[rangeStart + i + j + 1] != '\0')
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
            }

            return;
            
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
                        parsed_out -> inpType = Invalid;
                        parsed_out -> val1Int = 0; //Invalid syntax
                        return;
                    }
                    break;
                }
                else
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    return;
                }
            }

            if (!('9' >= inp[rangeStart + i] && '0' <= inp[rangeStart + i]))
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
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
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    return;
                }
            }


            if (inp[rangeStart + i+j] != ':')
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
            }

            if (val1Col > C || val1Row > R || val1Row <= 0)
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 1; //Address out of range
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
                        parsed_out -> inpType = Invalid;
                        parsed_out -> val1Int = 0; //Invalid syntax
                        return;
                    }
                    break;
                }
                else
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    return;
                }
            }

            if (!('9' >= inp[rangeEnd+i] && '0' <= inp[rangeEnd+i]))
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
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
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    return;
                }

            }


            if (inp[rangeEnd + i+j] != ')')
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
            }

            if (val2Col > C || val2Row > R || val2Row <= 0)
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 1; //Address out of range
                return;
            }

            if (val1Col > val2Col || val1Row > val2Row)
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 2; //Range is opposite;
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
            if ('9' >= inp[exprStart] && '0' <= inp[exprStart]) //val1 is an integer
            {
                int val1Int = 0;
                i = 0;
                j = 0;
                while ('9' >= inp[exprStart+i] && '0' <= inp[exprStart+i])
                {
                    val1Int = val1Int*10 + inp[exprStart+i] - '0';
                    i++;
                }
                parsed_out -> val1Type = 0; 
                parsed_out -> val1Int = val1Int;
            }
            else if ('Z' >= inp[exprStart] && 'A' <= inp[exprStart]) //val1 is an address
            {

                //Get address column (max three characters)
                i = 0;
                int val1Col = 0;
                while ('Z' >= inp[exprStart + i] && 'A' <= inp[exprStart + i] && i<3)
                {
                    val1Col = val1Col*26 + inp[exprStart + i] - 'A' + 1;
                    i++;
                }

                if (!('9' >= inp[exprStart+i] && '0' <= inp[exprStart+i])) //Column letters must be followed by a number
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    return;                    
                }

                //Get address row (max three characters)
                j = 0;
                int val1Row = 0;
                while ('9' >= inp[exprStart + i + j] && '0' <= inp[exprStart + i + j] && j<3)
                {
                    val1Row = val1Row*10 + inp[exprStart + i + j] - '0';
                    j++;
                }

                if (val1Col > C || val1Row > R || val1Row <= 0) //Must be within bounds
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 1; //Address out of range
                    return;
                }
                
                parsed_out -> val1Type = 1;
                parsed_out -> val1Col = val1Col;
                parsed_out -> val1Row = val1Row;
                
            }
            else //It was an assignment but followup was not correct
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                return;
            }
            
            if (inp[exprStart + i + j] == '\0') //If it does not have anything else (thus direct assignment)
            {
                parsed_out->inpType = Assignment;
                parsed_out -> operation = FIX;

                return;
            }
            
            else if (inp[exprStart + i + j] == '+')
            {
                parsed_out->inpType = Assignment;
                parsed_out -> operation = ADD;
            }
            else if (inp[exprStart + i + j] == '-')
            {
                parsed_out->inpType = Assignment;
                parsed_out -> operation = SUB;
            }
            else if (inp[exprStart + i + j] == '*')
            {
                parsed_out->inpType = Assignment;
                parsed_out -> operation = MUL;
            }
            else if (inp[exprStart + i + j] == '/')
            {
                parsed_out->inpType = Assignment;
                parsed_out -> operation = DIV;
            }
            else
            {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    return;      
            }
            
            //Get val 2
            int exprSecond = exprStart + i + j + 1;

            if ('9' >= inp[exprSecond] && '0' <= inp[exprSecond]) //val2 is an integer
            {
                int val2Int = 0;
                i = 0;
                j = 0;
                while ('9' >= inp[exprSecond+i] && '0' <= inp[exprSecond+i])
                {
                    val2Int = val2Int*10 + inp[exprSecond+i] - '0';
                    i++;
                }
                parsed_out -> val2Type = 0; 
                parsed_out -> val2Int = val2Int;
            }
            else if ('Z' >= inp[exprSecond] && 'A' <= inp[exprSecond]) //val2 is an address
            {

                //Get address column (max three characters)
                i = 0;
                int val2Col = 0;
                while ('Z' >= inp[exprSecond + i] && 'A' <= inp[exprSecond + i] && i<3)
                {
                    val2Col = val2Col*26 + inp[exprSecond + i] - 'A' + 1;
                    i++;
                }

                if (!('9' >= inp[exprSecond+i] && '0' <= inp[exprSecond+i])) //Column letters must be followed by a number
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    return;                    
                }

                //Get address row (max three characters)
                j = 0;
                int val2Row = 0;
                while ('9' >= inp[exprSecond + i + j] && '0' <= inp[exprSecond + i + j] && j<3)
                {
                    val2Row = val2Row*10 + inp[exprSecond + i + j] - '0';
                    j++;
                }

                if (val2Col > C || val2Row > R || val2Row <= 0) //Must be within bounds
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 1; //Address out of range
                    return;
                }
                
                parsed_out -> val2Type = 1;
                parsed_out -> val2Col = val2Col;
                parsed_out -> val2Row = val2Row;
                
            }

            if (inp[exprSecond + i + j] != '\0')
            {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; // Wrong Syntax
                    return;
            }

            return;

        }


        
    }
    else //Input had more than one character and first character was not alphabet (beginning of address) => Invalid
    {
            (*parsed_out).inpType = Invalid;
            (*parsed_out).val1Int = 0; //Invalid syntax
            return;
    }
    
    
}


void display_window(Cell** data, int currR, int currC, int R, int C)
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

    int R = 2000000;
    int C = 200000;
    char inp[30] = "";


    // scanf("%s %s", inp, inp2);
    int i = 0;
    int c;
    while ((c = getchar()) != EOF && c != '\n' && i < 30)
    {
        inp[i] = c;
        // printf("%c", c);
        i++;

    }
    

    int errPos = -1;
    printf("%s\n", inp);
    struct parsedInput parse = {0, 0, 0,0,0,0, 0,0,0,0, 0,0};
    parse_input(inp, &parse, R, C, &errPos);
    switch (parse.inpType)
    {
    case 0:
        printf("Invalid\n");
        break;
    case 1:
        printf("Movement\n");
        break;
    case 2:
        printf("Assignment\n");
        break;
    default:
        break;
    }
    // printf("%i\n", parse.inpType);

    switch (parse.operation)
    {
    case 0:
        printf("FIX\n");
        break;
    case 1:
        printf("ADD\n");
        break;
    case 2:
        printf("SUB\n");
        break;
    case 3:
        printf("MUL\n");
        break;
    case 4:
        printf("DIV\n");
        break;  
    case 5:
        printf("MIN\n");
        break;
    case 6:
        printf("MAX\n");
        break;
    case 7:
        printf("STDEV\n");
        break;
    case 8:
        printf("SUM\n");
        break;
    case 9:
        printf("AVG\n");
        break;
    case 10:
        printf("SLEEP\n");
        break;
    default:
        break;
    }

    printf("val1Type %i\n", parse.val1Type);
    printf("val1Col %i\n", parse.val1Col);
    printf("val1Row %i\n", parse.val1Row);
    printf("val1Int %i\n", parse.val1Int);
 //
    printf("val2Type %i\n", parse.val2Type);
    printf("val2Col %i\n", parse.val2Col);
    printf("val2Row %i\n", parse.val2Row);
    printf("val2Int %i\n", parse.val2Int);

    printf("targetCol %i\n", parse.targetCol);
    printf("targetRow %i\n", parse.targetRow);
    
}