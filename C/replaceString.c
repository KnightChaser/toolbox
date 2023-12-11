#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void replaceString(const char* string,
    const char* replaceFrom,
    const char* replaceTo,
    char* replaced) {

    const char* matchFound = string;
    size_t replaceFromLength = strlen(replaceFrom);
    size_t replaceToLength = strlen(replaceTo);

    while ((matchFound = strstr(matchFound, replaceFrom)) != NULL) {
        strncat(replaced, string, matchFound - string);                // Copy the part of the string before the match
        strcat(replaced, replaceTo);                                   // Copy the replacement string
        matchFound += replaceFromLength;                               // Move currentPosition past the replaced substring
        string = matchFound;                                           // Update string to point to the remaining part of the original string
    }

    strcat(replaced, string);                                          // Copy the remaining part of the original string (finished)
}

int main(void) {
    char string[1024];
    char replaceFrom[100];
    char replaceTo[100];
    char replaced[1024] = "";

    printf("Enter the string: ");               scanf("%1023[^\n]", string);     // Read up to 1023 characters until a newline is encountered
    printf("Enter the word to replace: ");      scanf("%99s", replaceFrom);      // Read up to 99 characters or until whitespace is encountered
    printf("Enter the replacement word: ");     scanf("%99s", replaceTo);        // Read up to 99 characters or until whitespace is encountered

    replaceString(string, replaceFrom, replaceTo, replaced);
    printf("Replaced string: %s\n", replaced);

    return 0;
}
