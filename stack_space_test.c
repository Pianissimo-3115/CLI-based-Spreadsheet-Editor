#include <stdio.h>
#include <stdlib.h>

char* col_chars_from_int(int col)
{
    char* out = (char*) malloc(4*sizeof(char));
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

void create_excel_chain(const char* filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    
    // Loop from column 1 (A) to 18277 (ZZY)
    for (int j = 1; j <= 999; j++)
    {
        for (int col = 1; col < 18278; col++) {
            char* a= col_chars_from_int(col);
            char* b= col_chars_from_int(col+1);
            fprintf(file, "%s%d=%s%d+1\n", a,j,b,j);
        }
        if (j!=999)
        {
            fprintf(file, "ZZZ%d=A%d+1\n",j,j+1);
        }
        
    }
    fprintf(file, "enable_output\n");
    fprintf(file, "ZZZ999=1\n");
    fprintf(file, "faltu\n");
    

    
    
    fclose(file);
    printf("Output written to '%s' successfully!\n", filename);
}

int main() {
    create_excel_chain("input.txt");
    return 0;
}
