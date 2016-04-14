/**
 * Memory-mapped files handling
 * @author Alejandro
 * @version 0.3
 */
#include <bufferedFiles.h>

/**
 * Maps in memory a certain file
 * @param filePath Path to the file
 * @return Buffer with the file, NULL if it fails
 */
BF_FILE *BF_open(char *filePath, char mode) {
    BF_FILE *returnedFile = NULL;
	FILE *file = NULL;
    int numOfLines = 0;
    int sizeOfFile = 0;
    int i;
	
    /* Select the mode to open the file */
    switch(mode) {
        case READING: file = fopen(filePath,"rb"); break;
        case WRITING: file = fopen(filePath,"wb"); break;
        /*case WR_APPEND: fopen(filePath,"a"); break;
        case BREADING: fopen(filePath,"rb"); break;
        case BWRITING: fopen(filePath,"wb"); break;
        case BWR_APPEND: fopen(filePath,"ab"); break;*/
    }
    
	if(file) {
        returnedFile = _pmalloc(BF_FILE, 1);
        returnedFile->mode = mode;
        
        if(returnedFile->mode == READING) {
            returnedFile->size = getSize(file);
            sizeOfFile = returnedFile->size;
            returnedFile->content = _pmalloc(unsigned char, returnedFile->size);

            fread(returnedFile->content,returnedFile->size,1,file);
            fclose(file);
            
            for(i = 0; i < sizeOfFile; i++)
                if(*(returnedFile->content + i) == '\n') numOfLines++;
            
            returnedFile->numOfLines = numOfLines;
        } else {
            returnedFile->content = _pmalloc(unsigned char, LENGTH_WRBUFF);
            returnedFile->fileId = file;
        }
	} else
        printf("[Error] Cannot open file %s\n", filePath);
	
	return returnedFile;
}

/**
 * Reads a line of the mapped file
 * @return NULL if there isn't any more characters to read
 */
unsigned char *BF_readLine(BF_FILE *file) {
    long int startPos = file->currentPos;
    long int size = file->size;
    unsigned char *buffer = file->content;
	unsigned char *line = NULL;
	int remainChars = 0;
    int lengthString = 0;
    int offset = 0;
	
    if(startPos >= size - 1) return NULL;
	
    while (*(buffer + startPos + offset) != 0x0a &&
           startPos + offset < size)
        offset++;
	
    /* Windows or linux EOL */
    if(*(buffer + startPos + offset - 1) == 0x0d &&
       *(buffer + startPos + offset) == 0x0a)
        remainChars = 1;
     
    file->currentPos += (offset + 1);
    
    /* Copy the string on the buffer */
	lengthString = offset - remainChars + 1;
    line = _pmalloc(unsigned char, lengthString);
	memcpy(line, buffer + startPos, lengthString - 1);
    
	return line;
}

/**
 * Writing of a line in the buffered file. It doesn't notice the EOL chars
 */
void BF_write(unsigned char *line, BF_FILE *file) {
    int currentPos = file->currentPos;
    unsigned char *writBuffer = file->content;
    int lineLength = strlen((char *) line);
    int remainChars = 0;
    int possibleChars = 0;
    
    if(currentPos + lineLength < LENGTH_WRBUFF) {
        /* The string has a length of less or equal than the buffer length */
        memcpy(writBuffer + currentPos, line, lineLength);
        file->currentPos += lineLength;
    } else {
        /* Only a piece of string fits in the buffer */
        possibleChars = LENGTH_WRBUFF - currentPos;
        remainChars = lineLength - possibleChars;
        memcpy(writBuffer + currentPos, line, possibleChars);
        fwrite(writBuffer, LENGTH_WRBUFF, 1, file->fileId);
        memcpy(writBuffer, line + possibleChars, remainChars);
        file->currentPos = remainChars;
    }
}

/**
 * Size of file calculation
 */
long int getSize(FILE *file) {
	long int end = 0;
	
	fseek(file, 0, SEEK_END);
	end = ftell(file);
	fseek(file, 0, SEEK_SET);

	return end;
}

/**
 * Close a file and deallocate the space used
 */
void BF_close(BF_FILE *file) {
    if(file->mode == WRITING) {
        fwrite(file->content, file->currentPos, 1, file->fileId);
        fclose(file->fileId);
    }
    
    pfree(file->content);
    pfree(file);
}
