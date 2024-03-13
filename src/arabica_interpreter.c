#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/arabica_interpreter.h"
#include "../include/arabica_instructions.h"
#include "../include/arabica_parser.h"


#define OUT_HEADER_NAME "CODE"



void main(int p_argc, char** p_args)
{
    if (p_argc != 2) {
        printf("Error: incorrect number of aguments");
        return;
    }
    char v_line[32];
    int* v_filesize = malloc(sizeof(int));
    
    FILE* v_arabicaInput = fopen(p_args[1], "r");
    FILE* v_arabicaOutput = fopen(OUT_HEADER_NAME, "wb");
    if (v_arabicaInput == NULL || v_arabicaOutput == NULL) {
        perror("Ciao");
        return;
    }

    // fwrite(&tmp, 1, 16, v_arabicaOutput);
    arabica_header(v_arabicaOutput, arabica_filename(p_args[1]));

    while (fgets(v_line, sizeof(v_line), v_arabicaInput)) {
        line_parsing(v_arabicaOutput, v_line, v_filesize);
    }

    int v_trueSize = inverseEndianess(*v_filesize);
    fseek(v_arabicaOutput, 4, 0);
    fwrite(&v_trueSize, 4, 1, v_arabicaOutput);

    fclose(v_arabicaInput);
    fclose(v_arabicaOutput);
    free(v_filesize);
    

    return;
}

void arabica_header(FILE* p_arabicaOutput, char* p_arabicaName) {
    int v_nullByte = 0x00;
    size_t v_filenameOffset = 16 - strlen(p_arabicaName); 
    
    fwrite(OUT_HEADER_NAME, 4, 1, p_arabicaOutput);
    fwrite(&v_nullByte, 4, 1, p_arabicaOutput);
    fwrite(p_arabicaName, strlen(p_arabicaName), 1, p_arabicaOutput);
    fwrite(&v_nullByte, 1, v_filenameOffset, p_arabicaOutput);
}

char* arabica_filename(char* p_inputName) {
    char* v_filenameParsed = strtok(p_inputName, ".");
    // printf("%s", v_filenameParsed);
    return v_filenameParsed;
}