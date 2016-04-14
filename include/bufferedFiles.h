/**
 * This library manages files mapped in memory.
 * The mapping is done with whole files, not with
 * the mmap system call. Therefore we need to use
 * this call when we want to map huge files.
 * @author Alejandro
 * @version 0.2 (March 2011)
 */
#ifndef BUFFERED_FILES_H
#define BUFFERED_FILES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commonHeader.h>

#define READING 0x01
#define WRITING 0x02
#define WR_APPEND 0x03
#define BREADING 0x04
#define BWRITING 0x05
#define BWR_APPEND 0x06

#define LENGTH_WRBUFF 10000
#define MAX_LENGTH_LINE 1000

/* Represents a memory-mapped file */
typedef struct {
    FILE *fileId;
    int numOfLines;
    char mode;
    long int size;
    long int currentPos;
    unsigned char *currentLine;
    unsigned char *content;
} BF_FILE;


BF_FILE *BF_open(char *filePath, char mode);
unsigned char *BF_readLine(BF_FILE *file);
/*void BF_readLine(BF_FILE *file, unsigned char *line);*/
void BF_write(unsigned char *line, BF_FILE *file);
long int getSize(FILE *file);
void BF_close(BF_FILE *file);

#ifdef __cplusplus
}
#endif

#endif
