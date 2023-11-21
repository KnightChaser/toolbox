#include <stdio.h>
#include <string.h>

// The given C code defines a function replaceString that replaces 
// every occurrence of a specified substring within a given string using a loop. 
void replaceString(const char *string,
                   const char *replaceFrom,
                   const char *replaceTo,
                   char *replaced) {

    const char *matchFound = string;                                // Traverse since the given string
    size_t replaceFromLength = strlen(replaceFrom);
    size_t replaceToLength = strlen(replaceTo);

    // Iterate processes to find every exact match.
    while ((matchFound = strstr(currentPosition, replaceFrom)) != NULL) {
    
        strncat(replaced, string, matchFound - string);             // Copy the part of the string before the match
        strcat(replaced, replaceTo);                                // Copy the replacement string
        matchFound += replaceFromLength;                            // Move currentPosition past the replaced substring
        string = matchFound;                                        // Update string to point to the remaining part of the original string
    }

    strcat(replaced, string);                                       // Copy the remaining part of the original string (finished)
}

int main(void) {

    const char string[1024] = "damn it, Clang doesn't support that very damnin' string replacemethod like C++!!!";
    const char replaceFrom[] = "damn";
    const char replaceTo[] = "F*ck";
    char replaced[1024] = "";

    replaceString(string, replaceFrom, replaceTo, replaced);
    printf("%s\n", replaced);

    return 0;
}
