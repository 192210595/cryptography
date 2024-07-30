#include <stdio.h>
#include <stdlib.h>

long long modPow(long long a, long long b, long long p) {
    long long result = 1;
    a = a % p;
    while (b > 0) {
        if (b & 1) result = (result * a) % p;
        b = b >> 1;
        a = (a * a) % p;
    }
    return result;
}

int main() {
    long long p = 23; 
    long long g = 5;  
    long long a = 6; 
    long long A = modPow(g, a, p);
    long long b = 15; 
    long long B = modPow(g, b, p);
    long long secretAlice = modPow(B, a, p);
    long long secretBob = modPow(A, b, p);

    printf("Alice's Shared Secret: %lld\n", secretAlice);
    printf("Bob's Shared Secret: %lld\n", secretBob);

    return 0;
}

