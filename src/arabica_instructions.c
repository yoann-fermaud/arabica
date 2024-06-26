#include <stdio.h>
#include <string.h>

#include "../include/arabica_instructions.h"
#include "../include/utilities.h"

void unsigned_arg_instruction(FILE *p_arabicaOutput, int p_instructionValue, int p_args)
{
    unsigned int v_argValue = inverseEndianess(p_args);
    fwrite(&p_instructionValue, 1, 1, p_arabicaOutput);
    fwrite(&v_argValue, 1, 1, p_arabicaOutput);
}

void signed_arg_instruction(FILE *p_arabicaOutput, int p_instructionValue, int p_args)
{
    int v_argValue = inverseEndianess(p_args);
    fwrite(&p_instructionValue, 1, 1, p_arabicaOutput);
    fwrite(&v_argValue, sizeof(int), 1, p_arabicaOutput);
}

void load_str(FILE *p_arabicaOutput, char *p_line, int *p_filesize)
{
    int v_loadStrValue = 0x15;
    int v_strArgSize = 0;
    int v_strArgParsed = 0;
    char v_instructionStr[16];
    char v_argStr[64];

    sscanf(p_line, "%s %s", v_instructionStr, v_argStr);
    char *v_argPointer = v_argStr + 1;
    v_argPointer[strlen(v_argPointer) - 1] = 0;
    v_strArgParsed = strlen(v_argPointer);

    fwrite(&v_loadStrValue, 1, 1, p_arabicaOutput);
    v_strArgSize = v_strArgParsed;

    for (int i = 0; i < v_strArgSize; i++)
    {
        if (i <= (v_strArgSize - 1) && v_argPointer[i] == '\\')
        {
            v_argPointer[i] = control_characters_parsing(v_argPointer[i + 1]);
            for (int j = i + 1; j < v_strArgSize - 1; j++)
            {
                v_argPointer[j] = v_argPointer[j + 1];
            }
            v_argPointer[v_strArgSize - 1] = 0;
            v_strArgParsed--;
        }
    }
    fwrite(&v_strArgParsed, 1, 1, p_arabicaOutput);

    for (int i = 0; i < v_strArgParsed; i++)
    {
        fwrite(&v_argPointer[i], 1, 1, p_arabicaOutput);
    }

    (*p_filesize) += 1 + (v_strArgParsed + 1);
}

unsigned int inverseEndianess(unsigned int value)
{
    return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) | ((value >> 8) & 0xFF00) | ((value >> 24) & 0xFF);
}