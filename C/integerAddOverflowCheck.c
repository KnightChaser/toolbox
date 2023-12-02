// Targeted for Microsoft Visual Studio (Windows) environment.
// Inline assembly depends on the runtime environment.
#include <stdio.h>
#define INT_MAX 2147483647

int addWithOverflowCheck(int a, int b, int* result, int* overflow) {

    int sum;
    *overflow = 0;

    // Inline assembly to add a and b, storing the result in sum
    __asm {
        mov eax, a
        add eax, b
        mov ecx, result
        mov[ecx], eax

        jo overflow_label           ; Jump to overflow_label if overflow occurred
        jmp end_label               ; Jump to end_label(overflow not occured)

        overflow_label:
            mov ecx, overflow
            mov byte ptr[ecx], 1    ; Set overflow bit up

        end_label:
    }

    return *result;
}

int main(void) {

    int result;
    int overflow;

    result = addWithOverflowCheck(INT_MAX, 1, &result, &overflow);

    if (overflow)
        printf("Overflow occurred!\n");
    else
        printf("Result: %d\n", result);

    return 0;

}
