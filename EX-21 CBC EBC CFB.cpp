#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8


void ecb_encrypt(unsigned char *plaintext, unsigned char *key, int size) {
    for (int i = 0; i < size; i++) {
        plaintext[i] ^= key[i % BLOCK_SIZE];
    }
}


void ecb_decrypt(unsigned char *ciphertext, unsigned char *key, int size) {
    ecb_encrypt(ciphertext, key, size);  
}


void cbc_encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *iv, int size) {
    for (int i = 0; i < size; i++) {
        plaintext[i] ^= iv[i % BLOCK_SIZE];
        plaintext[i] ^= key[i % BLOCK_SIZE];
        iv[i % BLOCK_SIZE] = plaintext[i]; 
    }
}


void cbc_decrypt(unsigned char *ciphertext, unsigned char *key, unsigned char *iv, int size) {
    unsigned char temp, next_iv;
    for (int i = size - 1; i >= 0; i--) {
        next_iv = ciphertext[i]; 
        ciphertext[i] ^= key[i % BLOCK_SIZE];
        ciphertext[i] ^= iv[i % BLOCK_SIZE];
        iv[i % BLOCK_SIZE] = next_iv; 
    }
}


void cfb_encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *iv, int size) {
    for (int i = 0; i < size; i++) {
        unsigned char encrypted_byte = plaintext[i] ^ key[i % BLOCK_SIZE];
        plaintext[i] = encrypted_byte ^ iv[i % BLOCK_SIZE];
        iv[i % BLOCK_SIZE] = encrypted_byte; 
    }
}


void cfb_decrypt(unsigned char *ciphertext, unsigned char *key, unsigned char *iv, int size) {
    for (int i = 0; i < size; i++) {
        unsigned char encrypted_byte = ciphertext[i] ^ key[i % BLOCK_SIZE];
        ciphertext[i] = encrypted_byte ^ iv[i % BLOCK_SIZE];
        iv[i % BLOCK_SIZE] = ciphertext[i]; 
    }
}

int main() {
    unsigned char plaintext[] = "01234567"; 
    unsigned char key[] = "abcdefgh"; 
    unsigned char iv[] = "12345678"; 

    printf("Plaintext: %s\n", plaintext);

  
    printf("\nECB Mode:\n");
    ecb_encrypt(plaintext, key, BLOCK_SIZE);
    printf("Encrypted: %s\n", plaintext);
    ecb_decrypt(plaintext, key, BLOCK_SIZE);
    printf("Decrypted: %s\n", plaintext);

 
    printf("\nCBC Mode:\n");
    unsigned char ciphertext_cbc[BLOCK_SIZE];
    memcpy(ciphertext_cbc, plaintext, BLOCK_SIZE); 
    cbc_encrypt(plaintext, key, iv, BLOCK_SIZE);
    printf("Encrypted: %s\n", plaintext);
    cbc_decrypt(plaintext, key, iv, BLOCK_SIZE);
    printf("Decrypted: %s\n", plaintext);

   
    printf("\nCFB Mode:\n");
    unsigned char ciphertext_cfb[BLOCK_SIZE];
    memcpy(ciphertext_cfb, plaintext, BLOCK_SIZE); 
    cfb_encrypt(plaintext, key, iv, BLOCK_SIZE);
    printf("Encrypted: %s\n", plaintext);
    cfb_decrypt(plaintext, key, iv, BLOCK_SIZE);
    printf("Decrypted: %s\n", plaintext);

    return 0;
}
