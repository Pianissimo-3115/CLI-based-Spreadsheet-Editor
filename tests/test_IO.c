#include "../cell_operations.h"
#include<stdio.h>
#include<string.h>



int main()
{
    printf("\n**IO Tester Started**\n");
    FILE *file_ptr;
    file_ptr = fopen("tests/IOtestcases.txt", "r");
    int R = 1000;
    int C = 19000;
    if (file_ptr == NULL)
    {
        printf("Test file could not be opened.\n");
        return 0;
    }

    char line[100];
    while (fgets(line, 100, file_ptr) != NULL)
    {
        if (line[0] != '#' && line[0] != '\n' && line[0] != '~') printf("\n> ");// else printf("\n");
        printf("%s", line);
        if (line[0] != '#' && line[0] != '\n' && line[0] != '~')
        {
            
            line[strcspn(line, "\n")] = 0;
            struct parsedInput parse = {0, 0, 0,0,0,0, 0,0,0,0, 0,0};
            parse_input(line, &parse, R, C);

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
                    printf("(%d, %d)\n", parse.val1Col, parse.val1Row);
                    break;
                    default:
                    printf("!!!!!!!!!!Unexpected parse\n");
                }
                break;
            default:
                printf("!!!!!!!!!!!Unexpected parse\n");
                break;
            }

        
        }
        else if (line[0] == '~')
        {
            if (line[1] == 'R')
            {
                int Rtemp = 0;
                int i = 0;
                while ('9' >= line[2+i] && '0' <= line[2+i])
                {
                    Rtemp = Rtemp*10 + line[2+i] - '0';
                    i++;
                }
                R = Rtemp;
                printf("Set R to %d\n", R);
            }
            else if (line[1] == 'C')
            {
                int Ctemp = 0;
                int i = 0;
                while ('9' >= line[2+i] && '0' <= line[2+i])
                {
                    Ctemp = Ctemp*10 + line[2+i] - '0';
                    i++;
                }
                C = Ctemp;
                printf("Set C to %d\n", C);

            }
        }
        
    }

}