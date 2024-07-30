#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int initial_permutation[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int final_permutation[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

void initialPermutation(uint64_t *data) {
    uint64_t newData = 0;
    for (int i = 0; i < 64; i++) {
        newData |= ((*data >> (64 - initial_permutation[i])) & 1) << (63 - i);
    }
    *data = newData;
}
void finalPermutation(uint64_t *data) {
    uint64_t newData = 0;
    for (int i = 0; i < 64; i++) {
        newData |= ((*data >> (64 - final_permutation[i])) & 1) << (63 - i);
    }
    *data = newData;
}

void desEncrypt(uint64_t *data) {
    uint64_t key = 0b11110000110011001010101011110101010101100110011110000;

    *data ^= key;

    initialPermutation(data);
    finalPermutation(data);
}

void desDecrypt(uint64_t *data) {
    desEncrypt(data);
}

int main() {
    uint64_t plaintext = 0b1100110000000000110011001111111111110000101010101111000010101010;

    printf("Original Plaintext: 0x%llx\n", plaintext);
    desEncrypt(&plaintext);
    printf("Encrypted Ciphertext: 0x%llx\n", plaintext);

    desDecrypt(&plaintext);
    printf("Decrypted Plaintext: 0x%llx\n", plaintext);

    return 0;
}
