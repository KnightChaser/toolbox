#include <iostream>
#include <cmath>

long long karatsubaMultiplication(long long x, long long y) {

    if (x < 10 || y < 10)
        return x * y;
        
    // Calculate ceil(len/2) to further operation
    int operandLength = std::min((int)(log10(x) + 1), (int)(log10(y) + 1));
    operandLength = operandLength / 2;
    
    // Split the number into halves
    long long power = static_cast<long long>(std::pow(10, operandLength));
    long long highX = x / power;
    long long lowX  = x % power;
    long long highY = y / power;
    long long lowY  = y % power;

    // Recursive call in O(log3) time complexity
    long long z0 = karatsubaMultiplication(lowX, lowY);
    long long z1 = karatsubaMultiplication((highX + lowX), (highY + lowY));
    long long z2 = karatsubaMultiplication(highX, highY);

    return ((z2 * std::pow(10, operandLength * 2)) + ((z1 - z2 - z0) * std::pow(10, operandLength)) + z0);
}

int main(void) {
    
    long long A = 1000;
    long long B = 1000;

    std::cout << A << " * " << B << " = " << karatsubaMultiplication(A, B) << std::endl;

    return 0;
}
