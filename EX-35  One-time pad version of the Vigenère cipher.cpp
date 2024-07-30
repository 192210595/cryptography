#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void encrypt_vigenere(const char *plaintext, const int *key, int key_len) {
    int plaintext_len = strlen(plaintext);
 
    char *ciphertext = (char *)malloc(plaintext_len + 1);
    if (ciphertext == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < plaintext_len; i++) {
   
        char c = plaintext[i];
        if (c >= 'a' && c <= 'z')
            c = c - 'a' + 'A';
       
        if (c >= 'A' && c <= 'Z') {
            int shift = key[i % key_len];
            ciphertext[i] = ((c - 'A' + shift) % 26) + 'A';
        } else {
        
            ciphertext[i] = c;
        }
    }
    ciphertext[plaintext_len] = '\0';
    
    printf("Ciphertext: %s\n", ciphertext);
    free(ciphertext);
}

int main() {
    const char *plaintext = "Hello, World!";
    int key[] = {3, 19, 5}; 
    int key_len = sizeof(key) / sizeof(key[0]);
    encrypt_vigenere(plaintext, key, key_len);
    
    return 0;
}

