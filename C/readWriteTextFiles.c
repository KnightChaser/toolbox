#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 2048
#include <stdio.h>

int main() {
    FILE* file;
    char input[MAX_LENGTH];
    char output[MAX_LENGTH];
    const char* filepath = "output.txt";

    // Open the file in append mode (creates file if it doesn't exist)
    file = fopen(filepath, "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    printf("Input...> ");
    fgets(input, sizeof(input), stdin);
    fprintf(file, "%s", input);
    fclose(file);

    // Open the file in read mode
    file = fopen(filepath, "r");

    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return -1;
    }

    // Read and print the contents of the file
    printf("Contents of the file...\n");
    while (fgets(output, sizeof(output), file) != NULL) {
        printf("%s", output);
    }

    fclose(file);

    return 0;
}
