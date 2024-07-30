#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>

#define BLOCK_SIZE 16

void xor_blocks(uint8_t *a, uint8_t *b, uint8_t *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = a[i] ^ b[i];
    }
}

void aes_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    AES_encrypt(plaintext, ciphertext, &aes_key);
}

void cbc_mac(uint8_t *message, uint8_t *key, uint8_t *mac) {
    uint8_t iv[BLOCK_SIZE] = {0};
    uint8_t xor_result[BLOCK_SIZE];
    
    xor_blocks(iv, message, xor_result);
    
    aes_encrypt(xor_result, key, mac);
}

int main() {
    uint8_t message[BLOCK_SIZE + 1] = "Hello, World!";  // Include null terminator explicitly
    uint8_t key[BLOCK_SIZE] = "ThisIsASecretKey";
    uint8_t mac[BLOCK_SIZE];
    
    cbc_mac(message, key, mac);
    
    printf("MAC for one-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");
    
    return 0;
}

