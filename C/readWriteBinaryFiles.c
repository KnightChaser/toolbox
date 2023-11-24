#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT_QTY 100

// Just create random numbers
void generateRandomNumbers(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand() % 123456;
    }
}

// binary file
void writeToFile(const char* filename, int* array, int size) {
    FILE* file = fopen(filename, "wb");

    if (file == NULL) {
        printf("Error opening file for writing!\n");
        exit(1);
    }

    fwrite(array, sizeof(int), size, file);
    fclose(file);
}

// binary file
void readFromFile(const char* filename, int* array, int size) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Error opening file for reading!\n");
        exit(1);
    }

    fread(array, sizeof(int), size, file);
    fclose(file);
}

void printArray(int* array, int size) {
    for (int _seq = 0; _seq < size; _seq++) {
        int number = array[_seq];
        printf("arr[%03d] => %06d(0x%06x) \n", _seq, number, number);
    }
    printf("\n");
}

int main(void) {
    const char* filepath = "somethingRandom.dat";

    // Set up for random numbers
    srand((unsigned int)time(NULL));
    int numbers[MAX_ELEMENT_QTY];
    generateRandomNumbers(numbers, MAX_ELEMENT_QTY);

    writeToFile(filepath, numbers, MAX_ELEMENT_QTY);

    printf("\nSave and reload....\n");
    printArray(numbers, MAX_ELEMENT_QTY);
    readFromFile(filepath, numbers, MAX_ELEMENT_QTY);

    printf("\n================================\n");
    printArray(numbers, MAX_ELEMENT_QTY);

    return 0;
}
