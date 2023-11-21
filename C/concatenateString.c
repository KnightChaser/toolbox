#include <stdio.h>
#include <string.h>
#define MAX_STRING_LENGTH 1024

// Get two string literal by char* pointer,
// concatenate, and return to the buffer given.
char *concatenateString(char *strA, 
                        char *strB, 
                        char *strConcatenated) {
    
    // Delete subsequent newline characters to take care of only intended input.
    // fgets() also accept even newline("\n") characters
    strA[strcspn(strA, "\n")] = 0;
    strB[strcspn(strB, "\n")] = 0;
    
    strncpy(strConcatenated, strA, sizeof(strA));
    strncat(strConcatenated, strB, sizeof(strB));
    return strConcatenated;
    
}

int main(void) {
    
    char strA[MAX_STRING_LENGTH / 2];
    char strB[MAX_STRING_LENGTH / 2];
    char strConcatenated[MAX_STRING_LENGTH];
    
    printf("String A: ");
    fgets(strA, MAX_STRING_LENGTH / 2, stdin);
    printf("String B: ");
    fgets(strB, MAX_STRING_LENGTH / 2, stdin);
    
    concatenateString(strA, strB, strConcatenated);
    printf("String concatenated: %s\n", strConcatenated);
    
    return 0;
    
}
