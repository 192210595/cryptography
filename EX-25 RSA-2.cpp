#include <stdio.h>
#include <stdlib.h>


int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}


int rsa_encrypt(int plaintext, int e, int n) {
    int ciphertext = 1;
    for (int i = 0; i < e; i++) {
        ciphertext = (ciphertext * plaintext) % n;
    }
    return ciphertext;
}

int main() {
    
    int p = 61;
    int q = 53;
    int n = p * q;
    int e = 17;

    
    int plaintext_blocks[] = {123, 456, 789, 1111};

    
    printf("Plaintext Blocks:\n");
    for (int i = 0; i < sizeof(plaintext_blocks) / sizeof(plaintext_blocks[0]); i++) {
        printf("%d ", plaintext_blocks[i]);
    }
    printf("\n\nCiphertext Blocks:\n");
    for (int i = 0; i < sizeof(plaintext_blocks) / sizeof(plaintext_blocks[0]); i++) {
        int ciphertext = rsa_encrypt(plaintext_blocks[i], e, n);
        printf("%d ", ciphertext);
    }

    return 0;
}
