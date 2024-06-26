#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/arabica_interpreter.h"
#include "../include/arabica_instructions.h"
#include "../include/arabica_parser.h"

#define OUT_HEADER_NAME "CODE"

int main(int p_argc, char **p_args)
{
    if (p_argc != 2)
    {
        printf("Error: incorrect number of arguments");
        return 1;
    }
    char v_line[32];
    int *v_filesize = malloc(sizeof(int));

    FILE *v_arabicaInput = fopen(p_args[1], "r");
    FILE *v_arabicaOutput = fopen(OUT_HEADER_NAME, "wb");
    if (v_arabicaInput == NULL || v_arabicaOutput == NULL)
    {
        perror("FileDirectoryError:");
        return 1;
    }

    arabica_header(v_arabicaOutput, arabica_filename(p_args[1]));

    while (fgets(v_line, sizeof(v_line), v_arabicaInput))
    {
        line_parsing(v_arabicaOutput, v_line, v_filesize);
    }

    int v_trueSize = inverseEndianess(*v_filesize);
    fseek(v_arabicaOutput, 4, 0);
    fwrite(&v_trueSize, 4, 1, v_arabicaOutput);

    fclose(v_arabicaInput);
    fclose(v_arabicaOutput);
    free(v_filesize);

    return 0;
}

void arabica_header(FILE *p_arabicaOutput, char *p_arabicaName)
{
    int v_nullByte = 0x00;
    size_t v_arabicaLength = strlen(p_arabicaName);
    size_t v_filenameOffset = 16 - v_arabicaLength - 1;

    fwrite(OUT_HEADER_NAME, 4, 1, p_arabicaOutput);
    fwrite(&v_nullByte, 4, 1, p_arabicaOutput);
    fwrite(p_arabicaName, v_arabicaLength + 1, 1, p_arabicaOutput);

    for (size_t i = 0; i < v_filenameOffset; i++)
    {
        fwrite(&v_nullByte, 1, 1, p_arabicaOutput);
    }
}

char *arabica_filename(char *p_inputName)
{
    char *v_filenameParsed = strtok(p_inputName, ".");
    return v_filenameParsed;
}
