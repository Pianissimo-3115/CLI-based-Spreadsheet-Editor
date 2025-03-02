#include<stdio.h>
#include<stdlib.h>
#include"cell_operations.h"


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


void col_chars_from_int(int col, char* out)
{
    out[3] = '\0';
    if (col <= 26)
    {
        out[2] = '\0';
        out[1] = '\0';
        out[0] = 'A' + col - 1;
    }
    else if (col <= 702) //26*26 + 26
    {
        out[2] = '\0';
        out[1] = 'A' + (col-1)%26;
        col = (col-1)/26;
        out[0] = 'A' + col - 1;
    }
    else if (col <= 18278) //26*26*26 + 26*26 + 26
    {
        out[2] = 'A' + (col-1)%26;
        col = (col-1)/26;
        out[1] = 'A' + (col-1)%26;
        col = (col-1)/26;
        out[0] = 'A' + col - 1;
    }
    //Wrong input
}



bool is_up_char(char ch)
{
    return ('Z' >= ch && ch >= 'A');
}

bool is_digit(char ch)
{
    return ('9' >= ch && ch >= '0');
}

/* ERRORS:
0 : Invalid input
1 : Address out of range
2 : Range is invalid (opposite order)
*/

void fetch_addr(char* instr, int* row_out, int* col_out, int* len_out)
{
    int row = 0;
    int col = 0;
    if (!is_up_char(instr[0]))
    {
        *len_out = 0;
        return;
    }
    //Get address column (max three characters)
    int i = 0;
    while (is_up_char(instr[i]) && i<3)
    {
        col = col*26 + instr[i] - 'A' + 1;
        i++;
    }

    if (!(is_digit(instr[i]))) //Column letters must be followed by a number
    {
        *len_out = -i;
        return;                  
    }

    //Get address row (max three characters)
    int j = 0;
    while (is_digit(instr[i+j]) && j<3)
    {
        row = row*10 + instr[i + j] - '0';
        j++;
    }
    *row_out = row;
    *col_out = col;
    *len_out = i + j;
    return;
}

void parse_input(char* inp, struct parsedInput* parsed_out, int R, int C)
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
    if (check_chars_equal(inp, checkgoto, 10))
    {
        parsed_out -> inpType = Display;
        parsed_out -> operation = SCROLL;
        
        int rangeStart = 10;

        int val1Col = 0;
        int val1Row = 0;
        int addrLen = 0;

        fetch_addr(inp+rangeStart, &val1Row, &val1Col, &addrLen);
        
        if (addrLen <= 0)
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 0; //Invalid syntax
            (*parsed_out).val2Int = rangeStart;
            return;
        }

        if (inp[rangeStart + addrLen] != '\0')
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 0; //Invalid syntax
            (*parsed_out).val2Int = rangeStart + addrLen;
            return;
        }

        if (val1Col > C || val1Row > R || val1Row <= 0)
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 1; //Address out of range
            (*parsed_out).val2Int = rangeStart;
            return;
        }

        parsed_out -> val1Type = 1;
        parsed_out -> val1Row = val1Row;
        parsed_out -> val1Col = val1Col;
        return;

    }
    

    if ( inp[1] == '\0' ) //Input has only one character => Must be movement
    {
        // printf("Only has one character.\n");
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
            (*parsed_out).val2Int = 0;
        } 
        return;
        
    }
    else if ( 'Z' >= inp[0] && 'A' <= inp[0]) //Input has more than one character => Must be an assignment
    {
        // printf("Has more than one character.\n");
        //Parse target address
        
        int targetCol = 0;
        int targetRow = 0;
        int addrLen = 0;

        fetch_addr(inp, &targetRow, &targetCol, &addrLen);

        if (addrLen <= 0)
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 0; //Invalid syntax
            (*parsed_out).val2Int = 0;
            return;
        }

        if (inp[addrLen] != '=') //Must be followed by an assignment operator
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 0; //Invalid syntax
            (*parsed_out).val2Int = addrLen;
            return;
        }

        if (targetCol > C || targetRow > R || targetRow <= 0) //Must be in range
        {
            parsed_out -> inpType = Invalid;
            parsed_out -> val1Int = 1; //Address out of range
            (*parsed_out).val2Int = 0;
            return;
        }
        //Target parsed successfully
        parsed_out->targetCol = targetCol;
        parsed_out->targetRow = targetRow;

        int exprStart = addrLen+1; //expression starts here

        //Check if it is a function
        int rangeStart;
        char checkMIN[4] = "MIN(";
        char checkMAX[4] = "MAX(";
        char checkAVG[4] = "AVG(";
        char checkSUM[4] = "SUM(";
        char checkSTDEV[6] = "STDEV(";
        char checkSLEEP[6] = "SLEEP(";
        bool isFunc=false;

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
            int val1Len = 0;

            if ('9' >= inp[rangeStart] && '0' <= inp[rangeStart]) //val1 is an integer
            {
                int val1Int = 0;
                int i = 0;
                while ('9' >= inp[rangeStart+i] && '0' <= inp[rangeStart+i])
                {
                    val1Int = val1Int*10 + inp[rangeStart+i] - '0';
                    i++;
                }
                val1Len = i;
                parsed_out -> val1Type = 0; 
                parsed_out -> val1Int = val1Int;
            }
            else if ('Z' >= inp[rangeStart] && 'A' <= inp[rangeStart]) //val1 is an address
            {

                int val1Col = 0;
                int val1Row = 0;

                fetch_addr(inp+rangeStart, &val1Row, &val1Col, &val1Len);

                if (val1Len <= 0)
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    (*parsed_out).val2Int = rangeStart;
                    return;
                }

                if (val1Col > C || val1Row > R || val1Row <= 0) //Must be within bounds
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 1; //Address out of range
                    (*parsed_out).val2Int = rangeStart;
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
                (*parsed_out).val2Int = rangeStart;
                return;
            }

            if (inp[rangeStart + val1Len] != ')')
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                (*parsed_out).val2Int = rangeStart + val1Len;
                return;
            }

            if (inp[rangeStart + val1Len + 1] != '\0')
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                (*parsed_out).val2Int = rangeStart + val1Len + 1;
                return;
            }

            parsed_out->inpType = Assignment;
            return;
            
        }

        if (isFunc) //It is a function => Parse Range
        {
            //Parse range start
            int val1Col = 0;
            int val1Row = 0;
            int val1Len = 0;
            
            fetch_addr(inp+rangeStart, &val1Row, &val1Col, &val1Len);

            if (val1Len <= 0)
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                (*parsed_out).val2Int = rangeStart;
                return;   
            }

            if (inp[rangeStart + val1Len] != ':')
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                (*parsed_out).val2Int = rangeStart + val1Len;
                return;
            }

            if (val1Col > C || val1Row > R || val1Row <= 0)
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 1; //Address out of range
                (*parsed_out).val2Int = rangeStart;
                return;
            }

            int rangeEnd = rangeStart + val1Len +1;

            //Parse range end
            int val2Col = 0;
            int val2Row = 0;
            int val2Len = 0;
            
            fetch_addr(inp+rangeEnd, &val2Row, &val2Col, &val2Len);

            if (val2Len <= 0)
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                (*parsed_out).val2Int = rangeEnd;
                return;
            }

            if (inp[rangeEnd + val2Len] != ')')
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                (*parsed_out).val2Int = rangeEnd + val2Len;
                return;
            }

            if (val2Col > C || val2Row > R || val2Row <= 0)
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 1; //Address out of range
                (*parsed_out).val2Int = rangeEnd;
                return;
            }

            if (val1Col > val2Col || val1Row > val2Row)
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 2; //Range is opposite;
                (*parsed_out).val2Int = rangeEnd;
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
            int val1Len = 0;
            bool isneg = false;
            if (inp[exprStart] == '-')
            {
                isneg = true;
                exprStart = exprStart + 1;
            }
            if ('9' >= inp[exprStart] && '0' <= inp[exprStart]) //val1 is an integer
            {
                int val1Int = 0;
                int i = 0;
                while ('9' >= inp[exprStart+i] && '0' <= inp[exprStart+i])
                {
                    val1Int = val1Int*10 + inp[exprStart+i] - '0';
                    i++;
                }
                if (isneg) val1Int = -val1Int;
                val1Len = i;
                parsed_out -> val1Type = 0; 
                parsed_out -> val1Int = val1Int;
            }
            else if ('Z' >= inp[exprStart] && 'A' <= inp[exprStart] && !isneg) //val1 is an address
            {

                
                int val1Col = 0;
                int val1Row = 0;

                fetch_addr(inp+exprStart, &val1Row, &val1Col, &val1Len);

                if (val1Len <= 0)
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    (*parsed_out).val2Int = exprStart;
                    return;
                }

                if (val1Col > C || val1Row > R || val1Row <= 0) //Must be within bounds
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 1; //Address out of range
                    (*parsed_out).val2Int = exprStart;
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
                (*parsed_out).val2Int = exprStart;
                return;
            }
            
            if (inp[exprStart + val1Len] == '\0') //If it does not have anything else (thus direct assignment)
            {
                parsed_out->inpType = Assignment;
                parsed_out -> operation = FIX;
                return;
            }
            
            else if (inp[exprStart + val1Len] == '+')
            {
                parsed_out->inpType = Assignment;
                parsed_out -> operation = ADD;
            }
            else if (inp[exprStart + val1Len] == '-')
            {
                parsed_out->inpType = Assignment;
                parsed_out -> operation = SUB;
            }
            else if (inp[exprStart + val1Len] == '*')
            {
                parsed_out->inpType = Assignment;
                parsed_out -> operation = MUL;
            }
            else if (inp[exprStart + val1Len] == '/')
            {
                parsed_out->inpType = Assignment;
                parsed_out -> operation = DIV;
            }
            else
            {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    (*parsed_out).val2Int = exprStart + val1Len;
                    return;      
            }
            
            //Get val 2
            int exprSecond = exprStart + val1Len + 1;
            int val2Len = 0;
            isneg = false;
            if (inp[exprSecond] == '-')
            {
                isneg = true;
                exprSecond = exprSecond + 1;
            }
            if ('9' >= inp[exprSecond] && '0' <= inp[exprSecond]) //val2 is an integer
            {
                int val2Int = 0;
                int i = 0;
                
                while ('9' >= inp[exprSecond+i] && '0' <= inp[exprSecond+i])
                {
                    val2Int = val2Int*10 + inp[exprSecond+i] - '0';
                    i++;
                }
                if (isneg) val2Int = -val2Int;
                val2Len = i;
                parsed_out -> val2Type = 0; 
                parsed_out -> val2Int = val2Int;
            }
            else if ('Z' >= inp[exprSecond] && 'A' <= inp[exprSecond] && !isneg) //val2 is an address
            {

                int val2Col = 0;
                int val2Row = 0;

                fetch_addr(inp+exprSecond, &val2Row, &val2Col, &val2Len);

                if (val2Len <= 0)
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; //Invalid syntax
                    (*parsed_out).val2Int = exprSecond;
                    return;
                }

                if (val2Col > C || val2Row > R || val2Row <= 0) //Must be within bounds
                {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 1; //Address out of range
                    (*parsed_out).val2Int = exprSecond;
                    return;
                }
                
                parsed_out -> val2Type = 1;
                parsed_out -> val2Col = val2Col;
                parsed_out -> val2Row = val2Row;
                
            }
            else //It was an assignment but followup was not correct
            {
                parsed_out -> inpType = Invalid;
                parsed_out -> val1Int = 0; //Invalid syntax
                (*parsed_out).val2Int = exprSecond;
                return;
            }


            if (inp[exprSecond + val2Len] != '\0')
            {
                    parsed_out -> inpType = Invalid;
                    parsed_out -> val1Int = 0; // Wrong Syntax
                    (*parsed_out).val2Int = exprSecond + val2Len;
                    return;
            }

            return;

        }
        
    }
    else //Input had more than one character and first character was not alphabet (beginning of address) => Invalid
    {
            (*parsed_out).inpType = Invalid;
            (*parsed_out).val1Int = 0; //Invalid syntax
            (*parsed_out).val2Int = 0;
            return;
    }
    
    
}


void display_window(Cell** data, int currR, int currC, int R, int C)
{

    char colChars[4];
    printf("          ");
    for (int i = currC; i < currC + windowWidth && i <= C; i++)
    {
        col_chars_from_int(i, colChars);
        printf("%10s", colChars);

    }
    printf("\n");

    // Cell** runningPtr = data;
    for (int i = currR; i < currR + windowHeight && i <= R; i++)
    {
        printf("%10d", i);
        for (int j = currC; j < currC + windowWidth && j <= C; j++)
        {
            if (*(data + C*(i-1) + j - 1) == NULL)
            {
                printf("%10d", 0);
            }
            else
            {
                Cell cell = **(data + C*(i-1) + j - 1);
                if (cell.valid)
                {
                    printf("%10d", cell.value);
                }
                else {
                    printf("       ERR");
                }
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


// static int main()
// {

//     // unsigned int R, C;
//     // scanf("%u %u", &R, &C);
    
//     // Cell** data = calloc(R*C, sizeof(Cell*));

//     // display_window(data, 23, 23, R, C);

//     int R = 2000000;
//     int C = 200000;
//     char inp[30] = "";


//     // scanf("%s %s", inp, inp2);
//     int i = 0;
//     int c;
//     while ((c = getchar()) != EOF && c != '\n' && i < 30)
//     {
//         inp[i] = c;
//         // printf("%c", c);
//         i++;

//     }
    

//     int errPos = -1;
//     printf("%s\n", inp);
//     struct parsedInput parse = {0, 0, 0,0,0,0, 0,0,0,0, 0,0};
//     parse_input(inp, &parse, R, C, &errPos);
//     switch (parse.inpType)
//     {
//     case 0:
//         printf("Invalid\n");
//         break;
//     case 1:
//         printf("Movement\n");
//         break;
//     case 2:
//         printf("Assignment\n");
//         break;
//     default:
//         break;
//     }
//     // printf("%i\n", parse.inpType);

//     switch (parse.operation)
//     {
//     case 0:
//         printf("FIX\n");
//         break;
//     case 1:
//         printf("ADD\n");
//         break;
//     case 2:
//         printf("SUB\n");
//         break;
//     case 3:
//         printf("MUL\n");
//         break;
//     case 4:
//         printf("DIV\n");
//         break;  
//     case 5:
//         printf("MIN\n");
//         break;
//     case 6:
//         printf("MAX\n");
//         break;
//     case 7:
//         printf("STDEV\n");
//         break;
//     case 8:
//         printf("SUM\n");
//         break;
//     case 9:
//         printf("AVG\n");
//         break;
//     case 10:
//         printf("SLEEP\n");
//         break;
//     default:
//         break;
//     }

//     printf("val1Type %i\n", parse.val1Type);
//     printf("val1Col %i\n", parse.val1Col);
//     printf("val1Row %i\n", parse.val1Row);
//     printf("val1Int %i\n", parse.val1Int);
//  //
//     printf("val2Type %i\n", parse.val2Type);
//     printf("val2Col %i\n", parse.val2Col);
//     printf("val2Row %i\n", parse.val2Row);
//     printf("val2Int %i\n", parse.val2Int);

//     printf("targetCol %i\n", parse.targetCol);
//     printf("targetRow %i\n", parse.targetRow);
    
// }

// int main(){ return 0; }