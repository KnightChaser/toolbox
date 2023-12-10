#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    unsigned int x, y;

    // Get values for x and y (you can use any method to obtain these values)
    printf("Enter the number of rows (x): ");       scanf("%d", &x);
    printf("Enter the number of columns (y): ");    scanf("%d", &y);

    // Dynamically allocate memory for the 2D array
    char **array = (char **)malloc(x * sizeof(char *));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < x; i++) {
        array[i] = (char *)malloc(y * sizeof(char));
        if (array[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            // Free previously allocated memory before returning
            for (int j = 0; j < i; j++)
                free(array[j]);
            free(array);
            return -1;
        }
    }

    char currentCharacter = 'A';
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            array[i][j] = currentCharacter;
            printf("%c ", array[i][j]);
    
            // Only print from 'A' to 'Z'
            currentCharacter++;
            if (currentCharacter > 'Z')
                currentCharacter = 'A';
        }
        printf("\n");
    }

    // Free the memory
    for (int i = 0; i < x; i++)
        free(array[i]);
    free(array);

    return 0;
}
