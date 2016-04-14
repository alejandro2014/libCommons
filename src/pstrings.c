#include <pstrings.h>

/**
 * This function gets the fields of a line delimited by a separator
 * \param line Line to be readed
 * \param separator The char that we want to use as separator
 * \param array Array where the fields have to be stored
 */
void getFieldsOfLine(char *line, char separator, ARRAY_PCH *array) {
    char **fieldsStruct = array->content;
    int numFields = array->numElems;
	int lastPosition = 0;
	int length = strlen(line) + 1;
	int i;
	int currentField = 0;
	int lengthString;
    int numF = 0;
    
	/* Copy all fields, until it finished, or the space runs out */
	for(i = 0; i < length; i++) {
		if(currentField < numFields && (*(line + i) == separator || 
                                        *(line + i) == 0x00)) {
			lengthString = i - lastPosition + 1;
			memcpy(fieldsStruct[currentField], line + lastPosition,
                   lengthString - 1);
            *(fieldsStruct[currentField] + lengthString - 1) = 0x00;
            
            currentField++;
			lastPosition = i + 1;
            numF++;
		}
	}
}

/**
 * Memory allocation for an array of strings
 * \param lengthArray Number of strings of the new structure
 * \param lengthString Max length of the the strings
 */
ARRAY_PCH *newArrayStrings(int lengthArray, int lengthString) {
    ARRAY_PCH *array = _pmalloc(ARRAY_PCH, 1);
    char **content = NULL;
    int i;
    
    if(array) {
        content = _pmalloc(char *, lengthArray);
        
        if(content) {
            for(i = 0; i < lengthArray; i++) {
                content[i] = _pmalloc(char, lengthString);
            }
            
            array->numElems = lengthArray;
            array->content = content;
        } else
            pfree(array);
    }
    
    return array;
}

/**
 * Deallocation of an array of strings
 * \param array Array to be deallocated from memory
 */
void deleteArrayStrings(ARRAY_PCH *array) {
    char **content = NULL;
    int lengthArray = -1;
    int i;
    
    if(array) {
        content = array->content;
        lengthArray = array->numElems;
    
        if(content) {
            for(i = 0; i < lengthArray; i++) {
                pfree(content[i]);
            }
            
            pfree(array->content);
        }
        
        pfree(array);
    }
}

/**
 * Convert a string to lowercase
 * \param input String to be converted
 * \return The string in lowercase
 */
char *lowercase(char *input) {
	int lengthString = strlen(input);
	int i;
	char currChar;
	
	for(i = 0; i < lengthString; i++) {
        currChar = *(input + i);
		if(isupper(currChar)) *(input + i) += 0x20;
	}
	
	return input;
}

/**
 * Removes the spaces from a string
 * \param input Input string
 * \param output The string trimmed
 */
void trim(char *input, char *output) {
    int i;
    int newPosition = 0;
    int length = 0;
    
    if(input) {
        length = strlen(input);

        /* Copy only the characters that aren't spaces */
        for(i = 0; i < length; i++) {
            if(*(input + i) != 0x20)
                *(output + (newPosition++)) = *(input + i);
        }
    
        *(output + newPosition) = 0x00;
    }
}
