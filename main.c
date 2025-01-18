#include<stdio.h>
// #include<string.h>

#define dtype struct cell
#define windowWidth 10
#define windowHeight 10

enum inputType {Invalid, Movement, Const, Expression};

struct addr /*  Not Done/Temp  */
{
    int col;
    int row;
};

struct cell /*  Not Done/Temp  */
{
    struct addr address;
    int val;
};

// emptycell = (struct cell) {0,0};

static void mainloop(int* data, int R, int C) /*  Not Done/Temp  */
{
    char cmd[50];
    scanf("%s", cmd);

}

static int row_int_from_chars(char* chars)
{
    int out = 0;
    for (int i = 0; i < 3; i++)
    {
        if (*(chars+i) != '\0')
        {
            out = out*10 + *(chars+i)-'0'+1;
        }
    }
    return out;
}

static int col_int_from_chars(char* chars)
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

static void col_chars_from_int(int col, char* out)
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


static void parse_input(char* inp, enum inputType* inpType_out) /*  Not Done/Temp  */
{
    char targetCol[3];
    char targetRow[3];
    if ( *inp == 'w' )
    {
        
    }
    else if ( *inp == 'a' )
    {
        
    }
    else if ( *inp == 's' )
    {
        
    }
    else if ( *inp == 'd' )
    {

    }

    // while (1)
    // {
    //     if ('Z' >= inp && inp >= 'A')
    //     {
    //         targetCol
    //     }
    // }
    
}


static int display_window(dtype** data, int currR, int currC, int R, int C)
{

    char colChars[3];
    printf("          ");
    for (int i = currC; i < currC + windowWidth && i <= C; i++)
    {
        col_chars_from_int(i, colChars);
        printf("%10s", colChars);

    }
    printf("\n");

    dtype** runningPtr = data;
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
                printf("%10d", (**(data + C*i + j - 1)).val);
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
    
    dtype** data = calloc(R*C, sizeof(dtype*));
    dtype** dataptr = data;

    display_window(data, 23, 23, R, C);
    
}