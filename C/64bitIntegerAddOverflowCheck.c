// Targeted for Microsoft Visual Studio (Windows) environment.
// Inline assembly depends on the runtime environment.
#include <stdio.h>
#define LONG_LONG_MAX 9223372036854775807LL

long long addWithOverflowCheck(long long a, long long b, long long* result, int* overflow) {

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

    return *result;
}

int main(void) {

    long long result;
    int overflow;

    result = addWithOverflowCheck(LONG_MAX, 1LL, &result, &overflow);

    if (overflow)
        printf("Overflow occurred!\n");
    else
        printf("Result: %lld\n", result);

    return 0;
}
