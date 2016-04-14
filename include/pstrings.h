#ifndef PSTRINGS_H
#define PSTRINGS_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <commonHeader.h>

void getFieldsOfLine(char *line, char separator, ARRAY_PCH *array);
/*char **newArrayStrings(int lengthArray, int lengthString);*/
ARRAY_PCH *newArrayStrings(int lengthArray, int lengthString);
/*void deleteArrayStrings(char **array, int lengthArray);*/
void deleteArrayStrings(ARRAY_PCH *array);
void trim(char *input, char *output);
char *lowercase(char *input);

#endif
