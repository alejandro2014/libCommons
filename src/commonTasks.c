#include <commonHeader.h>
#include <stdio.h>

/**
 * Deallocates a certain buffer of memory
 * \param buffer Buffer that we want to deallocate
 */
void pfree(void *buffer) {
    if(buffer) {
        free(buffer);
        buffer = NULL;
    }
}

/**
 * Memory allocation and proper asignation
 * \param size Size in bytes that we want to allocate
 * \param elems Number of elements that we want to allocate
 */
void *pmalloc(int size, int elems) {
    int sizeArray = size * elems;
    char *newVariable = NULL; 
    
    if(sizeArray > 0)
        newVariable = (char *) malloc(sizeArray);
    
    if(newVariable) {
        memset(newVariable, 0, sizeArray);
        return (void *) newVariable;
    }
    
    return NULL;
}
