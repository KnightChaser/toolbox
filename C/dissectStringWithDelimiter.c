#include <stdio.h>
#include <string.h>
#define MAX_INPUT_LENGTH 2048

// Dissect the given string into halves according to the given delimiter
// e.g.) "Love+You" => "Love" / "You"
void dissectExpression(const char* expression,
                       char* arrayA,
                       char* arrayB,
                       size_t arraySize,
                       const char delimiter) {

    memset(arrayA, 0, arraySize);
    memset(arrayB, 0, arraySize);

    // Find the position of the given delimiter in the expression
    const char* delimiterPosition = strchr(expression, delimiter);

    // If the delimiter is found, copy characters before the delimiter to arrayA
    if (delimiterPosition != NULL) {
        size_t lengthA = delimiterPosition - expression;
        strncpy(arrayA, expression, lengthA);
        
        size_t lengthB = strlen(delimiterPosition + 1);     // Copy characters after the delimiter to arrayB
        strncpy(arrayB, delimiterPosition + 1, lengthB);
    } else {
        strncpy(arrayA, expression, arraySize - 1);         // Delimter not found. Move everything to array A
    }
}

int main(void) {
    char expression[MAX_INPUT_LENGTH];
    char arrayA[MAX_INPUT_LENGTH / 2];
    char arrayB[MAX_INPUT_LENGTH / 2];
    const char delimiter = '+';

    printf("Enter an expression: ");
    fgets(expression, sizeof(expression), stdin);

    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }

    // Dissected strings according to the given delimter will be stored in arrayA and arrayB, respectively.
    dissectExpression(expression, arrayA, arrayB, sizeof(arrayA), delimiter);

    printf("Array A: %s\n", arrayA);
    printf("Array B: %s\n", arrayB);

    return 0;
}
