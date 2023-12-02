#include <stdio.h>
#define LONG_LONG_MAX           9223372036854775807LL
#define LONG_LONG_MIN           -9223372036854775808LL

long long multiply(long long a, long long b) {
    // Check for overflow
    if (((a > 0 && b > LONG_LONG_MAX / a) || (a < 0 && b < LONG_LONG_MAX / a)) ||
        ((b > 0 && a > LONG_LONG_MAX / b) || (b < 0 && a < LONG_LONG_MAX / b))) {
        // Overflow
        printf("overflow\n");
        return 0;
    }

    // Check for underflow
    if (((a > 0 && b < LONG_LONG_MIN / a) || (a < 0 && b < LONG_LONG_MIN / a)) ||
        ((b > 0 && a < LONG_LONG_MIN / b) || (b < 0 && a < LONG_LONG_MIN / b))) { 
        // Underflow
        printf("underflow\n");
        return 0;
    }

    long long result = a * b;
    return result;
    
}

int main() {
    long long num1 = -2;
    long long num2 = 9223372036854775207LL;

    printf("%lld * %lld = %lld", num1, num2, multiply(num1, num2));

    return 0;
}
