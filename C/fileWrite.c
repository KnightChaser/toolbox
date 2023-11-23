#include <stdio.h>

int main() {
    FILE* file;
    char input[1024];

    file = fopen("output.txt", "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    printf("Input...> ");
    fgets(input, sizeof(input), stdin);
    fprintf(file, "%s", input);
    fclose(file);

    return 0;
}
