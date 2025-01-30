#include "IO.c"
// #include<stdio.h>

// struct parsedInput;
// void parse_input(char* inp, struct parsedInput* parsed_out, int R, int C, int* errPos);

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
        if (line[0] != '#' && line[0] != '\n')
        {
            printf("\n> %s", line);
            line[strcspn(line, "\n")] = 0;
            struct parsedInput parse = {0, 0, 0,0,0,0, 0,0,0,0, 0,0};
            parse_input(line, &parse, 999, 18000, &errPos);

            switch (parse.inpType)
            {
            case 0:
                printf("Invalid with error code %d", parse.val1Int);
                switch (parse.val1Int)
                {
                    case 0:
                    printf(" (Invalid syntax)\n");
                    break;
                    case 1:
                    printf(" (Address out of range)\n");
                    break;
                    case 2:
                    printf(" (Range order opposite)\n");
                    break;
                }
                break;
            case 1:
                printf("Movement ");
                switch (parse.val1Int)
                {
                    case 0:
                    printf(" (w: Move up)\n");
                    break;
                    case 1:
                    printf(" (a: Move left)\n");
                    break;
                    case 2:
                    printf(" (s: Move down)\n");
                    break;
                    case 3:
                    printf(" (d: Move right)\n");
                    break;
                    case 4:
                    printf(" (q: Exit program)\n");
                    break;
                }
                break;
            case 2:
                printf("Assignment ");
                switch (parse.operation)
                {
                case 0:
                    printf("FIX ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d\n", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d)\n", parse.val1Col, parse.val1Row);
                    }
                    break;
                case ADD:
                    printf("ADD ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d, ", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d), ", parse.val1Col, parse.val1Row);
                    }
                    
                    if (parse.val2Type == 0)
                    {
                        printf("Val2: %d\n", parse.val2Int);
                    }
                    else
                    {
                        printf("Val2: (%d, %d)\n", parse.val2Col, parse.val2Row);
                    }

                    break;
                case SUB:
                    printf("SUB ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d, ", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d), ", parse.val1Col, parse.val1Row);
                    }
                    
                    if (parse.val2Type == 0)
                    {
                        printf("Val2: %d\n", parse.val2Int);
                    }
                    else
                    {
                        printf("Val2: (%d, %d)\n", parse.val2Col, parse.val2Row);
                    }
                    break;
                case MUL:
                    printf("MUL ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d, ", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d), ", parse.val1Col, parse.val1Row);
                    }
                    
                    if (parse.val2Type == 0)
                    {
                        printf("Val2: %d\n", parse.val2Int);
                    }
                    else
                    {
                        printf("Val2: (%d, %d)\n", parse.val2Col, parse.val2Row);
                    }
                    break;
                case DIV:
                    printf("DIV ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d, ", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d), ", parse.val1Col, parse.val1Row);
                    }
                    
                    if (parse.val2Type == 0)
                    {
                        printf("Val2: %d\n", parse.val2Int);
                    }
                    else
                    {
                        printf("Val2: (%d, %d)\n", parse.val2Col, parse.val2Row);
                    }
                    break;  
                case MIN:
                    printf("MIN ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d, ", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d), ", parse.val1Col, parse.val1Row);
                    }
                    
                    if (parse.val2Type == 0)
                    {
                        printf("Val2: %d\n", parse.val2Int);
                    }
                    else
                    {
                        printf("Val2: (%d, %d)\n", parse.val2Col, parse.val2Row);
                    }
                    break;
                case MAX:
                    printf("MAX ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d, ", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d), ", parse.val1Col, parse.val1Row);
                    }
                    
                    if (parse.val2Type == 0)
                    {
                        printf("Val2: %d\n", parse.val2Int);
                    }
                    else
                    {
                        printf("Val2: (%d, %d)\n", parse.val2Col, parse.val2Row);
                    }
                    break;
                case STDEV:
                    printf("STDEV ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d, ", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d), ", parse.val1Col, parse.val1Row);
                    }
                    
                    if (parse.val2Type == 0)
                    {
                        printf("Val2: %d\n", parse.val2Int);
                    }
                    else
                    {
                        printf("Val2: (%d, %d)\n", parse.val2Col, parse.val2Row);
                    }
                    break;
                case SUM:
                    printf("SUM ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d, ", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d), ", parse.val1Col, parse.val1Row);
                    }
                    
                    if (parse.val2Type == 0)
                    {
                        printf("Val2: %d\n", parse.val2Int);
                    }
                    else
                    {
                        printf("Val2: (%d, %d)\n", parse.val2Col, parse.val2Row);
                    }
                    break;
                case AVG:
                    printf("AVG ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d, ", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d), ", parse.val1Col, parse.val1Row);
                    }
                    
                    if (parse.val2Type == 0)
                    {
                        printf("Val2: %d\n", parse.val2Int);
                    }
                    else
                    {
                        printf("Val2: (%d, %d)\n", parse.val2Col, parse.val2Row);
                    }
                    break;
                case SLEEP:
                    printf("SLEEP ");
                    printf("Target: (%d, %d), ", parse.targetCol, parse.targetRow);
                    if (parse.val1Type == 0)
                    {
                        printf("Val1: %d\n", parse.val1Int);
                    }
                    else
                    {
                        printf("Val1: (%d, %d)\n", parse.val1Col, parse.val1Row);
                    }
                    break;
                default:
                    printf("Unexpected parse");
                    break;
                }
                break;
            case 3:
                printf("DISPLAY ");

                switch (parse.operation)
                {
                    case 11:
                    printf("Disable_out\n");
                    break;
                    case 12:
                    printf("Enable_out\n");
                    break;
                    case 13:
                    printf("scroll to ");
                    printf("(%d, %d)", parse.val1Col, parse.val1Row);
                    break;
                    default:
                    printf("Unexpected parse");
                }
                break;
            default:
                printf("Unexpected parse");
                break;
            }

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
        // //
        //     printf("val2Type %i\n\n", parse.val2Type);
        //     printf("val2Col %i\n\n", parse.val2Col);
        //     printf("val2Row %i\n\n", parse.val2Row);
        //     printf("val2Int %i\n\n", parse.val2Int);

        //     printf("targetCol %i\n", parse.targetCol);
        //     printf("targetRow %i\n", parse.targetRow);
        }
    }

}