#include <stdio.h>
#include <string.h>

unsigned long long calculateEffectiveKeys(char *key) {
    
    int matrixSize = 25;

    
    char usedLetters[matrixSize];
    memset(usedLetters, '\0', sizeof(usedLetters));

    int index = 0;

    
    for (int i = 0; i < strlen(key); i++) {
        if (key[i] != ' ' && key[i] != 'J' && !strchr(usedLetters, key[i])) {
            usedLetters[index++] = key[i];
        }
    }

    
    int emptySlots = matrixSize - index;

    
    unsigned long long effectiveKeys = 1;
    for (int i = matrixSize; i > emptySlots; i--) {
        effectiveKeys *= i;
    }

    return effectiveKeys;
}

int main() {
    char key[26];

    
    printf("Enter the key for the Playfair cipher (without spaces, 'J' excluded): ");
    scanf("%s", key);

    
    unsigned long long uniqueKeys = calculateEffectiveKeys(key);
    printf("Number of effectively unique keys: %llu\n", uniqueKeys);

    return 0;
}
