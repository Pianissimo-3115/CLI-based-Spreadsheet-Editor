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

    bool val1Type;
    char val1Addr[6];
    int val1Int;

    bool val2Type;
    char val2Addr[6];
    int val2Int;

    char target[6];

};

void parse_input(char* inp, struct parsedInput* parsed_out) /*  Not Done/Temp  */
{


    if ( inp[1] == '\0' ) //Input has only one character
    {
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
    else if ( 'Z' >= inp[0] && 'A' <= inp[0])
    {
        char* currCharPtr = inp;
        char targetColChar[3] = inp[0];         // THIS CAUSES AN ERROR AND COULD NOT DEBUG CAUSE NOT SURE WHAT IT IS SUPPOSED TO DO
        int targetCol;
        int targetRow;
        int i = 1;
        while (i < 3)
        {
            if ('Z' >= inp[i] && 'A' <= inp[i])
            {
                targetColChar[i] = inp[i];
            }
            else if ('9' >= inp[i] && '0' <= inp[i])
            {
                break;
            }
            else
            {
                (*parsed_out).inpType = Invalid;
                (*parsed_out).val1Int = 0; //Invalid syntax
            }
        }
        targetRow = inp[i] - '0' + 1;
        int j = 1;
        while (j < 3)
        {

            if ('9' >= inp[i+j] && '0' <= inp[i+j])
            {
                targetRow = 10*targetRow + (inp[i+j] - '0' + 1);
            }
            else if (inp[i+j] == '=')
            {
                j--;
                break;
            }
            else
            {
                (*parsed_out).inpType = Invalid;
                (*parsed_out).val1Int = 0; //Invalid syntax
            }
        }
        //TODO From here

        
    }
    else
    {
            (*parsed_out).inpType = Invalid;
            (*parsed_out).val1Int = 0; //Invalid syntax
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

    unsigned int R, C;
    scanf("%u %u", &R, &C);
    
    Cell** data = calloc(R*C, sizeof(Cell*));

    display_window(data, 23, 23, R, C);
    
}