#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 10
typedef struct {
    int rows;
    int cols;
    int data[MAX_SIZE][MAX_SIZE];
} Matrix;
void initMatrix(Matrix *matrix, int rows, int cols) {
    matrix->rows = rows;
    matrix->cols = cols;
    memset(matrix->data, 0, sizeof(matrix->data));
}

void printMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

int determinant(Matrix *matrix) {
    return matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];
}

Matrix inverse(Matrix *matrix) {
    Matrix result;
    initMatrix(&result, 2, 2);
    
    int det = determinant(matrix);
    if (det == 0) {
        printf("Matrix is not invertible\n");
        exit(1);
    }
    int invDet = ((int)pow(det, -1)) % 26; 
    result.data[0][0] = (matrix->data[1][1] * invDet) % 26;
    result.data[1][1] = (matrix->data[0][0] * invDet) % 26;
    result.data[0][1] = ((-matrix->data[0][1]) * invDet) % 26;
    result.data[1][0] = ((-matrix->data[1][0]) * invDet) % 26;
    
    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            if (result.data[i][j] < 0)
                result.data[i][j] += 26;
        }
    }
    
    return result;
}
void encrypt(char *plaintext, Matrix *key) {
    int len = strlen(plaintext);
    int i, j, k;
    int cipher[MAX_SIZE];
    
    for (i = 0; i < len; i += 2) {
        for (j = 0; j < 2; j++) {
            cipher[i + j] = 0;
            for (k = 0; k < 2; k++) {
                cipher[i + j] += key->data[j][k] * (plaintext[i + k] - 'A');
            }
            cipher[i + j] %= 26;
        }
    }
    
    for (i = 0; i < len; i++) {
        plaintext[i] = cipher[i] + 'A';
    }
}
void decrypt(char *ciphertext, Matrix *key) {
    Matrix invKey = inverse(key);
    int len = strlen(ciphertext);
    int i, j, k;
    int plain[MAX_SIZE];
    
    for (i = 0; i < len; i += 2) {
        for (j = 0; j < 2; j++) {
            plain[i + j] = 0;
            for (k = 0; k < 2; k++) {
                plain[i + j] += invKey.data[j][k] * (ciphertext[i + k] - 'A');
            }
            plain[i + j] %= 26;
        }
    }
    
    for (i = 0; i < len; i++) {
        ciphertext[i] = plain[i] + 'A';
    }
}

int main() {
    char plaintext[] = "HELLO"; 
    char ciphertext[] = "LMXSO"; 
    Matrix key;
    initMatrix(&key, 2, 2);
    key.data[0][0] = (ciphertext[0] - 'A' - (plaintext[0] - 'A')) % 26;
    key.data[0][1] = (ciphertext[1] - 'A' - (plaintext[1] - 'A')) % 26;
    key.data[1][0] = (ciphertext[2] - 'A' - (plaintext[2] - 'A')) % 26;
    key.data[1][1] = (ciphertext[3] - 'A' - (plaintext[3] - 'A')) % 26;
    for (int i = 0; i < key.rows; i++) {
        for (int j = 0; j < key.cols; j++) {
            if (key.data[i][j] < 0)
                key.data[i][j] += 26;
        }
    }
    
    printf("Key Matrix:\n");
    printMatrix(&key);
    decrypt(ciphertext, &key);
    printf("Recovered Plaintext: %s\n", ciphertext);
    
    return 0;
}

