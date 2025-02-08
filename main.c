
#include<stdio.h>
// #include<stdbool.h>
#include"cell_operations.h"
// void parse_input(char* inp, struct parsedInput* parsed_out, int R, int C, int* errPos);
/*
Create Data Structure
Take input



*/


int main()
{

    bool displayOn = true;

    unsigned int R, C;
    scanf("%u %u", &R, &C);

    Cell** data = (Cell**) calloc(R*C, sizeof(Cell*));


    
    char inp[30] = "";
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
    parse_input(inp, &parse, R, C, &errPos);


}