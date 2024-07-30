#include <stdio.h>
#include <ctype.h>
char encrypt_char(int a, int b, char plaintext) {
    if (isalpha(plaintext)) {
        int shift = (a * (toupper(plaintext) - 'A') + b) % 26;
        return 'A' + shift;
    }
    return plaintext; 
}
void encrypt_affine_caesar(int a, int b, const char *plaintext) {
    printf("Ciphertext: ");
    while (*plaintext != '\0') {
        printf("%c", encrypt_char(a, b, *plaintext));
        plaintext++;
    }
    printf("\n");
}

int main() {
    const char *plaintext = "Hello, World!";
    int a = 5; 
    int b = 8; 
    encrypt_affine_caesar(a, b, plaintext);
    
    return 0;
}

