#include <stdio.h>
#define MATRIX_SIZE 3
int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE];
    char plaintext[MATRIX_SIZE + 1]; 
    char ciphertext[MATRIX_SIZE + 1]; 
    int x[MATRIX_SIZE];
    int y[MATRIX_SIZE];
    printf("Enter the key matrix for Hill cipher (3x3):\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            scanf("%d", &key[i][j]);
        }
    }
    printf("Enter the plaintext (3 characters): ");
    scanf("%s", plaintext);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        x[i] = plaintext[i] - 'a';
    }
    for (int i = 0; i < MATRIX_SIZE; i++) {
        y[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            y[i] += key[i][j] * x[j];
        }
        y[i] %= 26;
    }
    for (int i = 0; i < MATRIX_SIZE; i++) {
        ciphertext[i] = y[i] + 'a';
    }
    ciphertext[MATRIX_SIZE] = '\0'; // Null-terminate the string
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

