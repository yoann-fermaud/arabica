#ifndef ARABICA_INSTRUCTIONS_H
#define ARABICA_INSTRUCTIONS_H

#include <stdio.h>



// void load_val(FILE* p_arabicaOutput, int p_args);

// void read_var(FILE* p_arabicaOutput, int p_args);

// void store_var(FILE* p_arabicaOutput, int p_args);

// void jmp(FILE* p_arabicaOutput, int p_args);

// void jmp_if_zero(FILE* p_arabicaOutput, int p_args);

// void jmp_if_true(FILE* p_arabicaOutput, int p_args);

void unsigned_arg_instruction(FILE* p_arabicaOutput, int p_instructionValue, int p_args);

void signed_arg_instruction(FILE* p_arabicaOutput, int p_instructionValue, int p_args);

void load_str(FILE* p_arabicaOutput, char* p_line, int* p_filesize);

unsigned int inverseEndianess(unsigned int value);


#endif