// Targeted for Microsoft Visual Studio (Windows) environment.
// Inline assembly depends on the runtime environment.
#include <stdio.h>
#include <stdbool.h>
#define LONG_LONG_MAX +9223372036854775807LL
#define LONG_LONG_MIN -9223372036854775808LL

// Add two long long integer OOR(Out-Of-Range; overflow and underflow) check
long long addTwoLLIntOORCheck(const long long a, 
                              const long long b, 
                              long long* result, 
                              int* overflow, int* underflow) {

    *overflow = 0;

    // Inline assembly to add a and b, storing the result in result
    __asm {
        mov eax, dword ptr[a]               ; Lower 32 bits of a
        mov edx, dword ptr[a + 4]           ; Upper 32 bits of a
        add eax, dword ptr[b]               ; Lower 32 bits of b
        adc edx, dword ptr[b + 4]           ; Add with carry for upper 32 bits
        mov ecx, result
        mov dword ptr[ecx], eax             ; Store the lower 32 bits of the result
        mov dword ptr[ecx + 4], edx         ; Store the upper 32 bits of the result

        jo overflow_label                   ; Jump to overflow_label if overflow occurred
        jmp end_label                       ; Jump to end_label(overflow not occurred)

        overflow_label:
            mov ecx, overflow
            mov byte ptr[ecx], 1            ; Set overflow bit up

        end_label:
    }

    // When there is a signed numbers at least while the overflow flag is set up, it's underflow actually.
    if (*overflow == true) {
        *overflow = false;
        *underflow = true;
    }

    return *result;
}

int main(void) {

    long long result;
    int overflow = false;
    int underflow = false;

    result = addTwoLLIntOORCheck(LONG_LONG_MIN, -1LL, &result, &overflow, &underflow);

    if (overflow)
        printf("Overflow occurred!\n");
    else if (underflow)
        printf("Underflow occurred!\n");
    else
        printf("Result: %lld\n", result);

    return 0;
}
