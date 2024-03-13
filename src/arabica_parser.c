#include <stdio.h>
#include <string.h>

#include "../include/arabica_parser.h"
#include "../include/arabica_instructions.h"



void line_parsing(FILE* p_arabicaOutput, char* p_line, int* p_filesize) {
    int v_nbWords = 0;
    for (int i= 0; i < strlen(p_line); i++) {
        if(p_line[i] == ' ') {
            v_nbWords++;
        }
    }

    if (v_nbWords == 0) {
        no_args_instructions(p_arabicaOutput, p_line, p_filesize);
    }
    else if (v_nbWords == 1) {
        one_args_instructions(p_arabicaOutput, p_line, p_filesize);
    }
    else {
        printf("Non-recognized instruction: %s\n", p_line);
    }
}

void no_args_instructions(FILE* p_arabicaOutput, char* p_line, int* p_filesize) {
    char v_operation[16];
    int v_instructionVal = 0;

    sscanf(p_line, "%s", v_operation);
    if (strcmp(v_operation, "ADD") == 0) v_instructionVal = 0x04;
    else if (strcmp(v_operation, "SUB") == 0) v_instructionVal = 0x05;
    else if (strcmp(v_operation, "MUL") == 0) v_instructionVal = 0x06;
    else if (strcmp(v_operation, "DIV") == 0) v_instructionVal = 0x07;
    else if (strcmp(v_operation, "MOD") == 0) v_instructionVal = 0x08;
    else if (strcmp(v_operation, "EQ") == 0) v_instructionVal = 0x0C;
    else if (strcmp(v_operation, "NEQ") == 0) v_instructionVal = 0x0D;
    else if (strcmp(v_operation, "GT") == 0) v_instructionVal = 0x0E;
    else if (strcmp(v_operation, "LT") == 0) v_instructionVal = 0x0F;
    else if (strcmp(v_operation, "GTE") == 0) v_instructionVal = 0x10;
    else if (strcmp(v_operation, "LTE") == 0) v_instructionVal = 0x11;
    else if (strcmp(v_operation, "PRINT_VAL") == 0) v_instructionVal = 0x12;
    else if (strcmp(v_operation, "INPUT_VAL") == 0) v_instructionVal = 0x13;
    else if (strcmp(v_operation, "HALT") == 0) v_instructionVal = 0x14;
    else if (strcmp(v_operation, "PRINT_STR") == 0) v_instructionVal = 0x16;
    else if (strcmp(v_operation, "INPUT_STR") == 0) v_instructionVal = 0x17;
    else if (strcmp(v_operation, "STR_LEN") == 0) v_instructionVal = 0x18;
    else printf("Non-recognized instruction: %s\n", p_line);

    fwrite(&v_instructionVal, 1, 1, p_arabicaOutput);
    (*p_filesize)++;
}

void one_args_instructions(FILE* p_arabicaOutput, char* p_line, int* p_filesize) {
    char v_operation[16];
    int v_value = 0;

    sscanf(p_line, "%s %d", v_operation, &v_value);
    if (strcmp(v_operation, "LOAD_VAL") == 0) {
        int v_loadVal = 0x01;
        signed_arg_instruction(p_arabicaOutput, v_loadVal, v_value);
        (*p_filesize) += 5;
    }
    else if (strcmp(v_operation, "READ_VAR") == 0) {
        int v_readVar = 0x02;
        unsigned_arg_instruction(p_arabicaOutput, v_readVar, v_value);
        (*p_filesize) += 2;
    }
    else if (strcmp(v_operation, "STORE_VAR") == 0) {
        int v_storeVar = 0x03;
        unsigned_arg_instruction(p_arabicaOutput, v_storeVar, v_value);
        (*p_filesize) += 2;
    }
    else if (strcmp(v_operation, "JMP") == 0) {
        int v_jmp = 0x09;
        signed_arg_instruction(p_arabicaOutput, v_jmp, v_value);
        (*p_filesize) += 5;
    }
    else if (strcmp(v_operation, "JMP_IF_ZERO") == 0) {
        int v_jmpIfZero = 0x0A;
        signed_arg_instruction(p_arabicaOutput, v_jmpIfZero, v_value);
        (*p_filesize) += 5;
    }
    else if (strcmp(v_operation, "JMP_IF_TRUE") == 0) {
        int v_jmpIfTrue = 0x0B;
        signed_arg_instruction(p_arabicaOutput, v_jmpIfTrue, v_value);
        (*p_filesize) += 5;
    } 
    else if (strcmp(v_operation, "LOAD_STR") == 0) {
        load_str(p_arabicaOutput, p_line, p_filesize);
    } 
    else printf("Non-recognized instruction: %s\n", p_line);
}