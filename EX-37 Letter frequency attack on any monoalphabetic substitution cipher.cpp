#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
void calculate_letter_frequency(const char *ciphertext, int *frequency) {
    memset(frequency, 0, ALPHABET_SIZE * sizeof(int));
    
    while (*ciphertext != '\0') {
        if (isalpha(*ciphertext)) {
            char letter = toupper(*ciphertext);
            frequency[letter - 'A']++;
        }
        ciphertext++;
    }
}
void letter_frequency_attack(const char *ciphertext, int top_n) {
    int frequency[ALPHABET_SIZE];
    calculate_letter_frequency(ciphertext, frequency);
    
    printf("Letter Frequency Analysis:\n");
    printf("==========================\n");
    int sorted_indices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_indices[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequency[sorted_indices[i]] < frequency[sorted_indices[j]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }
    printf("Possible Plaintexts:\n");
    printf("====================\n");
    for (int i = 0; i < top_n && i < ALPHABET_SIZE; i++) {
        char possible_plaintext[ALPHABET_SIZE + 1];
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            int shift = (sorted_indices[i] - j + ALPHABET_SIZE) % ALPHABET_SIZE;
            possible_plaintext[j] = 'A' + shift;
        }
        possible_plaintext[ALPHABET_SIZE] = '\0';
        printf("%2d. %s\n", i + 1, possible_plaintext);
    }
}

int main() {
    const char *ciphertext = "Lxqlqb qefp xkaexqzf rq ql axkexqzfe tmzqfe qefp.";
    int top_n = 10;
    letter_frequency_attack(ciphertext, top_n);

    return 0;
}

