#ifndef ARABICA_PARSER_H
#define ARABICA_PARSER_H

#include <stdio.h>



void line_parsing(FILE* p_arabicaOutput, char* p_line, int* p_filesize);

void no_args_instructions(FILE* p_arabicaOutput, char* p_line, int* p_filesize);

void one_args_instructions(FILE* p_arabicaOutput, char* p_line, int* p_filesize);


#endif