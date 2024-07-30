#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepareKey(char *key, char keyMatrix[SIZE][SIZE]) {
    int used[26] = {0};
    int row = 0, col = 0;

    for (int i = 0; i < strlen(key); i++) {
        char ch = tolower(key[i]);
        if (ch == 'j') ch = 'i';

        if (isalpha(ch) && !used[ch - 'a']) {
            keyMatrix[row][col++] = ch;
            used[ch - 'a'] = 1;

            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }

    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch == 'j') continue;

        if (!used[ch - 'a']) {
            keyMatrix[row][col++] = ch;

            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

void findPosition(char keyMatrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'j') ch = 'i';

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char *plaintext, char keyMatrix[SIZE][SIZE]) {
    int len = strlen(plaintext);

    for (int i = 0; i < len; i++) {
        if (!isalpha(plaintext[i])) continue;

        if (i < len - 1 && plaintext[i] == plaintext[i + 1]) {
            for (int j = len; j > i + 1; j--) {
                plaintext[j] = plaintext[j - 1];
            }
            plaintext[i + 1] = 'x';
            len++;
        }
    }

    if (len % 2 != 0) {
        plaintext[len] = 'x';
        len++;
    }

    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findPosition(keyMatrix, plaintext[i], &row1, &col1);
        findPosition(keyMatrix, plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {
            plaintext[i] = keyMatrix[row1][(col1 + 1) % SIZE];
            plaintext[i + 1] = keyMatrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            plaintext[i] = keyMatrix[(row1 + 1) % SIZE][col1];
            plaintext[i + 1] = keyMatrix[(row2 + 1) % SIZE][col2];
        } else {
            plaintext[i] = keyMatrix[row1][col2];
            plaintext[i + 1] = keyMatrix[row2][col1];
        }
    }
}

int main() {
    char key[50], plaintext[100], keyMatrix[SIZE][SIZE];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    key[strcspn(key, "\n")] = '\0';
    plaintext[strcspn(plaintext, "\n")] = '\0';

    prepareKey(key, keyMatrix);
    encrypt(plaintext, keyMatrix);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}

