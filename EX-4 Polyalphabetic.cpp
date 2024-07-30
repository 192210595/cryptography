
#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char *plaintext, char *key) {
    int keyLength = strlen(key);
    int plaintextLength = strlen(plaintext);

    for (int i = 0; i < plaintextLength; i++) {
        char currentKey = tolower(key[i % keyLength]); 
        int shift = currentKey - 'a'; 

        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            plaintext[i] = base + (plaintext[i] - base + shift) % 26; 
        }
    }
}
int main() {
    char plaintext[1000];
    char key[100];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    plaintext[strcspn(plaintext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    encrypt(plaintext, key);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}


