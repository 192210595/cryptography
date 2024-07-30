#include <stdio.h>
#include <stdint.h>
#define BLOCK_SIZE_64 8
#define BLOCK_SIZE_128 16
void generateSubKeys(uint8_t *key, int keySize, uint8_t *subKey1, uint8_t *subKey2) {
    uint8_t zeroBlock[BLOCK_SIZE_128] = {0}; 
    uint8_t cipher[BLOCK_SIZE_128] = {0}; 
    for (int i = 0; i < BLOCK_SIZE_128; ++i) {
        cipher[i] = zeroBlock[i];
    }
    int carry = 0;
    for (int i = 0; i < BLOCK_SIZE_128; ++i) {
        int newCarry = (cipher[i] & 0x80) >> 7;
        cipher[i] = (cipher[i] << 1) | carry;
        carry = newCarry;
    }
    if (keySize == BLOCK_SIZE_64) {
        
        uint8_t constant[BLOCK_SIZE_64] = {0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B};
        for (int i = 0; i < BLOCK_SIZE_64; ++i) {
            subKey1[i] = cipher[i] ^ constant[i];
        }
    } else if (keySize == BLOCK_SIZE_128) {
       
        uint8_t constant[BLOCK_SIZE_128] = {
            0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87,
            0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87
        };
        for (int i = 0; i < BLOCK_SIZE_128; ++i) {
            subKey1[i] = cipher[i] ^ constant[i];
        }
    }
    carry = (subKey1[0] & 0x80) >> 7;
    for (int i = 0; i < keySize; ++i) {
        int newCarry = (subKey1[i] & 0x80) >> 7;
        subKey2[i] = (subKey1[i] << 1) | carry;
        carry = newCarry;
    }
}

int main() {
    uint8_t key64[BLOCK_SIZE_64] = {0}; 
    uint8_t subKey1_64[BLOCK_SIZE_64];
    uint8_t subKey2_64[BLOCK_SIZE_64];

    uint8_t key128[BLOCK_SIZE_128] = {0};
    uint8_t subKey1_128[BLOCK_SIZE_128];
    uint8_t subKey2_128[BLOCK_SIZE_128];

   
    generateSubKeys(key64, BLOCK_SIZE_64, subKey1_64, subKey2_64);
    generateSubKeys(key128, BLOCK_SIZE_128, subKey1_128, subKey2_128);
    printf("Subkey 1 (64-bit):\n");
    for (int i = 0; i < BLOCK_SIZE_64; ++i) {
        printf("%02X ", subKey1_64[i]);
    }
    printf("\n");

    printf("Subkey 2 (64-bit):\n");
    for (int i = 0; i < BLOCK_SIZE_64; ++i) {
        printf("%02X ", subKey2_64[i]);
    }
    printf("\n");

    printf("Subkey 1 (128-bit):\n");
    for (int i = 0; i < BLOCK_SIZE_128; ++i) {
        printf("%02X ", subKey1_128[i]);
    }
    printf("\n");

    printf("Subkey 2 (128-bit):\n");
    for (int i = 0; i < BLOCK_SIZE_128; ++i) {
        printf("%02X ", subKey2_128[i]);
    }
    printf("\n");

    return 0;
}
