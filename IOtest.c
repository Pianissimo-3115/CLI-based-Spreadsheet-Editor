#include "IO.c"

int main()
{
    FILE *file_ptr;
    file_ptr = fopen("IOtestcases.txt", "r");

    if (file_ptr == NULL)
    {
        printf("Test file could not be opened.");
        return 0;
    }

    char line[100];
    int errPos = 0;
    while (fgets(line, 100, file_ptr) != NULL)
    {
        if (line[0] != '#')
        {
            printf("%s", line);
            struct parsedInput parse = {0, 0, 0,0,0,0, 0,0,0,0, 0,0};
            parse_input(line, &parse, 999, 18000, &errPos);

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
    }

}