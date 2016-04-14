#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

#include <stdlib.h>
#include <string.h>

#define _pmalloc(type, numElems) (type*) pmalloc(sizeof(type), numElems)

#define FALSE 0
#define TRUE 1
typedef int BOOLEAN;

typedef struct {
    int numElems;
    char **content;
} ARRAY_PCH; /* Array of pointers to char (strings) */

/* Memory allocation and deallocation */
void *pmalloc(int size, int elems);
void pfree(void *buffer);

#endif
